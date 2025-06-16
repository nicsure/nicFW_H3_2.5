void secondTick(const u8 secs)
{
    subCounter(&dualWatchStartTimer, 1);
    subCounter(&powerSaveSuspend, 1);
    if(subCounter(&remoteDisableTimer, 1))
    {
        remoteActive = 0;
        externalKey = KEY_NONE;
    }

    if(scanActivityMode)
    {
        uartSendByte(0x2b);
    }

    if(txTimer!= 0xff && subCounter(&txTimer, secs) && xmitActive)
    {
        txTimer = 0xff;
    }

    if(!inputMode)
    {
        subCounter(&scanningSkip, secs);
        if(loopMode==LOOPMODE_SCANMONITOR && settings.scanResume && !skipMeter)
            displayVfoRefreshActiveNoDrawBG();
    }

    if(subCounter(&dtmfDisplayTime, 1)) {
        lcdFill(0, flagsYPOS(), 128, 8, COL_FWBGROUND);        
        displayRefreshGeneral();
    }

    if(subCounter(&heardToneCounter, secs))
    {
        heardTone=0;
        displayToneMonitor();
    }

    if(subCounter(&fmtResume, 1))
    {
        if(VFOX[settings.activeVfo^1].isFmTuner)
        {
            radioSwapVfo();
            bkApplyActiveVfo();
        }
    }

    if(!xmitActive && !squelchOpen && KEY_LED && !inputMode && subCounter(&lcdTimer, 1))
    {
        lcdBacklight(0);
    }

    if(settings.breathe && !KEY_LED)
    {
        if(!breatheTimer) breatheTimer++;
        if(subCounter(&breatheTimer, secs))
        {
            breatheTimer=settings.breathe;
            KEY_LED=1;
            delay(30);
            KEY_LED=0;
        }
    }

    if(reqSettingsSave)
    {
        reqSettingsSave=0;
        settingsWrite();
    }
    if(!inputMode && settings.battStyle)
    {
        batteryRead();
        batteryShow(FLAGS_BATTX, flagsYPOS());
    }
}

void decisecondTick(const u8 tenths)
{
    u8 otherVfo;
    if(sinceLastDtmfDigit<settings.dtmfEndPause) {
        sinceLastDtmfDigit++;
        if(sinceLastDtmfDigit==settings.dtmfEndPause && !inputMode && !fmtActive) {
            dtmfSearchPresets();
        }
    }    

    if(ceilingMenuActive && (inputMode & INPUTMODE_MENU)) 
    {
        SPRINT_NUMBER(TXT, bkGetExNoise(), 3, 255, 0, 1); 
        fontDraw8x16(TXT, 82, 95, COL_MENUEDIT);
    }

    if(loopMode==LOOPMODE_SCAN && subCounter(&updateTimer, 1))
    {
        updateTimer = settings.scanUpdate;
        if(!inputMode)
        {
            vposTemp = displayVfoPos(settings.activeVfo);
            if(settings.pttMode!=1 && !VFO_CHANGERXFREQNOTBG) COL_BGROUND.value = COL_VFOSCAN.value;
            if(!ACTIVE_VFOSTATE.mode)
            {
                SPRINT_NUMBER(&TXT[5], scanFreq, 4, 5, 1, 1);
                memCpy2(scanActivityMode?ACIV_LABEL:SCAN_LABEL, TXT, 5);
                fontDraw6x8(TXT, VFO_CH_NAMEX, vposTemp+DIS(VFO_CH_NAMEY), COL_VFOCHNAME);
            }
            else
            {
                displayFreq(&scanFreq, VFO_RXXPOS, vposTemp+DIS(VFO_RXYPOS), COL_VFORXFREQ, 5, 1);
                channelSprintName(updateScanChannel);
                fontDraw8x8(TXT, VFO_CH_NAMEX, vposTemp+DIS(VFO_CH_NAMEY), COL_VFOCHNAME, LARGE_CH_NAME);
                SPRINT_NUMBER(TXT, updateScanChannel, 3, 255, 0, 1);
                fontDraw6x8(TXT,VFO_NAMEX+12,vposTemp+DIS(VFO_NAMEY),COL_VFOCORNER);
            }
            COL_BGROUND.value = COL_FWBGROUND.value;
        }
    }
    subCounter(&squelchOpenPause, 1);
    subCounter(&voxTank, tenths);
    subCounter(&voxIgnore, 1);
    subCounter(&steTimer, 1);
    if(subCounter(&voxTailTimer, tenths))
    {
        xmitRequest = 0;
    }
    if(fmtResume && (inputMode || loopMode || fmtActive))
        fmtResume = 0;    
    if(squelchOpen)
    {
        lcdBacklight(1);
    }    
    if(rssiTrigger) rssiTrigger--;
    if(scanningResume) scanningResume--;
    if(fmtActive) fmtTick();

    if(settings.dualWatch && !xmitActive && !loopMode && !inputMode && !squelchOpen && !dualWatchStartTimer)
    {
        
        otherVfo = settings.activeVfo ^ 1;
        if(!ACTIVE_VFOX.isFmTuner)
        {
            if(!VFOX[otherVfo].isFmTuner)
            {
                bkApplyVfo(otherVfo);
                delay(20);
                rssiTick();
                if(squelchOpen)
                {
                    settings.activeVfo = otherVfo;
                    displayRefreshFull();
                }
                else
                {
                    bkApplyActiveVfo();
                    delay(20);
                    rssiTick();                    
                }
            }
        }
        else
        {
            if(!VFOX[otherVfo].isFmTuner && appliedVfo != otherVfo)
                bkApplyVfo(otherVfo);
        }
    }
    if(settings.dualWatch && ACTIVE_VFOX.isFmTuner)
    {
        if(squelchOpen)
        {
            settings.activeVfo ^= 1;
            displayRefreshFull();
            if(fmtActive) fmtDisable();
            fmtResume = 5;
        }
    }


}

