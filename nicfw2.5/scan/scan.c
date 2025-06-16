
void scanSetDirection(const u8 key)
{
    scanDirection = (key==KEY_UP)?1:0xff;
}

void scanTick(void)
{
    u8 key;
    key = keypadSinglePress();
    if(key==KEY_STAR || key==KEY_0)
    {
        if(ACTIVE_VFOSTATE.group)
            radioToggleVfoModeAndGroup(ACTIVE_VFOSTATE.mode, ACTIVE_VFOSTATE.group, 0, key==KEY_STAR?1:0xff);
    }
    else
    if(key==KEY_1)
    {
        scanActivityMode^=1;
        displayVfoRefreshActiveNoDrawBG();
    }
    else
    if(key==KEY_EXIT || keypadPTT())
    {
        scanStop();
    }
    else
    if(key==KEY_MENU)
    {
        menuInit();
    }
    else
    if(loopMode == LOOPMODE_SCANMONITOR)
    {        
        if(squelchOpen) scanningResume = (settings.scanPersist.bytes.lo)+2;
        if(!scanningResume)
        {
            updateTimer = settings.scanUpdate ? 1 : 0;
            loopMode=LOOPMODE_SCAN;
            if(fmtStealth) { fmtMute(0); }
            displayVfoRefreshActiveNoDrawBG();
        }
        if(settings.scanResume)
        {
            if(!scanningSkip)
                key = 0x99;
        }
        switch(key)
        {          
            default: return;
            case KEY_HASH:
                scanAddIgnore(&ACTIVE_VFO.rxFreq.value);
                goto SCANRESUME;
            case KEY_DOWN:                
            case KEY_UP:
                scanSetDirection(key);
            case 0x99:
                SCANRESUME:
                if(!fmtStealth)  { POW_2822=0; } else { fmtMute(0); }
                delay(5);
                bkSet30(0);
                bkSetFreqRegs(1000000l);
                squelchOpen=0;
                scanningResume=0;
                scanningSkip=0;
                break;
        }
    }
    else
    if(loopMode == LOOPMODE_SCAN)
    {
        switch(key)
        {
            case KEY_UP:
            case KEY_DOWN:
                scanSetDirection(key);
                break;
            case KEY_HASH:
                scanAddIgnore(&ACTIVE_VFO.rxFreq.value);
                break;
        }
        // RXA_LED = (scanningCount++)&32;
        radioSetLED(RXALED, (scanningCount++)&32);
        if(ACTIVE_VFOSTATE.mode)
            scanModeChannel();
        else
            scanModeVFO();
    }
    else
    if(loopMode == LOOPMODE_SCANFMT)
    {
        if(key==KEY_UP)
            fmtScanDown = 0;
        if(key==KEY_DOWN)
            fmtScanDown = 1;
        scanModeFMT();
    }

}

void scanStop(void)
{
    if(fmtStealth) {
        fmtDisable();
    }
    scanActivityMode = 0;
    voicePlay(VOICE_ID_SCANNING_STOP, 0);
    if(scanModSave)
    {
        ACTIVE_VFO.bits.modulation = 0;
        scanModSave=0;
        channelSaveActive();
    }
    loopMode = 0;
    if(ACTIVE_VFOSTATE.mode)
        channelLoad(ACTIVE_VFOX.number, settings.activeVfo);
    bkApplyActiveVfo();
    if(!ACTIVE_VFOSTATE.mode)
        displayRefreshFull();
}

void scanPrepare(void)
{
    step833Counter=1;
    if(!(ACTIVE_VFOSTATE.mode))
    {
        if(scanFreqStart==0)
            radioSetScanStartFreqToVfo();
        scanFreqEnd = scanFreqStart + ((u32)settings.scanRange * 1000l);
        if(scanFreq<scanFreqStart || scanFreq>scanFreqEnd)
            scanFreq = scanFreqStart;
        //if(settings.ultraScan)
        //    scanNormalize();
    }
}

