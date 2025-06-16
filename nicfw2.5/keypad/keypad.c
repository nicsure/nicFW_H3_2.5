void keypadDelay(void)
{
    u8 d = 16;
    while(d-- != 0) { }
}

const u8 keypadScanCol1(void)
{
    u8 k = KEY_NONE;
    if(KEY_L1)
    {
        KEY_R1 = 0;
        keypadDelay();
        if(!KEY_L1) k = KEY_EXIT;
        KEY_R1 = 1;
        KEY_R3 = 0;
        keypadDelay();
        if(!KEY_L1) k = KEY_3;
        KEY_R3 = 1;
        KEY_R4 = 0;
        keypadDelay();
        if(!KEY_L1) k = KEY_6;
        KEY_R4 = 1;
        KEY_R5 = 0;
        keypadDelay();
        if(!KEY_L1) k = KEY_9;
        KEY_R5 = 1;
        KEY_R6 = 0;
        keypadDelay();
        if(!KEY_L1) k = KEY_HASH;
        KEY_R6 = 1;
    }
    else
    {
        P0CON = 0xfe;    
        keypadDelay();
        if(!KEY_R4) k = KEY_6;
        P0CON = 0xfd;    
        keypadDelay();
        if(!KEY_R3) k = KEY_3;
        P0CON = 0xf7;    
        keypadDelay();
        if(!KEY_R1) k = KEY_EXIT;
        P0CON = 0xff;
        P2CON = 0x46;
        keypadDelay();
        if(!KEY_R5) k = KEY_9;
        P2CON = 0x86;
        if(!KEY_R6) k = KEY_HASH;
        P2CON = 0xc6;     
    }
    return k;
}

const u8 keypadScanCol2(u8 k)
{
    if(KEY_L2)
    {
        KEY_R1 = 0;
        keypadDelay();
        if(!KEY_L2) k = KEY_UP;
        KEY_R1 = 1;
        KEY_R2 = 0;
        keypadDelay();
        if(!KEY_L2) k = KEY_DOWN;
        KEY_R2 = 1;
        KEY_R3 = 0;
        keypadDelay();
        if(!KEY_L2) k = KEY_2;
        KEY_R3 = 1;
        KEY_R4 = 0;
        keypadDelay();
        if(!KEY_L2) k = KEY_5;
        KEY_R4 = 1;
        KEY_R5 = 0;
        keypadDelay();
        if(!KEY_L2) k = KEY_8;
        KEY_R5 = 1;
        KEY_R6 = 0;
        keypadDelay();
        if(!KEY_L2) k = KEY_0;
        KEY_R6 = 1;
    }
    else
    {
        P0CON = 0xfe;    
        keypadDelay();
        if(!KEY_R4) k = KEY_5;
        P0CON = 0xfd;    
        keypadDelay();
        if(!KEY_R3) k = KEY_2;
        P0CON = 0xfb;    
        keypadDelay();
        if(!KEY_R2) k = KEY_DOWN;
        P0CON = 0xf7;    
        keypadDelay();
        if(!KEY_R1) k = KEY_UP;
        P0CON = 0xff;
        P2CON = 0x46;
        keypadDelay();
        if(!KEY_R5) k = KEY_8;
        P2CON = 0x86;
        if(!KEY_R6) k = KEY_0;
        P2CON = 0xc6;     
    }
    return k; 
}

const u8 keypadScanCol3(u8 k)
{
    if(!KEY_L3) return KEY_NONE;
    KEY_R1 = 0;
    keypadDelay();
    if(!KEY_L3) k = KEY_MENU;
    KEY_R1 = 1;
    KEY_R3 = 0;
    keypadDelay();
    if(!KEY_L3) k = KEY_1;
    KEY_R3 = 1;
    KEY_R4 = 0;
    keypadDelay();
    if(!KEY_L3) k = KEY_4;
    KEY_R4 = 1;
    KEY_R5 = 0;
    keypadDelay();
    if(!KEY_L3) k = KEY_7;
    KEY_R5 = 1;
    KEY_R6 = 0;
    keypadDelay();
    if(!KEY_L3) k = KEY_STAR;
    KEY_R6 = 1;
    return k; 
}

