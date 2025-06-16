void fskChunk(void)
{
    u8 to;
    u8 i;
    to = 200;    
    while(--to != 0)
    {
        feedTheDog();        
        if(bkGetReg(0x0c)->bytes.lo & 1)
        {
            bkSetReg(0x02, 0);
            if(bkGetReg(0x02)->bytes.hi & 0x10)
            {
                for(i=0; i!=4; i++)
                {
                    fskBuffer.words[i] = (bkGetReg(0x5f)->value);                    
                }
                return;
            }
        }
        delay(10);
    }   
    fskBuffer.bytes[0] = 0x22;
}

u8 fskGetBlock(const u8 block)
{
    fskChunk();
    if( fskBuffer.words[0]==0x6789 &&
        fskBuffer.words[1]==0xabcd &&
        fskBuffer.bytes[4]==0xef &&
        fskBuffer.bytes[5]==block )
    {
        u16 pcs = fskBuffer.checksum.value;
        u16 cs = block;
        u8 i, j;
        for(i=0; i!=4; i++)
        {
            fskChunk();
            for(j=0; j!=8; j++)
            {
                fskBlockBuffer[(i<<3)+j] = fskBuffer.bytes[j];
                cs += (u16)fskBuffer.bytes[j] + 3;
                cs *= 19;
            }
        }
        return (pcs==cs) ? 1 : 0xff;
    }
    return 0;
}

void fskSendBlock(const u8 block)
{
    u8 i;
    u16* buffer;
    bkTemp.value = (u16)block;
    for(i=0; i<32; i++)
    {
        bkTemp.value += ((u16)fskBlockBuffer[i]) + 3;
        bkTemp.value *= 19;
    }
    bkSetReg(0x5f, 0x6789);
    bkSetReg(0x5f, 0xabcd);
    bkSetReg(0x5f, 0xef00 | block);
    bkSetReg(0x5f, bkTemp.value);
    buffer = (u16*)fskBlockBuffer;
    for(i=0; i<16; i++)
    {
        bkSetReg(0x5f, buffer[i]);
    }
}

void fskSendTail(void)
{
    delay(20);
    bkSetReg(0x59, 0x2868);
    while(1)
    {
        feedTheDog();
        bkGetReg(0x0c);
        if(bkGetReg(0x0c)->bytes.lo&1) break;
    }
    bkSetReg(0x02, 0x0008);
    delay(20);
    bkSetReg(0x3f, 0x0000);
    bkSetReg(0x59, 0x0068);
}

void printBlock(const u8 start, const COLOR col)
{
    SPRINT_NUMBER(TXT, start, 3, 255, 0, 1);
    fontDraw8x16(TXT, 4, 55, col);
}

void fskKeyHandler(void)
{
    delay(10);
    feedTheDog();
    uartTick();
    keypadTick(1);    
}

void fskStep(u8* start, const u8 step)
{
    *start+=step;
    *start&=0xFC;
    if(*start>238) *start=0;
    printBlock(*start, COL_MENU); 
}

void fskLedsOff(void)
{
    radioSetLED(RXALED | RXBLED | TXALED | TXBLED, 0); 
}

const bit fskCheckAbort(const u8 start)
{
    if(keypadScanCol1()==KEY_EXIT)
    {
        fskLedsOff();
        printBlock(start, COL_MENU); 
        while(keypadScanCol1()==KEY_EXIT)
        {
            feedTheDog();
        }
        return 1;
    }
    return 0;
}

void fskSetLockLED(const u8 send)
{
    radioSetLED(TXBLED | RXALED, !send);
    radioSetLED(TXALED | RXBLED, send);    
}

void fskWlClone(const u8 send)
{
    u8 start;
    u8* inputValue8;
    u8 blockInput;
    u8 activeKey;
    u8 i;
    POW_2822=0;
    bkAfDacOff();
    fskLedsOff();
    start = 0;
    lcdCls();        
    printBlock(start, COL_MENU);

    fontDraw8x8(WIRELESS, 4, 34, COL_MENU,0);
    fontDraw8x8(send?SEND:RECEIVE, 4, 42, COL_MENU,0);
    fontDraw8x8(START, 4, 82, COL_MENU,0);
    fontDraw8x8(STOPEXIT, 4, 92, COL_MENU,0);

    inputValue8 = (u8*)&inputValue;
    blockInput = 0;
    while(1)
    {
        while(1)
        {
            fskKeyHandler();
            activeKey = keypadSinglePress();
            if(!blockInput && activeKey<=KEY_9)
            {
                inputPrepare(3, 0, 4, 55, 2);
                inputParseKey(activeKey);
                blockInput=1;
            }
            if(blockInput)
            {
                while(blockInput)
                {
                    fskKeyHandler();
                    inputTick();
                    switch(inputState)
                    {
                        case INPUT_APPLIED:
                            start = *inputValue8 & 0xFC;
                            fskStep(&start, 0);
                        case INPUT_CANCELLED:
                            blockInput=0;
                            printBlock(start, COL_MENU);                
                            break;
                    }
                }
            }
            else
            {
                if(activeKey == KEY_EXIT)
                {
                    //timersReset();
                    inputMode=0;
                    inputState=0;
                    lcdCls();
                    displayRefreshFull();
                    return;
                }
                if(activeKey == KEY_MENU)
                    break;
                if(activeKey == KEY_UP)
                    fskStep(&start, 4);
                else
                if(activeKey == KEY_DOWN)
                    fskStep(&start, 0xFC);
            }
        }
        printBlock(start, COL_VFOTXFREQ);
        POW_2822=0;



        //TXA_LED=send;
        //TXB_LED=!send;
        //RXA_LED=!send;
        //RXB_LED=send;

        fskSetLockLED(send);

        if(send)
        {
            bkInitXmit();
            bkSetTxDeviation(64, 0);
            //bkSetBandwidth(1, 0);
            bkSetBandwidth(1);
            stSetTone(0);
            delay(500);
            feedTheDog();
            delay(500);
            feedTheDog();
            while(1)
            {
                if(fskCheckAbort(start))
                    break;
                bkSendSeq(fskInit1);
                bkSendSeq(fskInit3);
                for(i=0; i!=4; i++)
                {
                    eepromRead((u16)start << 5, fskBlockBuffer, 32);
                    fskSendBlock(start++);
                }
                fskSendTail();
                printBlock(start, COL_VFOTXFREQ);
                if(start>238) 
                {
                    start = 0;
                    break;
                }
            }
            delay(50);
            bkEndXmit();
            fskLedsOff();
            printBlock(start, COL_MENU);
        }
        else
        {
            bkSetModulation(1, 0);
            //bkSetBandwidth(1, 1);
            bkSetBandwidth(1);
            bkSendSeq(fskInit1);
            bkSendSeq(fskInit2);            
            while(1)
            {
                if(fskCheckAbort(start))
                {
                    start&=0xFC;
                    printBlock(start, COL_MENU);                    
                    break;
                }
                feedTheDog();
                switch(fskGetBlock(start))
                {
                    case 0:
                        break;
                    case 1:
                        eepromBurn((u16)start << 5, fskBlockBuffer);
                        if(++start>238) 
                        {
                            while(1) {}  //__asm   LJMP 0      __endasm;
                        }
                        printBlock(start, COL_VFOTXFREQ);
                        break;
                    case 0xff:
                        start&=0xFC;
                        printBlock(start, COL_ASLFLAG);
                        break;
                }
            }
            fskLedsOff();
        }
    }

}