void scanStart(void)
{
    if(settings.squelch)
    {
        if(!ACTIVE_VFOX.isFmTuner)
        {
            fmtStart(1);
            scanClearIgnores();
            scanActivityMode = 0;
            updateTimer = settings.scanUpdate ? 1 : 0;
            voicePlay(VOICE_ID_SCANNING_BEGIN, 0);
            //step833Counter=1;
            loopMode=LOOPMODE_SCAN;
            scanPrepare();
            ultraFloor = 0;
            usFloorCount = 0;
            usLowSig=255;
            //if(!(ACTIVE_VFOSTATE.mode))
            //{
            //    if(scanFreqStart==0)
            //        radioSetScanStartFreqToVfo();
            //    scanFreqEnd = scanFreqStart + ((u32)settings.scanRange * 1000l);
            //    if(scanFreq<scanFreqStart || scanFreq>scanFreqEnd)
            //        scanFreq = scanFreqStart;
            //    if(settings.ultraScan)
            //        scanNormalize();
            //}
            displayRefreshFull();
            return;
        }
        loopMode=LOOPMODE_SCANFMT;
    }
}


const bit scanTestSignal(void)
{
    u8 noise;
    u16 sig;
    delay(20);
    noise = bkGetExNoise();
    if( noise < (settings.sqNoiseLev - 8 ))
    {
        sig = rssiGetSignal();
        if( sig>(((u16)settings.squelch-1)*12)+2 )
        {
            return 1;
        }
    }
    return 0;    
}

const u8 scanDetect(void)
{
    u8 sig;
    if(scanCheckIgnores(&scanFreq))
    {
        radioSetFilters(1, isFreqVhf(&scanFreq, 1)); //(scanFreq/10000) < settings.rxSplit);
        if(!(ACTIVE_VFOSTATE.mode) && settings.ultraScan)
        {
            sig = scanUltra(&scanFreq);
            if(sig<usLowSig)
            {
                usLowSig = sig;
            }
            usFloorCount++;
            if(usFloorCount==32)
            {
                ultraFloor+=usLowSig;
                ultraFloor>>=1;            
                usFloorCount=0;
                usLowSig=255;
            }
            if(sig<ultraFloor+settings.ultraScan)
                return 0;

            //if(sig>ultraFloor)
            //{
            //    sig-=ultraFloor;
            //    if(sig<settings.ultraScan)
            //        return 0;
            //}
            //else
            //    return 0;
        }
        bkSet30(0);    
        bkSetFreqRegs(scanFreq);
        //bkSetBandwidth(ACTIVE_VFOX.rxBandwidth, 1);
        bkSetBandwidth(ACTIVE_VFOX.rxBandwidth);
        rssiGetFloor(&scanFreq);
        bkAfDacOff();
        return scanTestSignal();
    }
    return 0;
}


void scanAcknowledge(void)
{
    scanningResume=(settings.scanPersist.bytes.lo)+4;
    scanningSkip = settings.scanResume;
    loopMode = LOOPMODE_SCANMONITOR;
    if(fmtStealth) { fmtMute(1); }
}

void scanCheckMulti(void)
{
    u8 i;
    if(scanUsingMultiPresets())
    {
        for(i = 0; i!=20; i++)
        {
            scanPresetIndex++;
            if(scanPresetIndex>19) scanPresetIndex=0;
            if(scanMultiPreset[scanPresetIndex])
                break;
        }
        scanLoadPreset();
        scanApplyPreset();
        scanPrepare();
        displayVfoRefreshActiveNoDrawBG();
    }
}

void scanModeVFO(void)
{
    scanFreq+=step833(scanDirection);
    if(scanDirection == 1 && scanFreq>scanFreqEnd)
    {
        scanFreq=scanFreqStart;
        step833Counter=1;
        scanCheckMulti();
    }
    else
    if(scanDirection == 0xff && scanFreq<scanFreqStart)
    {
        scanFreq=scanFreqEnd;
        step833Counter=1;
        scanCheckMulti();
    }
    if(scanDetect())
    {
        rssiTick();
        if(squelchOpen)
        {
            scanAcknowledge();
            ACTIVE_VFO.rxFreq.value = scanFreq;
            ACTIVE_VFO.txFreq.value = scanFreq;
            displayVfoRefreshActiveNoDrawBG();
        }
    }
}

void scanModeChannel(void)
{
    const u8 group = ACTIVE_VFOSTATE.group;
    scanningChannel = channelValidateOrNext(scanningChannel, 1, group, 0);
    updateScanChannel = scanningChannel; // fix update error
    scanFreq = channelMap[scanningChannel];
    if(scanDetect())
    {
        scanAcknowledge();        
        channelLoad(scanningChannel, settings.activeVfo);
        if(plans[ACTIVE_VFOX.rxplan].bits.bandwidth!=5)
            bkApplyActiveVfo();
        else
        {
            bkSet30(0);
            scanningResume = 1;
        }
        delay(20);
    }
    scanningChannel++;
}

