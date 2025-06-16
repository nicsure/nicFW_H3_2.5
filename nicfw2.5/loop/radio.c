void finalizeGroupEdit(void)
{
    displayVfoRefreshActiveNoDrawBG();
    groupMap[ACTIVE_VFOX.number] = ACTIVE_VFO.groups.value;
    channelSaveActive();  
}

const u8 pinOk(void)
{
    return (u16)inputValue==settings.pin;
}

void radioLoopTick(void)
{
    u8 i, y, dir;
    u8 key, ch;
    U16* reg0c;
    u32 offset;
    s32 step;
    if(ACTIVE_VFOSTATE.mode)
    {
        if(addGroupTrigger)
        {
            if(ACTIVE_VFO.groups.single.g0==0) ACTIVE_VFO.groups.single.g0=addGroupTrigger; else
            if(ACTIVE_VFO.groups.single.g1==0) ACTIVE_VFO.groups.single.g1=addGroupTrigger; else
            if(ACTIVE_VFO.groups.single.g2==0) ACTIVE_VFO.groups.single.g2=addGroupTrigger; else
            if(ACTIVE_VFO.groups.single.g3==0) ACTIVE_VFO.groups.single.g3=addGroupTrigger;
            finalizeGroupEdit();
        }
        if(delGroupTrigger)
        {
            if(ACTIVE_VFO.groups.single.g0==delGroupTrigger) ACTIVE_VFO.groups.single.g0=0; else
            if(ACTIVE_VFO.groups.single.g1==delGroupTrigger) ACTIVE_VFO.groups.single.g1=0; else
            if(ACTIVE_VFO.groups.single.g2==delGroupTrigger) ACTIVE_VFO.groups.single.g2=0; else
            if(ACTIVE_VFO.groups.single.g3==delGroupTrigger) ACTIVE_VFO.groups.single.g3=0;
            finalizeGroupEdit();
        }
    }
    addGroupTrigger=0;
    delGroupTrigger=0;

    if(!KEY_LED && settings.powerSave && !squelchOpen && !xmitActive && !fmtActive && !powerSaveSuspend)
    {
        POW_2822=0;
        bkSet30(0);
        BT_ON = 0;
        radioClearFilters();
        for(i=0; i!=settings.powerSave; i++)
        {
            delay(50);
            feedTheDog();
            keypadTick(3);
            if(KEY_LED)
                break;
        }
        ticksPassed=0;
        radioSetFilters(1, ACTIVE_VFOX.rxIsVhf);
        BT_ON = settings.bluetooth;
        bkSet30(0xBDF1);
        delay(20);
    }
    key = keypadSinglePress();
    if(settings.vox)
    {
        reg0c = bkGetReg(0x0c);
        voxTank += !voxIgnore && (reg0c->bytes.lo & 4) ? 1 : 0xff;
        if(voxTank == 0xff) voxTank=0;
        if(voxTank == 11) voxTank=10;
        if(xmitRequest)
        {
            if((voxTank==0 && !voxTailTimer) || voxTank==10)
                voxTailTimer=settings.voxTail;
        }
        else
        {
            if(voxTank==10)
                xmitRequest = 1;
        }
    }
    if(!xmitActive && !settings.pttMode) // not currently in xmit mode and in dual ptt mode
    {
        if(!scopeActive)
        {
            if((keypadPTTA() && VFOB_ISACTIVE) || (keypadPTTB() && VFOA_ISACTIVE)) // has the opposite PTT to the active vfo been pressed?
            {
                radioSwapVfo(); // swap the vfos
                settingsSave();
                bkApplyActiveVfo(); // send the new VFO's settings to the BK4819
                //if(ACTIVE_VFO.bits.busyLock) // if the new vfo has busylock enabled
                //{
                //    delay(20); // pause for 20ms to allow signal to build up
                //    if(ACTIVE_VFO.rxSubTone) // if an rx subtone is also enabled
                //        delay(230); // increase pause to 1/4 second to allow tone to be decoded
                //    rssiTick(); // perform a squelch check
                //}
            }
        }
    }
    if(!ACTIVE_VFOX.isFmTuner && !scopeActive)
    {
        if(xmitActive || !ACTIVE_VFO.bits.busyLock || !RXB_LED)
        {
            if(txTimer!=0xff && (keypadPTT() || xmitRequest))
            {
                fmtResume = 0;
                lcdBacklight(1);
                if(settings.dualWatch && settings.vfoLock && settings.pttMode && settings.activeVfo != settings.setVfo)
                {
                    radioSwapVfo();
                    bkApplyActiveVfo();
                }
                if(ACTIVE_VFOX.txPower)
                {
                    if(!xmitActive)
                    {
                        bkInitXmit();            
                    }
                    bkXmitTick();
                }
            }
            else
            {
                if(xmitActive)
                {
                    dualWatchStartTimer = settings.dwDelay;
                    bkEndXmit();
                    if(txTimer == 0xff)
                    {
                        differentialKeyTone(12, 10);
                        voicePlay(VOICE_ID_TRANSMIT_OVER_TIME, 0);
                        voxIgnore = 40;
                        voxTank = 0;
                        xmitRequest = 0;
                        EA=0;
                        while(keypadPTT())
                        {
                            uartTick();
                            keypadTick(1);
                            delay(10);
                            feedTheDog();
                        }
                        EA=1;
                    }
                }
                txTimer = 0;
            }
        }
    }
    if(xmitActive)
        return;
    switch(longPress)
    {
        case KEY_UP:
        case KEY_DOWN:
            if(fmtActive)
            {
                fmtScanDown = longPress==KEY_DOWN;
                longPress=KEY_LONGACTIONED;
                scanStart();
                return;
            }
            else
                key = longPress;
            break;
        case KEY_FLSH:
            squelchOverride =! squelchOverride;
            longPress = KEY_LONGACTIONED;            
        case KEY_NONE:
        case KEY_LONGACTIONED:
            break;
        default:
            key=longPress+0x20;
            longPress=KEY_LONGACTIONED;
            break;
    }
    if(inputState)
    {
        if(inputState==INPUT_APPLIED)
        {
            if(ACTIVE_VFOSTATE.mode && inputUnits==3) // potential code shrink
            {
                inputState = INPUT_IDLE;
                ch=C32(inputValue)->bytes.byte0;
                if(ch>198) ch=198;
                ch++;
                radioToggleVfoMode(1, ACTIVE_VFOSTATE.group, ch);
                return;
            }
            else
            if(enteringPin) // keylock
            {                
                delay(500);
                feedTheDog();
                if(pinOk())
                {                    
                    lcdCls();
                    toggleKeylock();
                }                
            }
            else
            if(offsetInput)
            {
                switch(offsetInput)
                {
                    case 1: // absolute freq
                        ACTIVE_VFO.txFreq.value = inputValue;
                        break;
                    case 2: // negative offset
                        ACTIVE_VFO.txFreq.value = ACTIVE_VFO.rxFreq.value - inputValue;
                        break;
                    case 3: // positive offset
                        ACTIVE_VFO.txFreq.value = ACTIVE_VFO.rxFreq.value + inputValue;
                        break;
                }
            }
            else
            if(inputAsGroup)
            {
                radioToggleVfoMode(1, inputValue, 0);
            }            
            else
            {
                offset = ACTIVE_VFO.txFreq.value - ACTIVE_VFO.rxFreq.value;
                ACTIVE_VFO.rxFreq.value = inputValue;
                inputValue+=offset;
                ACTIVE_VFO.txFreq.value = inputValue;
                scanFreqStart=inputValue;
                scanClearMultiPresets();
                step833Counter = 1;
            }
        }
        inputState = INPUT_IDLE;
        offsetInput = 0;
        inputAsGroup = 0;
        validateVfo(settings.activeVfo);
        bkApplyActiveVfo();
        if(enteringPin && settings.keyLock) lcdCls();
        displayRefresh(1); //enteringPin);        
        enteringPin = 0;
    }
    else    
    if(key<10 && (key || inputMode))
    {
        y = displayVfoPos(settings.activeVfo);
        if(!ACTIVE_VFOSTATE.mode)
        {            
            inputPrepare(4, 5, VFO_RXXPOS, y+DIS(VFO_RXYPOS), 4);
            inputParseKey(key);
        }
        else
        {
            inputPrepare(3, 0, VFO_NAMEX+12, y+DIS(VFO_NAMEY), 0);
            inputParseKey(key);       
        }
    }
    else
    {
        dir = 0xff;
        if(key==KEY_NONE)
            return;
        if(key>0x1f)
        {
            longpressAction(key-0x20);
            return;
        }
        switch(key)
        {
            default: return;

            case KEY_FLSH:
                HLED=!HLED;
                return;
            case KEY_EXIT:
                if(scopeActive)
                {
                    scopeStop();
                    displayBlankSBarDPTT();
                    return;
                }
                if(ACTIVE_VFOSTATE.mode)
                {
                    if(ACTIVE_VFOSTATE.group)
                    {
                        radioToggleVfoMode(0, 0, 0);
                    }
                    else
                    {
                        if(!ACTIVE_VFOSTATE.lastGroup) ACTIVE_VFOSTATE.lastGroup=1;
                        radioToggleVfoMode(1, ACTIVE_VFOSTATE.lastGroup, 0);
                    }
                }
                else
                {
                    radioToggleVfoMode(1, 0, 0);
                }
                return;
            case KEY_DOWN:
            case KEY_UP: {
                STEPUPDOWN:
                dir = key==KEY_UP||key==KEY_STAR?1:0xff;
                if(!ACTIVE_VFOSTATE.mode)
                {
                    step = step833(dir);
                    if(key==KEY_STAR || key==KEY_0)
                        step*=10;
                    ACTIVE_VFO.rxFreq.value+=step;
                    ACTIVE_VFO.txFreq.value+=step;
                    planWrapVfo(settings.activeVfo);
                    radioSetScanStartFreqToVfo();
                    scanClearMultiPresets();
                    break;
                }
                radioToggleVfoMode(ACTIVE_VFOSTATE.mode, ACTIVE_VFOSTATE.group, dir);
                return; }
            case KEY_STAR:
            case KEY_0:
                if(scopeActive)
                {
                    goto STEPUPDOWN;
                }
                if(ACTIVE_VFOSTATE.group)
                {
                    radioToggleVfoModeAndGroup(ACTIVE_VFOSTATE.mode, ACTIVE_VFOSTATE.group, 0, key==KEY_STAR?1:0xff);
                }
                return;
            case KEY_MENU:
                menuInit();
                return;
            case KEY_HASH:
                if(scopeActive)
                {
                    ACTIVE_VFO.rxFreq.value=hiFreq;
                    ACTIVE_VFO.txFreq.value=hiFreq;
                    break;
                }            
                radioSwapVfo();
                settingsSave();
                bkApplyActiveVfo();
                settings.setVfo = settings.activeVfo;
                displayRefreshGeneral();
                return;
        }
        validateVfo(settings.activeVfo);
        bkApplyActiveVfo();     
        displayVfoRefreshActiveNoDrawBG();
    }
}

