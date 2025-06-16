
void bkSendByte(u8 byt)
{
    u8 i;
    for(i = 8; i != 0; i--)
    {
        SCK4819 = 0;
        delayL5();
        SDA4819 = (byt & 0x80) ? 1 : 0;
        delayL5();
        SCK4819 = 1;
        delayL5();
        byt <<= 1;
    }
}

const u8 bkGetByte(void)
{
    u8 r = 0;
    u8 i;
    for(i = 128; i != 0; i >>= 1)
    {
        SCK4819 = 1;
        delayL5();
        if(SDA4819) r |= i;
        SCK4819 = 0;
        delayL5();
    }
    return r;
}

U16* bkGetReg(const u8 reg)
{
    SCN4819 = 0;
    delayL5();
    bkSendByte(reg|0x80);
    SCK4819 = 0;
    SDA4819 = 0;
    P5CON = 0xf9;
    SDA4819 = 1;
    delayL5();
    bkReg[reg].bytes.hi = bkGetByte();
    bkReg[reg].bytes.lo = bkGetByte();
    SCN4819 = 1;
    P5CON = 0xfd;
    delayL5();
    return &bkReg[reg];
}

void bkSetReg(const u8 reg, const u16 val)
{
    SCN4819 = 0;
    delayL5();
    bkSendByte(reg);
    bkSendByte(C16(val)->bytes.hi);
    bkSendByte(C16(val)->bytes.lo);
    SCK4819 = 0;
    delayL5();
    SDA4819 = 0;
    SCN4819 = 1;
    delayL5();
    bkReg[reg].value = val;
}

void bkAndReg(const u8 reg, const u16 and)
{
    bkSetReg(reg, bkGetReg(reg)->value & and);
}

void bkOrReg(const u8 reg, const u16 or)
{
    bkSetReg(reg, bkGetReg(reg)->value | or);
}

void bkSendSeq(const u8* sequence)
{
    u8 cnt = 0, reg;
    U16 val;
    while(1)
    {
        feedTheDog();
        reg = sequence[cnt++];
        switch(reg)
        {
            case 0xff:
                return;
            case 0xfe:
                delay(sequence[cnt++] * 10);
                break;
            default:
                val.bytes.hi = sequence[cnt++];
                val.bytes.lo = sequence[cnt++];
                bkSetReg(reg, val.value);
                break;
        }
    }
}

void bkSet30(const u16 reg30)
{
    bkSetReg(0x30, reg30);
}

void bkAfDacOn(void)
{
    bkSet30(0xBFF1); 
}

void bkAfDacOff(void)
{
    bkSet30(0xBDF1); 
}

void bkSetFreqRegs(s32 freq)
{
    if(!(freq%2600000))
        freq+=1000;
    freq += ((freq >> 17) * (s32)tuning.xtal671) >> 9;
    bkSetReg(0x39, C32(freq)->words.hi);
    bkSetReg(0x38, C32(freq)->words.lo); 
}

void bkSetFreq(const u32* freq)
{
    bkSet30(0);
    bkSetFreqRegs(*freq);    
    if(squelchOpen)
        bkAfDacOn();
    else
        bkAfDacOff();
}

void bkSetGain(const u8 gainSetting)
{    
    //const bit agc = !gainSetting;
    //const u16 gain = gainTable[gainSetting];
    //bkSetReg(0x13, agc?0x03be:gain);
    //bkSetReg(0x12, agc?0x037b:gain);
    //bkSetReg(0x11, agc?0x027b:gain);
    //bkSetReg(0x10, agc?0x007a:gain);
    bkSetReg(0x10, gainTable[gainSetting ? gainSetting : settings.gain0]);    
    bkSetReg(0x11, gainTable[gainSetting ? gainSetting : settings.gain1]);
    bkSetReg(0x12, gainTable[gainSetting ? gainSetting : settings.gain2]);
    bkSetReg(0x13, gainTable[gainSetting ? gainSetting : settings.gain3]);
    bkSetReg(0x14, gainSetting ? gainTable[gainSetting] : 0x19);
}

void bkSetBandwidth(const bit narrow)
{
    //bkSetReg(0x43, rx ? (narrow?0x4408:0x45a8) : (narrow?0x0040:0x0020));
    bkSetReg(0x43, currentModulation==2?0x0028:(narrow?0x4048:0x3028));
}

void bkSetTxDeviation(u16 deviation, const bit narrow)
{
    deviation*=19;
    if(narrow) deviation--;
    deviation|=0x3000;
    bkSetReg(0x40, deviation);    
}

const u16 bkGetRssi(void)
{
    U16* reg = bkGetReg(0x67);
    reg->bytes.hi &= 1;
    return reg->value;
}

const u8 bkGetExNoise(void)
{
    U16* reg = bkGetReg(0x65);
    reg->bytes.hi = 0;
    reg->bytes.lo &= 0x7f;
    return reg->bytes.lo;
}

void bkSetMicGain(const u8 micGain)
{
    bkSetReg(0x7d, 0xe940 | micGain);  
}