void scanModeFMT(void)
{
    if(ACTIVE_VFOSTATE.mode)
    {
        loopMode=0;
        return;
    }
    if(fmtScanDown)
        ACTIVE_VFO.rxFreq.value-=5000l;
    else
        ACTIVE_VFO.rxFreq.value+=5000l;
    fmtSetFreq(&ACTIVE_VFO);
    displayVfoRefreshActiveNoDrawBG();
    delay(50);
    feedTheDog();
    fmtTick();
    if(RXA_LED)
    {
        loopMode=0;
        channelSaveActive();
    }
}

void scanClearIgnores(void)
{
    u8 i;
    for(i=0; i!=50; i++)
    {
        scanIgnores[i] = 0;
    }
}

void scanAddIgnore(const u32* freq)
{
    if(scanCheckIgnores(freq))
    {
        scanIgnores[scanIgnoreIndex++] = *freq;
        if(scanIgnoreIndex>49)
            scanIgnoreIndex=0;
    }
}

const u8 scanCheckIgnores(const u32* freq)
{
    u8 i;
    for(i=0; i!=50; i++)
    {
        if(*freq==scanIgnores[i]) return 0;
    }
    return 1;
    //return !isFmtFreq((const U32*)&freq);
}

const u8 scanUltra(const u32* freq)
{
    bkSet30(0);
    bkSetReg(0x43, 0x0028);
    bkSetFreqRegs(*freq);
    bkAfDacOff();
    delay(1);
    delay100us();
    delay100us();
    return bkGetReg(0x67)->bytes.lo;
}


/* void scanNormalize(void)
{
    ultraFloor=255;
    EA = 0;
    u32 freq = scanFreqStart;
    u8 cnt=50;
    while(cnt--)
    {
        feedTheDog();
        const u8 sig = scanUltra(&freq);
        if(sig<ultraFloor)
            ultraFloor=sig;
        freq+=(u32)settings.step;
        if(freq>scanFreqEnd)
            break;
    }
    EA=1;
} */

void scanFreqCountStart(void)
{
    if(!ACTIVE_VFOSTATE.mode)
    {
        loopMode = LOOPMODE_FREQCOUNTER;
        displayVfoRefreshActiveDrawBG();
        freqScanFilter = 0;
    }
}

void scanFreqCountTick(void)
{
    U16* regd;
    U16* rege;
    POW_2822 = 0;
    squelchOpen = 0;
    radioSetFilters(1, freqScanFilter);
    bkSetReg(0x32, 0x4001);
    regd = bkGetReg(0x0d);
    if(!(regd->bytes.hi & 0x80))
    {
        regd->bytes.hi &= 7;
        rege = bkGetReg(0x0e);
        bkSetReg(0x32, 0x4000);
        ACTIVE_VFO.rxFreq.words.hi = regd->value;
        ACTIVE_VFO.rxFreq.words.lo = rege->value;
        ACTIVE_VFO.rxFreq.value -= (((s32)ACTIVE_VFO.rxFreq.value >> 17) * (s32)tuning.xtal671) >> 9;
        ACTIVE_VFO.txFreq.value = ACTIVE_VFO.rxFreq.value;
        freqScanFilter = ACTIVE_VFO.rxFreq.words.hi < 0x1ab;
        displayVfoRefreshActiveNoDrawBG();
        bkSetFreq(&(ACTIVE_VFO.rxFreq.value));
        delay(30);
        if(bkGetRssi()>219)
            loopMode = 0;
    }
    if(!loopMode || keypadSinglePress()==KEY_EXIT)
    {
        loopMode = 0;
        bkApplyActiveVfo();        
        displayVfoRefreshActiveDrawBG();
    }
}

void scanLoadPreset(void)
{
    eepromRead(0x1b00 + ((u16)scanPresetIndex*20), (u8*)&scanPresetBuffer, 20);
    ((u8*)&scanPresetBuffer)[19]=0;
}