void tick(const u8 ticks)
{
    bkAmAgc();
    if(!xmitActive)
    {
        if(!loopMode || loopMode==LOOPMODE_SCANMONITOR)
            rssiTick();
    }
    keypadTick(ticks&0x7f);
    if(inputMode & INPUTMODE_INPUT)
    {
        inputTick();
    }
    else
    if(inputMode & INPUTMODE_MENU)
    {
        menuTick();
    }
    else
    if(!loopMode)
    {
        radioLoopTick();
    }
}

void timers(void)
{
    u8 dtmfDigit;    
    u8 secs;
    u8 decisecs;
    u8 ticks;
    secs=0;
    decisecs=0;
    ticks=0;
    EA=0;
        if(secondsPassed)
        {
            secs=secondsPassed;
            secondsPassed=0;
        }
        if(decisecondsPassed)
        {
            decisecs = decisecondsPassed;
            decisecondsPassed=0;
        }
        ticks = ticksPassed;
        ticksPassed=0;
    EA=1;
    if(secs) secondTick(secs);
    if(decisecs) decisecondTick(decisecs);
    if(ticks) tick(ticks);
    if(settings.dtmfDecode && !xmitActive && !inputMode && !fmtActive) {
        if(squelchOpen || (signalPresent && settings.dtmfDecode == 1)) {
            dtmfDigit = dtmfDetect();
            if(dtmfDigit <= 16) {
                if(dtmfDigit < 10) {
                    dtmfDigit+=48;
                } else if(dtmfDigit<14) {
                    dtmfDigit+=55;
                } else if(dtmfDigit==14) {
                    dtmfDigit = 42;
                } else {
                    dtmfDigit = 35;
                }
                if(sinceLastDtmfDigit>9)  {
                    dtmfAddDetectedDigit(32);
                }
                dtmfAddDetectedDigit(dtmfDigit);
                sinceLastDtmfDigit = 0;
            }
        }
    }     
    if(!inputMode)
    {
        if((loopMode & (LOOPMODE_SCAN | LOOPMODE_SCANMONITOR | LOOPMODE_SCANFMT)))
            scanTick();
        else
        if(loopMode==LOOPMODE_FREQCOUNTER)
            scanFreqCountTick();
    }    

    if(settings.noiseGate && squelchOpen && loopMode!=LOOPMODE_SCAN && !squelchOverride)
    {
        if(bkGetExNoise()>settings.noiseCeiling && !rxToneDetected)
        {
            noiseLimited = 10;
            bkSetModulation(0, 0);
        }
        else
        {
            if(subCounter(&noiseLimited, 1))
                bkSetModulation(currentModulation, 1);
        }
    }
    else
        noiseLimited = 0;

}

//void timersReset(void)
//{
//    EA=0;
//    secondsPassed=0;
//    decisecondsPassed=0;
//    ticksPassed=0;
//    EA=1;
//}

void timer0_ISR(void) interrupt 1
{
    secCounter++;
    if(secCounter==60)
    {
        secCounter = 0;
        secondsPassed++;
    }
    decisecCounter++;
    if(decisecCounter==6)
    {
        decisecCounter = 0;
        decisecondsPassed++;
    }
    ticksPassed++;
}