const s16 step833(const u8 dir)
{
    u8 add;
    if(fmtActive) return dir==1?5000:0xEC78;
    add = 0;
    if(settings.step==833)
    {
        step833Counter += dir;
        if(step833Counter==0)
        {
            step833Counter = 3;
            add=1;
        }
        else
        if(step833Counter==4)
        {
            step833Counter = 1;
            add=1;
        }
    }
    if(dir==1)
        return settings.step+add;
    return 0-(settings.step+add);
}

void radioToggleVfoModeAndGroup(u8 newMode, u8 group, const u8 chstep, const u8 grpDir)
{
    u8* lastChannel;
    if(newMode>1) newMode=0;
    if(!newMode) group=0;
    if(group)
    {
        group+=grpDir;
        group=channelValidateGroup(group, grpDir==0xff?0xff:1);
        ACTIVE_VFOSTATE.lastGroup = group;
        if(group==0)
            newMode=0;
    }
    if(initComplete && newMode != ACTIVE_VFOSTATE.mode)
    {
        voicePlay(newMode?VOICE_ID_CHANNEL_MODE:VOICE_ID_FREQUENCY_MODE, 0);
    }
    ACTIVE_VFOSTATE.group = group;
    ACTIVE_VFOSTATE.mode = newMode;
    switch(ACTIVE_VFOSTATE.mode)
    {
        case 0: // vfo mode
            channelLoad(settings.activeVfo, settings.activeVfo);
            break;
        case 1: {  // potential code shrink
            lastChannel = &(ACTIVE_VFOSTATE.groupModeChannels[group]);
            if(chstep==1 || chstep==0xff)
                *lastChannel += chstep;
            else
            if(chstep)
                *lastChannel = chstep;
            if(*lastChannel<2 || *lastChannel==0xff) *lastChannel=199;
            if(*lastChannel>199) *lastChannel=2;
            *lastChannel = channelValidateOrNext(*lastChannel, chstep==0xff?chstep:1, group, 0);
            channelLoad(*lastChannel, settings.activeVfo);
            break; }
    }
    bkApplyActiveVfo();
    displayVfoRefreshActiveNoDrawBG();
}

