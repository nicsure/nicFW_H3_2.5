
const u8 rssiSetToneDetectionFlag(void)
{
    rxToneDetected = bkSubToneDetected();
    return rxToneDetected;
}

static u8 squelchHiNoiseTrip;

void rssiCheckSquelch(const u8 hdbm, const u8 exnoise, const u8 level)
{
    // hdbm represents half dbm units above the noise floor it is not absolute.
    // it is also 0 based, so 0 represents the noise floor or S0
    // each S unit is 6 dbm which correspends to 12 in this scale so
    // S0 = 0 
    // S1 = 12
    // ...
    // S8 = 96
    // S9 = 108
    // S9+10 = 128;
    // S9+20 = 148;
    // ...
    // S9+50 = 208;
    // S9+60 = 228;

    // V2 squelch operates as such
    // squelch =
    //   0   - No squelch, always open
    //   1   - Ex Noise based squelch only, squelch opens on low exnoise
    //   2-9 - Signal/Noise based squelch minus 1
    //         In order to trigger squelch opening the signal must reach Sx for example for squelch 4 a signal must hit S3 AND have low ex noise
    //         for squelch to close, the signal should drop below Sx for example for squelch 4, the signal should drop below S3
    //         However noise plays a part here.
    //         If the signal drops below Sx but ex noise is still low, squelch will remain open until ex noise goes high
    //         If the ex noise goes high but the signal has not dropped below close threshold (Sx) one of two things will happen
    //                  If the signal strength is above the threshold (Sx) squelch remains open
    //                  If the signal strength is below the threshole (Sx) squelch will close.

    u8 targetnoise;
    u8 targetdbm;
    bit triggerdbm;
    bit triggernoise;

    if(squelchOpenPause)
    {
        signalPresent = 1;
        squelchOpen = 1;
        return;
    }

    if(exnoise>settings.noiseCeiling && !rxToneDetected)
    {
        if(squelchHiNoiseTrip++>3)
        {
            signalPresent = 0;
            squelchHiNoiseTrip = 0;
        }
    }
    else {
        squelchHiNoiseTrip = 0;
    }
    
    rssiSetToneDetectionFlag();
    targetnoise = settings.sqNoiseLev + (signalPresent?8:0xF8u); // calculate target noise and add or subtract 10 for hysteresis
    targetdbm = ((level-1)*12) + (signalPresent?0xFAu:6); // calculate target dbm (S level-1)
    triggerdbm = signalPresent ? (hdbm<targetdbm) : (hdbm>targetdbm); // triggers are dependant on current squelch state
    triggernoise = signalPresent ? (exnoise>targetnoise) : (exnoise<targetnoise); // bit is 8051-Speak for BOOL
    if(triggernoise)
    {
        if(level==1 || triggerdbm)
            signalPresent=!signalPresent;
    }
    radioSetLED(RXBLED, signalPresent);
    if((settings.ste & 1) && bk55Detected())
    {
        steTimer=5;
    }
    if(steTimer)
    {
        squelchOpen=0;
    }
    else
    if(!fmtActive && appliedVfo==settings.activeVfo && (!level || squelchOverride)) //keypadLong==KEY_FLSH))
    {
        squelchOpen = 1;
    }
    else
    if(APPLIED_VFO.rxSubTone.value && !subToneOverride) 
    {
        u8 cnt=25;
        squelchOpen = rxToneDetected;
        while(signalPresent && !squelchOpen && !anyKeyInUse && (cnt--)) 
        {
            delay(10);
            keypadTick(1);            
            squelchOpen = rssiSetToneDetectionFlag();
            if(bkGetExNoise()>settings.noiseCeiling) signalPresent = 0;
        }
        if(squelchOpen && APPLIED_VFO.rxSubTone.value==1050)
        {
            subToneOverride = 1;
        }   
        if(!squelchOpen && (loopMode&LOOPMODE_SCANMONITOR))
        {
            radioSetLED(RXBLED, 0);
            scanningResume = 0;
        }
    }
    else
        squelchOpen=signalPresent;
    if(!fmtActive)
        radioSetLED(RXALED, squelchOpen);
    if(!signalPresent) subToneOverride = 0;
    if(squelchOpen && scanActivityMode && (loopMode&LOOPMODE_SCAN))
    {
        squelchOpen=0;
        uartSendByte(0x2A);
        uartSendByte(C32(scanFreq)->bytes.byte0);
        uartSendByte(C32(scanFreq)->bytes.byte1);
        uartSendByte(C32(scanFreq)->bytes.byte2);
        uartSendByte(C32(scanFreq)->bytes.byte3);
        uartSendByte(hdbm);
    }
}

