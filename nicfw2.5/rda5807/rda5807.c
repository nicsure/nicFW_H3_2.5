void fmtInit(const u8 r0Hi, const u8 r0Lo, const u8 single)
{
    i2cTarget=I2CFMRADIO;
    i2cDelay();
    i2cStart();
    i2cSend(0x20);   
    i2cSend(r0Hi);   
    i2cSend(r0Lo);
    if(single) i2cStop();
}

void fmtRead(void)
{    
    i2cTarget=I2CFMRADIO;
    i2cDelay();
    i2cStart();
    i2cSend(0x21);
    i2cTarget=I2CVOICE;
    i2cStart();
    i2cTarget=I2CFMRADIO;
    i2cRead((char*)&fmtRegBuffer, 12);
    i2cStop();
    i2cTarget=I2CVOICE;
    i2cStop();
}

void fmtSaveLast(channelInfo* vfo)
{
    settings.lastFmtFreq = vfo->rxFreq.value;
}

const planInfo* getFmtPlan(void)
{
    return &plans[fmtPlan];
}

const u8 testBeforeStart(const channelInfo* vfo)
{
    return vfo->rxFreq.value<getFmtPlan()->startFreq;
}

const u8 testPastEnd(const channelInfo* vfo)
{
    return vfo->rxFreq.value>=getFmtPlan()->endFreq;
}

void fmtEqualize(channelInfo* vfo)
{    
    if(testBeforeStart(vfo)) 
    {
        vfo->rxFreq.value = getFmtPlan()->endFreq;
        vfo->rxFreq.value--;
    }
    else
    if(testPastEnd(vfo))
    {
        vfo->rxFreq.value = getFmtPlan()->startFreq;
    }
    vfo->rxFreq.value /= 5000;
    vfo->rxFreq.value *= 5000;
    vfo->txFreq.value = vfo->rxFreq.value;    
}


void fmtSetFreq(const channelInfo* vfo)
{
    U32 freq;
    fmtEqualize((channelInfo*)vfo);
    fmtSaveLast((channelInfo*)vfo);
    freq.value = vfo->rxFreq.value;
    freq.value -= 7600000l;
    freq.value /= 5000;
    freq.words.lo <<= 6;
    freq.bytes.byte0 |= 0x1A;
    fmtInit(0xf2, 0xe9, 0);
    i2cSend(freq.bytes.byte1);
    i2cSend(freq.bytes.byte0);
    i2cStop();
}

void fmtMute(const bit mute)
{
    fmtInit(mute?0xb2:0xf2, 0xe9, 1);
    if(!mute) POW_2822=1;
}

void fmtStart(const u8 stealth)
{    
    u8 i;
    if(stealth)
    {
        if(!VFOX[!settings.activeVfo].isFmTuner)
        {
            return;
        }
    }
    fmtActive=!stealth;
    fmtStealth = stealth;
    fmtInit(0x92, 0xe1, 1);
    fmtInit(0xd2, 0xe1, 1);
    fmtInit(0x00, 0x02, 1);
    fmtInit(0x92, 0xe1, 0);
    for(i=0; i<70; i++)
        i2cSend(rdaInit[i]);
    i2cStop();
    if(stealth)
    {
        fmtSetFreq(&VFO[!settings.activeVfo]);
    }
    else
    {
        if(settings.squelch)
            fmtMute(1);
    }
}

void fmtDisable(void)
{
    fmtActive=0;
    fmtInit(0,0,1);
    if(!fmtStealth) {
        displayDrawMeter(0, 3);
    }
    fmtStealth = 0;
}

void fmtTick(void)
{
    POW_2822 = 1;
    fmtRead();
    //RXA_LED = fmtRegBuffer.bytes[2]&0x1;

    radioSetLED(RXALED, fmtRegBuffer.bytes[2]&0x1); // led lag
    displayDrawMeter( fmtRegBuffer.bytes[2]>>1 , 2);

    if(settings.squelch)
        fmtMute(!RXA_LED);
}