void radioToggleVfoMode(u8 newMode, u8 group, const u8 chstep)
{
    radioToggleVfoModeAndGroup(newMode, group, chstep, 0);
}


void radioSetScanStartFreqToVfo(void)
{
    scanFreqStart = ACTIVE_VFO.rxFreq.value;
}

void radioSwapVfo(void)
{
    settings.activeVfo = settings.activeVfo ? 0 : 1; // potential code shrink
    radioSetScanStartFreqToVfo();
    displayRefreshFull();
    soundBlip(6, 170, settings.activeVfo);
}

void radioSetLED(const u8 led, const u8 state)
{
    if(led&RXALED) RXA_LED=state;
    if(led&TXALED) TXA_LED=state;
    if(led&RXBLED) RXB_LED=state;
    if(led&TXBLED) TXB_LED=state;
    remoteSendLedStatus();
}

void radioClearFilters(void)
{
    URX_FILT = 1;
    UTX_FILT = 1;
    VRX_FILT = 1;
    VTX_FILT = 1;
}

void radioSetFilters(const bit rx, const bit vhf)
{
    radioClearFilters();
    if(rx)
    {
        if(vhf)
            VRX_FILT=0;
        else
            URX_FILT=0;
    }
    else
    {
        if(vhf)
            VTX_FILT=0;
        else
            UTX_FILT=0;
    }
}