const u8 keypadPTT(void)
{
    return keypadPTTA() || keypadPTTB() || keypadPTTE();
}

const u8 keypadPTTA(void)
{
    return keyTank[KEY_PTTA].latch;
}

const u8 keypadPTTB(void)
{
    return keyTank[KEY_PTTB].latch;
}

const u8 keypadPTTE(void)
{
    return keyTank[KEY_PTTE].latch;
}

void keypadKeyState(const u8 key, const u8 on, const u8 ticks)
{
    if(on)
    {
        voxIgnore = 10;
        keyTank[key].tank+=ticks;
        if(keyTank[key].tank>5)
            keyTank[key].tank=6;
    }
    else
    {
        if(keyTank[key].tank>ticks)
            keyTank[key].tank-=ticks;
        else
            keyTank[key].tank=0;
    }
    if(keyTank[key].latch)
    {
        if(!keyTank[key].tank)
        {
            keyTank[key].latch=0;
            if(key<KEY_PTTA || key==KEY_FLSH)
            {                
                if(keypadPressed!=KEY_NONE && longPress==KEY_NONE)
                {
                    if(KEY_LED && (!settings.keyLock || enteringPin || key==KEY_FLSH))
                        singlePress = keypadPressed;
                    lcdBacklight(1);
                }
                keypadPressed = KEY_NONE;
            }
        }
    }
    else
    {
        if(key==KEY_PTTE)
        {
            if(keyTank[key].tank>1)
                xSwap = 1;
            else
            if(keyTank[key].tank==0)
            {
                if(xSwap)
                {
                    radioSwapVfo();
                    bkApplyActiveVfo();
                }
                xSwap = 0;
            }
        }
        if(keyTank[key].tank==6)
        {
            xSwap = 0;
            keyTank[key].latch=1;
            anyKeyInUse=1;
            if(key<KEY_PTTA || key==KEY_FLSH)
            {
                keypadPressed = key;
            }
            else
                lcdBacklight(1);
        }
    }
}

void differentialKeyTone(const u8 duration, const u8 key)
{
    if((duration==12 || settings.keyTones) && key!=KEY_NONE)
    {
        
        if(settings.keyTones==3 && key<10 && !fmtActive && duration!=10)
            voicePlay(key, 0);
        else
        {
            soundBeep(duration, (settings.keyTones==1) ? 100 : ((15-key)<<3)+100);
        }
    }
}

const u8 keypadSinglePress(void)
{
    u8 key;
    differentialKeyTone(3, singlePress);
    key = singlePress;
    singlePress = KEY_NONE;
    return key;
}

void keypadTick(const u8 ticks)
{   
    u8 i, k; 
    anyKeyInUse=0;
    if(keypadPressed!=KEY_NONE)
    {
        longPressTime+=ticks;
        if(longPressTime>49)
        {
            longPressTime = 50;
            if(longPress!=KEY_LONGACTIONED)
            {
                if(!settings.keyLock || lpActionTable[keypadPressed]==LP_KEYLOCK)
                {
                    if(longPress!=keypadPressed)
                        differentialKeyTone(10, keypadPressed);
                    longPress = keypadPressed;
                    lcdBacklight(1);
                }
            }
        }
    }
    else
    {
        longPressTime = 0;
        longPress = KEY_NONE;
    }

    //if(remoteActive && externalKey<0x13)
    //{
    //    keypadKeyState(externalKey, 1, ticks<<1);
    //}

    if(!settings.pinAction || !settings.keyLock)
    {
        keypadKeyState(KEY_PTTA, !KEY_L1 || externalKey==KEY_PTTA, ticks);
        keypadKeyState(KEY_PTTB, !KEY_L2 || externalKey==KEY_PTTB, ticks);
        keypadKeyState(KEY_FLSH, !KEY_L3 || externalKey==KEY_FLSH, ticks);
        keypadKeyState(KEY_PTTE, !PTT_EXT, ticks);
    }
    k = keypadScanCol3(keypadScanCol2(keypadScanCol1()));
    for(i = KEY_0; i != KEY_PTTA; i++)
    {
        keypadKeyState(i, i==k || i==externalKey, ticks);
    }
}