void scanApplyPreset(void)
{
    ACTIVE_VFO.rxFreq.value = scanPresetBuffer.startFreq.value;
    ACTIVE_VFO.txFreq.value = scanPresetBuffer.startFreq.value;
    settings.scanRange = scanPresetBuffer.range;
    settings.step = scanPresetBuffer.step;
    settings.scanResume = scanPresetBuffer.resume;
    settings.scanPersist.value = scanPresetBuffer.persist;
    scanModSave=ACTIVE_VFO.bits.modulation==0;
    ACTIVE_VFOX.modulation = scanPresetBuffer.bits.modulation+1;
    ACTIVE_VFO.bits.modulation = scanPresetBuffer.bits.modulation+1;
    settings.ultraScan = scanPresetBuffer.bits.ultrascan;
    validateVfo(settings.activeVfo);
    bkApplyActiveVfo();
    radioSetScanStartFreqToVfo();
}

void scanDisplayPreset(void)
{
    SPRINT_NUMBER(TXT, scanPresetIndex, 2, 255, 1, 1);
    fontDraw8x16(TXT,4,40,COL_BATTICONBODY);
    fontCustomSymbol(scanMultiPreset[scanPresetIndex]?8:13, 28, 44, COL_MENU);
    fontDraw8x16(scanPresetBuffer.label,38,40,COL_VFORXFREQ);
    SPRINT_NUMBER(TXT, scanPresetBuffer.startFreq.value, 4, 5, 1, 1);
    fontDraw8x16(TXT,28,62,COL_INPUT);
    SPRINT_NUMBER(TXT, scanPresetBuffer.startFreq.value + ((u32)scanPresetBuffer.range*1000), 4, 5, 1, 1);
    fontDraw8x16(TXT,28,88,COL_INPUT);
    fontDraw6x8(getModName(scanPresetBuffer.bits.modulation+1), 4, 110, COL_VFOCHNAME);
    SPRINT_NUMBER(TXT, scanPresetBuffer.step, 3, 2, 1, 1);
    fontDraw6x8(TXT, 28, 110, COL_VFOCHNAME);
    fontDraw6x8(KHZ, 67, 110, COL_VFOCHNAME);
    memCpy2(US, TXT, 3);
    SPRINT_NUMBER(&TXT[3], scanPresetBuffer.bits.ultrascan, 2, 255, 1, 1);
    fontDraw6x8(TXT, 91, 110, COL_VFOCHNAME);

}

void clampSPI(void)
{
    if(scanPresetIndex&0x80) scanPresetIndex=19;
    if(scanPresetIndex>19) scanPresetIndex=0;
}

const u8 scanNextPreset(u8 dir)
{
    u8 i;
    scanPresetIndex+=dir;
    clampSPI();
    if(!dir) dir=1;
    for(i=0; i!=21; i++)
    {
        scanLoadPreset();
        if(scanPresetBuffer.startFreq.value)
        {
            scanDisplayPreset();
            return 1;
        }
        scanPresetIndex+=dir;
        clampSPI();
    }
    return 0;
}

const u8 scanUsingMultiPresets(void)
{
    u8 i;
    for(i = 0; i != 20; i++)
    {
        if(scanMultiPreset[i]) return 1;
    }
    return 0;
}

void scanClearMultiPresets(void)
{
    memFill(scanMultiPreset, 20, 0);
}

void scanPresetMenu(void)
{
    u8 loop, lastKey, key;
    scanClearMultiPresets();
    lcdCls();
    fontDraw8x8(SCANPRESETS, 16, 8, COL_VFOTXFREQ, 0);    
    if(scanNextPreset(0))
    {
        inputMode=1;
        loop=1;
        lastKey=0;
        while(loop)
        {            
            feedTheDog();
            delay(15);
            uartTick();
            keypadTick(1);
            key=keypadSinglePress();
            if(key<10)
            {
                if(lastKey==1)
                {
                    scanPresetIndex=10+key;
                    lastKey=0;
                }
                else
                {
                    scanPresetIndex=key;
                    lastKey=key;
                }
                scanNextPreset(0);
            }
            else
            switch(key)
            {
                case KEY_STAR:
                    scanMultiPreset[scanPresetIndex] ^= 1;
                    scanNextPreset(0);
                    break;
                case KEY_MENU:
                    if(scanUsingMultiPresets())
                        scanMultiPreset[scanPresetIndex] = 1;
                    scanApplyPreset();
                    scanStart();
                    loop = 0;
                    break;
                case KEY_EXIT:
                    loop = 0;
                    break;
                case KEY_DOWN:
                case KEY_UP:
                    scanNextPreset(key==KEY_UP?1:0xff);
                    break;
            }
        }
    }
    inputMode=0;
    lcdCls();
    displayRefreshFull();
    //timersReset();
}