void validateVfo2(const u8 vfoPosition)
{
    channelInfo* vfo = &(VFO[vfoPosition]);
    channelXtra* vfox = &VFOX[vfoPosition];
    if(vfox->number < 2) vfo->groups.value = 0;
    if( clampFreq(&(vfo->rxFreq.value)) | clampFreq(&(vfo->txFreq.value)) )
    {
        vfo->rxSubTone.value=0;
        vfo->txSubTone.value=0;
        *((u8*)&(vfo->bits))=0;
    }
    vfox->rxIsVhf = isFreqVhf(&(vfo->rxFreq.value), 1); // (vfo->rxFreq.value/10000) < settings.rxSplit;
    vfox->txIsVhf = isFreqVhf(&(vfo->txFreq.value), 0); //(vfo->txFreq.value/10000) < settings.txSplit;    
    planApply(vfoPosition);
}

void planEnd(const u8 vfoPosition)
{
    channelInfo* vfo = &(VFO[vfoPosition]);
    const planInfo* plan = &plans[VFOX[vfoPosition].rxplan];
    if(plan->endFreq > FREQ_MAX)
    {
        vfo->rxFreq.value=0;
        vfo->txFreq.value=0;
    }
    else
    { 
        vfo->rxFreq.value=plan->endFreq;
        vfo->txFreq.value=plan->endFreq;
    }
}

void validateVfo(const u8 vfoPosition)
{
    planInfo* plan;
    do
    {
        validateVfo2(vfoPosition);
        plan = &plans[VFOX[vfoPosition].rxplan];
        if(plan->bits.modulation!=7) break;
        planEnd(vfoPosition);
    } while(1);
    channelSave(vfoPosition);
    settingsSave();
}