void bkSetRxExpanderAndVox(const u8 exp, const u8 vox)
{
    if(vox)
    {
        u8 v = 16-vox;
        bkTemp.bytes.hi = 0xa0;
        bkTemp.bytes.lo = 0x08 * v;
        bkSetReg(0x46, bkTemp.value);
        bkTemp.bytes.hi = 0x18;
        bkTemp.bytes.lo = 0x04 * v;        
        bkSetReg(0x79, bkTemp.value);
    }
    bkTemp.bytes.hi = 0;
    bkTemp.bytes.lo = (vox?4:0)|(exp?8:0)|(settings.scrambleFreq?2:0); 
    bkSetReg(0x31, bkTemp.value);
    bkTemp.bytes.hi = 0x2b | (exp<<6);
    bkTemp.bytes.lo = 0x38;
    bkSetReg(0x28, bkTemp.value);
    if(settings.scrambleFreq) {
        bkSetReg(0x71, 25812 + ((u16)settings.scrambleFreq * (u16)1032));    
    }    
}

void bkSetAfFilters(const u8 aff)
{
    bkTemp.bytes.hi = aff==8?7:aff;
    bkTemp.bytes.lo = aff==8?7:0;
    bkSetReg(0x2b, bkTemp.value); 
}

void bkSetModulation(const u8 mod, const  bit remember)
{
    if(remember)
        currentModulation = mod;
    bkTemp.bytes.lo = 0x40;
    switch(mod)
    {
        default: bkTemp.bytes.hi = 0x60; break; // mute
        case 1: bkTemp.bytes.hi = 0x61; break; // fm
        case 2: bkTemp.bytes.hi = 0x67; break;// am    
        case 3: bkTemp.bytes.hi = 0x65; break;// usb
        case 4: bkTemp.bytes.hi = 0x63; break;// tones
    }
    bkSetReg(0x47, bkTemp.value); 
}

void bkInit(void)
{
    bkSendSeq(bkInitSeq);
}

void bkApplyActiveVfo(void)
{
    bkApplyVfo(settings.activeVfo);
}

void bkApplyVfo(const u8 vfoPosition)
{
    channelInfo* vfo;
    channelXtra* vfox;
    appliedVfo = vfoPosition;
    vfo = &(VFO[vfoPosition]);
    vfox = &(VFOX[vfoPosition]);
    //if(isFmtFreq(&(vfo->rxFreq))) //  vfo->rxFreq.bytes.byte2>0x73 && vfo->rxFreq.bytes.byte2<0xA5 && vfo->rxFreq.bytes.byte3==0)
    if(!settings.disableFmt && plans[vfox->rxplan].bits.bandwidth==5)
    {
        bkSet30(0);
        bkSetFreqRegs(deadFreq);
        bkSetGain(1);
        squelchOpen=0;
        if(!fmtActive)
            displayVfoRefresh(vfoPosition, 1);
        POW_2822 = 1;
        fmtStart(0);
        fmtSetFreq(vfo);
        vfox->isFmTuner=1;
        return;
    }
    else
    {
        if(vfoPosition == settings.activeVfo && fmtActive)
            fmtDisable();
        vfox->isFmTuner=0;
    }
    bkSendSeq(bkReceiveSeq);    
    //bkSetBandwidth(vfox->rxBandwidth, 1);
    bkSetBandwidth(vfox->rxBandwidth);
    bkSetModulation(vfox->modulation, 1);
    bkSetAfFilters(settings.afFilters);
    radioSetFilters(1, vfox->rxIsVhf);
    bkSetRxExpanderAndVox(0, settings.vox);
    bkSetGain(settings.rfGain);
    if(vfox->modulation == 1) // FM
    {
        bkAndReg(0x73, 0xc7ef); // clear bit 4, enable AFC
        bkOrReg(0x73, 0x3800); // set min range
    }
    else // AM, USB
        bkOrReg(0x73, 0x0010); // set bit 4, disable AFC
    //bkSetReg(0x3D, vfox->modulation==3 ? 0x0000:0x2AAB); // gain
    bkSetReg(0x3D, vfox->modulation==3 ? 0x0000:ifTable[settings.ifFreq]); // gain
    bkSetReg(0x4A, vfox->modulation==2 ? 0x5448:0x5450);
    stSetTone(vfo->rxSubTone.value);
    //bkSetReg(0x07, 0x21CE);
    bkSetReg(0x37, 0x1F0F);
    rssiGetFloor(&(vfo->rxFreq.value));
    bkSetFreq(&(vfo->rxFreq.value));
}

void bkToneFreq(const u16 fr, const bit channel)
{
    bkTone[channel].value = (u32)fr;
    bkTone[channel].value *= 103244l;
    bkTone[channel].value += 5000l;
    bkTone[channel].value /= 10000l;
    //bkSetReg(0x71+channel, bkTone[channel].words.lo); 
}

u16 xdata r71;

