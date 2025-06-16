void uartInit(void)
{
    if(!(settings.asl&1))
    {
        EXA1 &= 0x3f;
        EXA1 |= 0x40;
        SFR91 &= 0x8fu;
        SFR91 |= 0x30;
        EXA1 |= 0x10;
        exUart1Con &= 0xf8u;
        PCON |= 0x40;
        exUart1Baud = 0xb2ffu;
        exUart1Con |= 0x80u;
        exUart1Port = 0x11;
        exP11Mode = 0x02;
        exP13Mode = 0x02;
    }

    SCON &= 0x3f;
    SCON |= 0x40;
    SFR91 &= 0xf8u;
    SFR91 |= 0x04;
    SCON |= 0x10;
    exUart2Con &= 0xf8u;
    PCON |= 0x80;
    exUart2Baud = 0xc8feu;
    exUart2Con |= 0x80;
    exP20Mode = 2;
    exP21Mode = 2;   
}

void uartGetPending(void)
{
    if(!uartPending)
    {
        if(EXA1 & 1)
        {
            uartPendingByte = EXA2;
            btInUse=0;
        }
        else
        if((SCON & 1) && BT_ON)
        {
            uartPendingByte = SBUF;
            btInUse=1;
        }
        else
            return;
        uartPending = 1;
        dualWatchStartTimer=2;
        powerSaveSuspend = 60;
    }       
}

void uartSendByte(const u8 byt)
{
    uartGetPending();
    //if(uartPending)
    //    uartTick();
    if(btInUse)
    {
        SBUF = byt;
        while( (SCON & 2) == 0) { }
        SCON &= 0xfd;
    }
    else
    {
        EXA2 = byt;
        while( (EXA1 & 2) == 0) { }
        EXA1 &= 0xfd;
    }
}

void uartRemoteKey(const u8 byt)
{
    externalKey = byt<0x93 ? byt&0x7f : KEY_NONE;
}

void uartSendNull(void)
{
    uartSendByte(0);
    uartSendByte(0);
}

void uartIdle(const u8 byt)
{
    if(byt&0x80)
    {
        if(remoteActive)
        {
            uartRemoteKey(byt);
            //externalKey = byt<0x93 ? byt&0x7f : KEY_NONE;
            remoteDisableTimer = 10;
        }
    }
    else
    switch(byt)
    {
        case 0x49: // reboot
            while(1) {}//__asm LJMP 0 __endasm;
        case 0x43: // report ignores
            uartSendByte(byt);
            {
                u8 i;
                for(i=0; i!=200; i++)
                {
                    uartSendByte(((u8*)scanIgnores)[i]);
                }
            }
            break;      
        case 0x4c: // remote key   
        case 0x30: // read eeprom
        case 0x31: // write eeprom
        case 0xAA: // AA sig for vfo state
            uartState = byt;        
            break;
        //case 0: // remote heartbeat
        //    if(remoteActive)
        //        remoteDisableTimer = 10;
        //    break;
        case 1:case 2: // pings
            goto SENDACK;
        case 0x45: // disable radio
            inputMode |= INPUTMODE_SERIAL;
            bkSet30(0);
            goto SENDACK;
        case 0x46: // enable radio
            inputMode &= ~INPUTMODE_SERIAL;
            squelchOpen = 0;
            bkAfDacOff();
            goto SENDACK;
        case 0x4a: // remote on
            externalKey = KEY_NONE;
            remoteDisableTimer = 10;
            remoteActive = 1;
            uartSendByte(byt);
            delay(100);
            //uartSendByte(105);
            //uartSendByte(SMETER_DPTT_YPOS);
            break;
        case 0x4b: // remote off
            externalKey = KEY_NONE;
            remoteDisableTimer = 0;
            remoteActive = 0;
            SENDACK:
            uartSendByte(byt);
            break;
    }
}

void uartProcessByte(u8 byt)
{
    u8 i;
    switch(uartState)
    {
        case 0: // idle
            uartIdle(byt);
            return;     
        case 0xAA:
            if(byt==0x60) {
                uartSendByte(0xAA);
                uartSendByte(squelchOpen?0x61:0x60);
                for(i=0; i!=32; i++) {
                    uartSendByte( ((u8*)&ACTIVE_VFO)[i] );
                }
                uartSendByte(bkReg[0x67].bytes.hi);
                uartSendByte(bkReg[0x67].bytes.lo);
                uartSendByte(bkReg[0x65].bytes.lo);                
            }
            break;
        case 0x30: { // read eeprom
            uartSendByte(0x30);
            uartAddr = ((u16)byt)<<5;
            eepromRead(uartAddr, eepromReadBuffer, 32);
            uartCS = 0;
            for(i=0; i!=32; i++)
            {
                const u8 b = eepromReadBuffer[i];
                uartSendByte(b);
                uartCS+=b;
            }
            uartSendByte(uartCS);
            //uartIdleState();
            break; }
        case 0x31: // write eeprom
            uartAddr = ((u16)byt)<<5;
            uartCS = 0;
            uartState++;
            uartCnt = 0;
            return;
        case 0x32: // write eeprom data stream
            eepromWriteBuffer[uartCnt++]=byt;
            uartCS+=byt;
            if(uartCnt==32)
                uartState++;
            return;
        case 0x33: // write eeprom checksum
            if(byt == uartCS)
            {
                eepromWrite(uartAddr, eepromWriteBuffer, 32);
                uartSendByte(0x31);
            }
            //uartIdleState();
            break;
        case 0x4c: // remote key
            uartState = (byt==0x4d ? byt : 0);
            return;
        case 0x4d: // remote key confirm
            uartRemoteKey(byt);
            //externalKey = byt<0x93 ? byt&0x7f : KEY_NONE;
            //uartIdleState();
            break;
    }
    uartIdleState();
}

void uartIdleState(void)
{
    uartState=0;
}

void uartRead(void)
{
    u16 to = 0;
    while(1)
    {
        feedTheDog();
        uartGetPending();
        if(uartPending)
        {
            EA=0;
            to = 20000;
            uartPending = 0;
            if(btInUse)
                SCON &= 0xfe;
            else
                EXA1 &= 0xfe;
            uartProcessByte(uartPendingByte);
            if(!uartState)
                break;
        }
        else
        {
            if(!to)
                break;
        }
        to--;
    }
    EA=1;
    uartIdleState();
}

void uartTick(void)
{
    uartRead();
}