const u16 rssiGetSignal(void)
{
    u16 sig = bkGetRssi();
    if(sig > noiseFloor) sig-=noiseFloor; else sig=0;
    return sig;    
}

void rssiGetFloor(const u32* freq)
{
    const U32* temp = (U32*)freq;
    /*
    if(settings.autoFloor)
    {        
        if(temp.words.hi != lastAutoFloorFreq)
        {
            lastAutoFloorFreq = temp.words.hi;
            noiseFloor = 255;
        }
        temp.value -= 18708;
        for(u8 i=0; i<8; i++)
        {
            if(i==7) temp.value=freq; else temp.value+=4677;  
            if(i==3) continue;
            bkSetFreq(temp.value);
            delay(19);
            const u16 sig = bkGetRssi();
            if(sig<noiseFloor) noiseFloor=sig;
        }
    }
    else
    {
    */
        if(temp->words.hi<=0xA4) noiseFloor = 90; else
        if(temp->words.hi<=0xD2) noiseFloor = 110; else
        if(temp->words.hi<=0x109) noiseFloor = 100; else
        if(temp->words.hi<=0x216) noiseFloor = 68; else
        if(temp->words.hi<=0x262) noiseFloor = 74; else
        if(temp->words.hi<=0x2cd) noiseFloor = 72; else
            noiseFloor=62;
        //bkSetFreq(freq);
    //}
}


void rssiTick(void)
{
    u16 oldTone;
    u16 sig;
    bit oldSquelch;
    u8 exn;
    bit state2822;    
    if(scopeActive)
    {
        scopeDraw();
        return;
    }
    if(settings.toneMonitor && (!loopMode || loopMode==LOOPMODE_SCANMONITOR))
    {
        oldTone = heardTone;
        if(stMonitor())
        {
            heardToneCounter = 10;
            if(toneChanged)
            {
                if(oldTone==heardTone)
                {
                    toneChanged--;
                    if(!toneChanged)
                        displayToneMonitor();
                }
                else
                    toneChanged=50;
            }
            else
            {
                if(oldTone!=heardTone)
                    toneChanged=50;
            }
        }
        else
            toneChanged=0;
    }
    sig = rssiGetSignal();
    oldSquelch = squelchOpen;
    exn = bkGetExNoise();
    rssiCheckSquelch(sig, exn, settings.squelch);
    if(!squelchOpen) {
        lastSig=255;
    }
    state2822 = POW_2822;
    //if(oldSquelch != squelchOpen)
    //{
    //    if(!inputMode)
    //        displayVfoRefresh(settings.activeVfo, 1);
    //    POW_2822 = 0;
    //}
    if(settings.asl==2) btInUse=0;
    if(oldSquelch)
    {
        if(!squelchOpen)
        {
            POW_2822=0;
            delay(3);
            bkAfDacOff();
            if(settings.asl==2) uartSendByte(0x10);
            if(!inputMode) displayVfoRefreshActiveDrawBG();
            if(!settings.sBarAlwaysOn) displayDrawMeter(0,3);
            displayDrawExNoise(0,0);            
        }
    }
    else
    {
        if(squelchOpen)
        {
            squelchOpenPause = 4;
            if(settings.asl==2) uartSendByte(0x11);
            if(!inputMode) displayVfoRefreshActiveDrawBG();
            state2822 = POW_2822;
            POW_2822=0;
            if(state2822) delay(3);
            bkAfDacOn();
            bkSetModulation(0, 0);
            delay(3);
            POW_2822=1;
            delay(3);
            bkSetModulation(currentModulation, 1);
        }
    }
    if(settings.asl&1)
        COS = settings.asl==1 ? squelchOpen : !squelchOpen;    
    if(squelchOpen)
    {
        if(fmtResume)
            fmtResume = 5;
    }
    if(squelchOpen || (settings.sBarAlwaysOn && appliedVfo==settings.activeVfo))
    {
        if(!rssiTrigger && !fmtActive)
        {
            displayDrawMeter(sig>>1, 0);
            displayDrawExNoise(exn, 0);
            rssiTrigger=1;
        }
    }
}