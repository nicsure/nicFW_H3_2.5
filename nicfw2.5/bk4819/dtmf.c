
void dtmfPlay(const u8 digit)
{
    bkPlayTone(dtmfTableA[digit], dtmfTableB[digit]);
}

const u8 dtmfExtractDigit(const dtmfSequence* sequence, const u8 position)
{
    u8 byt = ((u8*)sequence)[position>>1];
    if(position&1) byt>>=4;
    return byt & 0xf;
}

void dtmfReplaceDigit(const dtmfSequence* sequence, const u8 position, const u8 newDigit)
{
    u8* bytePointer = &(((u8*)sequence)[position>>1]);
    if(position&1)
    {
        *bytePointer &= 0xf;
        *bytePointer |= newDigit<<4;
    }
    else
    {
        *bytePointer &= 0xf0;
        *bytePointer |= newDigit;
    }
}

void dtmfSearchPresets(void)
{
    u8 i, vpos;
    for(i=0; i!=20; i++) {
        dtmfGetPresetSeq(i);
        if(!manualSeq.first.length) { continue; }
        dtmfSeqToString(&manualSeq, 0, TXTEDIT);  
        if(strcontains((char*)dtmfDigitBuffer, TXTEDIT)) {
            memFill(dtmfDigitBuffer, 11, 32);
            lcdFill(0, flagsYPOS(), 128, 8, COL_FWBGROUND); 
            dtmfDisplayTime = 0;
            displayRefreshGeneral();        
            dtmfGetPresetName(i);
            vpos = displayVfoPos(settings.activeVfo);            
            COL_BGROUND.value = colVfo();
            lcdFill(VFO_CH_NAMEX,vpos,LARGE_CH_NAME?128-VFO_CH_NAMEX:96,16, COL_BGROUND );
            //void fontDraw8x8 (char* text, const u8 x, const u8 y, const COLOR col, const bit ds)
            fontDraw8x8(TXT, VFO_CH_NAMEX, vpos+DIS(VFO_CH_NAMEY), COL_VFOCHNAME, LARGE_CH_NAME?1:0);
            //if(LARGE_CH_NAME) {
            //    fontDraw8x8(TXT, VFO_CH_NAMEX, vpos+DIS(VFO_CH_NAMEY), COL_VFOCHNAME, 1);
            //} else {
            //    fontDraw8x8(TXT, VFO_CH_NAMEX, vpos+DIS(VFO_CH_NAMEY), COL_VFOCHNAME, 0);
            //}
            COL_BGROUND.value = COL_FWBGROUND.value;
            return;
        }
    }    
}

void dtmfAddDetectedDigit(const u8 digit)
{
    u8 i;
    for(i = 1; i<11; i++) {
        dtmfDigitBuffer[i-1] = dtmfDigitBuffer[i];
    }
    dtmfDigitBuffer[10] = digit;
    dtmfDisplayTime = 7;
    displayRefreshGeneral();
}

// we don't actually use the IRQ of the BK4819 as an interrupt trigger because hardware does not utilize it but we can poll the IRQ
u8 dtmfDetect(void) {
    if(bkGetReg(0x0c)->bytes.lo & 1) { // bit 1 of reg0c is IRQ
        bkSetReg(2,0); // acknowledge IRQ (clears all pending bits)
        if(bkGetReg(0x02)->bytes.hi & 0x08) { // check dtmf interrupt flag (BK4819) note: reg 0x02 has different roles for read and write
            return bkGetReg(0x0B)->bytes.hi & 0x0F; // read and return the digit being heard (BK4819)     
        }
    }
    return 0xFF; // return 0xff (essentially -1) to indicate no new DTMF tone detected
}

void dtmfSeqToString(const dtmfSequence* sequence, const char fill, char *target)
{
    u8 i;
    u8 len;
    len = dtmfExtractDigit(sequence, 0);
    if(len>9) len = 0;
    memFill(target, 9, fill);
    target[9] = 0;

    for(i=0; i!=len; i++)
    {
        u8* digitPointer = &target[i];
        const u8 digit = dtmfExtractDigit(sequence, i+1);
        if(digit<10) *digitPointer = digit+48; else
        if(digit==14) *digitPointer = '*'; else
        if(digit==15) *digitPointer = '#'; else
            *digitPointer = digit+55;
    }
}

const u16 dtmfGetSpeed(void)
{
    return (((u16)(20-settings.dtmfSpeed))<<5)+100;
}

void dtmfSeqFromString(void)
{
    u8* digitPointer;
    u8 i;
    u8 digit;
    i = 0;
    for(; 1; i++)
    {
        digitPointer = &TXTEDIT[i];        
        if(*digitPointer>='0' && *digitPointer<='9') digit=*digitPointer-48; else
        if(*digitPointer>='A' && *digitPointer<='D') digit=*digitPointer-55; else
        if(*digitPointer=='*') digit=14; else
        if(*digitPointer=='#') digit=15; else break;
        dtmfReplaceDigit(&manualSeq, i+1, digit);
        if(i==9) break;      
    }
    dtmfReplaceDigit(&manualSeq, 0, i);
}

const u16 dtmfPresetSeqAddress(const u8 seqNum)
{
    return 0x1cf0 + ((u16)seqNum * 12);
}

const u16 dtmfPresetNameAddress(const u8 seqNum)
{
    return dtmfPresetSeqAddress(seqNum) + 5;
}

void dtmfGetPresetName(const u8 seqNum)
{
    eepromRead(dtmfPresetNameAddress(seqNum), TXT, 7);
    TXT[8]=0;
}

void dtmfGetPresetSeq(const u8 seqNum)
{
    eepromRead(dtmfPresetSeqAddress(seqNum), (u8*)&manualSeq, 5);
}

const u8 dtmfSeek(u8 dir)
{
    u8 i;
    for(i=0; i!=20; i++)
    {
        lastDtmfPreset+=dir;
        if(dir==0) dir=1;
        if(lastDtmfPreset==20) lastDtmfPreset=0;
        if(lastDtmfPreset==0xff) lastDtmfPreset=19;
        dtmfGetPresetSeq(lastDtmfPreset);
        if(manualSeq.first.length && manualSeq.first.length<10)
        {
            dtmfGetPresetName(lastDtmfPreset);
            return 1;
        }
    }
    return 0;
}

void dtmfPlaySeq(const dtmfSequence* sequence, const u8 id)
{
    u8 len;
    u8 i;
    EA=0;
    len = dtmfExtractDigit(sequence, 0);
    if(!len || len>9) return;
    if(id)
    {
        delay(200);
    }
    else
    for(i=0; i!=4; i++)
    {
        delay(500);
        feedTheDog();
    }
    for(i=0; i!=len; i++)
    {
        dtmfPlay(dtmfExtractDigit(sequence, i+1));
        delay(id?120:dtmfGetSpeed());
        feedTheDog();
        bkStopTone();
        delay(id?60:(dtmfGetSpeed()>>1));
        feedTheDog();
    }
    EA=1;
}

void dtmfPlayPTTID(void)
{
    dtmfSequence tempSeq;
    tempSeq = manualSeq;
    dtmfGetPresetSeq(19);
    dtmfPlaySeq(&manualSeq, 1);
    manualSeq = tempSeq;
}