void bkPlayTone(const u16 lefthz, const u16 righthz)
{    
    r71 = bkReg[0x71].value;
    tonePlaying = 1;
    bkSetModulation(4, 1);
    delay(5);
    POW_2822 = 0;
    bkToneFreq(lefthz, 1);
    bkToneFreq(righthz, 0);
    bkSetReg(0x71, bkTone[0].words.lo); 
    bkSetReg(0x72, bkTone[1].words.lo); 
    bkSetReg(0x70, settings.dtmfDev | (((u16)settings.dtmfDev*180)&0x7f00) | 0x8080);
    bkSetReg(0x30, 0xc3fa);
    delay(5);
    POW_2822 = 1;
}

void bkStopTone(void)
{
    tonePlaying = 0;
    bkSetModulation(0, 1);
    delay(5);
    POW_2822 = 0;
    delay(5);
    bkToneFreq(0,0);
    bkToneFreq(0,1);
    bkSetReg(0x70, 0);
    bkSetReg(0x71, r71);
    bkSetReg(0x30, 0xc1fe); 
}

const u8 bkSubToneDetected(void)
{
    return bkGetReg(0x0c)->bytes.hi & 0x44;
}

const u8 bk55Detected(void)
{
    return bkGetReg(0x0c)->bytes.hi & 0x08;
}


void bkInitXmit(void)
{
    u8 i;
    //RXB_LED = 0;
    //RXA_LED = 0;
    radioSetLED(RXBLED | RXALED, 0);
    //if(settings.activeVfo)
    //    TXB_LED=1;
    //else
    //    TXA_LED=1;
    radioSetLED(settings.activeVfo ? TXBLED : TXALED, 1);

    xmitActive=1;
    txTimer = settings.txTimeout;
    squelchOpen=0;
    if(!wlCloneTrigger)
        displayVfo(settings.activeVfo, 1);
    displayDrawMeter(ACTIVE_VFOX.txPower, 1);
    displayDrawExNoise(0, 1);
    radioClearFilters();
    POW_2822=0;
    delay(5);
    bkSendSeq(transSeq);
    bkSetRxExpanderAndVox(0, settings.vox);
    //bkSetBandwidth(ACTIVE_VFOX.txBandwidth, 0);
    bkSetBandwidth(ACTIVE_VFOX.txBandwidth);
    bkSetMicGain(settings.micGain);
    bkSetTxDeviation(settings.txDeviation, ACTIVE_VFOX.txBandwidth);
    stSetTone(ACTIVE_VFO.txSubTone.value);
    bkSetFreqRegs(ACTIVE_VFO.txFreq.value);
    actualPower = ACTIVE_VFOX.txPower-1;
    if(actualPower)
    {
        radioSetFilters(0, ACTIVE_VFOX.txIsVhf);
        pwmSetPa(1);
    }
    delay(10);
    bkSet30(0xC1FE);        
    bkSetReg(0x50, 0x3B20);
    delay(5);    
    for(i=2; i<actualPower; i++)
    {
        delay(1);
        pwmSetPa(i);
    }
    if(ACTIVE_VFO.bits.pttID&1)
    {
        dtmfPlayPTTID();
    }
    if(playDtmfOnPTT)
    {
        if(ACTIVE_VFO.bits.pttID&1) {
            delay(1000);
        }        
        dtmfPlaySeq(&manualSeq, 0);
    }
    playDtmfOnPTT=0;
}

void bkEndXmit(void)
{
    u8 i;
    if(ACTIVE_VFO.bits.pttID&2)
    {
        dtmfPlayPTTID();
    }    
    if(settings.ste & 2)
    {
        stSetTone(550);
        delay(500);
        feedTheDog();
    }
    radioSetLED(TXALED | TXBLED, 0);

    for(i=actualPower; i!=0xff; i--)
    {
        delay(1);
        pwmSetPa(i);
    }
    pwmSetPa(0);
    bkSet30(0);
    radioClearFilters();
    xmitActive=0;
    displayVfo(settings.activeVfo, 1);
    displayDrawMeter(0, 3);
    displayDrawExNoise(0, 0); 
    bkApplyActiveVfo();
}

void bkXmitTick(void)
{
    u8 key;
    if(settings.txModMeter)
    {
        u8 modLevel = bkGetReg(0x6f)->bytes.lo & 0x7f;
        modLevel = modLevel > 55 ? modLevel - 55 : 0;
        modLevel = modLevel < 40 ? modLevel*3 : 120;
        displayDrawExNoise(modLevel, 1);         
    }
    key = keypadPressed;

    if(tonePlaying)
    {
        if(key==KEY_NONE)
            bkStopTone();
    }
    else
    {
        if(key<16)
            dtmfPlay(key);
        else
        if(key==KEY_FLSH)
            bkPlayTone(settings.repeaterTone, 0);        
    }
}

void bkResetAgcTables(void)
{
    settings.gain0 = 24;
    settings.gain1 = 32;
    settings.gain2 = 37;
    settings.gain3 = 40;
}

void bkAmAgc(void) 
{
    if(currentModulation==2 && settings.amAgc && !settings.rfGain)
    {
        u16 rssi;
        rssi = bkGetRssi();
        if(rssi > 206) {
            amGain=15;
        }
        else
        if(!squelchOpen && amGain!=40) {
            amGain=40;
        }
        else
            return;
        bkSetGain(amGain);
    }
}


