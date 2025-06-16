void saveVfo(void)
{
    vfoSaveRX = ACTIVE_VFO.rxFreq.value;
    vfoSaveTX = ACTIVE_VFO.txFreq.value;
}

void recallVfo(void)
{
    if(!isValidFreq(&vfoSaveRX)) vfoSaveRX=defaultFreq;
    if(!isValidFreq(&vfoSaveTX)) vfoSaveTX=defaultFreq;
    ACTIVE_VFO.rxFreq.value=vfoSaveRX;
    ACTIVE_VFO.txFreq.value=vfoSaveTX;
}

void reverseRxTx(void)
{
    if(ACTIVE_VFO.rxFreq.value != ACTIVE_VFO.txFreq.value)
    {
        ACTIVE_VFO.bits.reversed=!ACTIVE_VFO.bits.reversed;
        inputValue = ACTIVE_VFO.rxFreq.value;
        ACTIVE_VFO.rxFreq.value = ACTIVE_VFO.txFreq.value;
        ACTIVE_VFO.txFreq.value = inputValue;            
    }   
}

void displayDtmfWindow(void)
{
    lcdFill(0, 63, 128, 1, COL_MENU);
    lcdFill(0, 64, 128, 64, COL_FWBGROUND);
    fontDraw8x8(DTMF_LABEL, 32, 74, COL_INPUT, 1);    
}

void displayDtmfPreset(void)
{
    displayDtmfWindow();
    fontDraw8x16(TXT, 48, 94, COL_INPUT);
    dtmfSeqToString(&manualSeq, ' ', TXTEDIT);    
    fontDraw8x16(TXTEDIT, 48, 111, COL_VFORXFREQ);
    SPRINT_NUMBER(TXT, lastDtmfPreset, 2, 255, 0, 1);
    fontDraw8x16(TXT, 16, 94, COL_VFOTXFREQ);
}

void longpressAction(u8 key)
{
    u8 lpFunc;
    u8 ok, y, yy;
    lpFunc = (lpShift ? lpShiftActionTable :  lpActionTable)[key];
    switch(lpFunc)
    {
        case LP_VFOLOCK:
            settings.vfoLock ^= 1;
            displayRefreshGeneral();
            break;
        case LP_DUALPTT:
        case LP_SINGLEPTT:
        case LP_HYBRIDPTT:
            settings.pttMode = lpFunc - LP_DUALPTT;
            lcdCls();
            displayRefresh(1);
            break;
        case LP_SHIFT:
            lpShift^=1;
            displayRefreshGeneral();
            break;
        case LP_SCOPE:
            if(!ACTIVE_VFOSTATE.mode && !fmtActive)// && (settings.pttMode==0 || settings.pttMode==2))
            {
                scopeActive = 1;
                if(settings.pttMode==1) lcdCls();
                displayRefresh(1);
                squelchOpen=0;
                displayBlankSBarDPTT();
                lcdFill(0, displayVfoPos(settings.activeVfo^1), 128, VFO_HEIGHT, COL_FWBGROUND);
            }
            break;
        case LP_RFICOMP:
            //rfiAdjust = !rfiAdjust;
            //displayRefreshGeneral();
            break;
        case LP_SCANPRESET_LCDINVERT:
            if(!ACTIVE_VFOSTATE.mode)
            {
                if(!fmtActive && settings.squelch)
                    scanPresetMenu();
            }
            else
            {
                settings.lcdInverted^=1;
                lcdInvert(settings.lcdInverted);
            }
            break;
        case LP_DTMFPRESETS:
            if(ACTIVE_VFOX.txPower && dtmfSeek(0)) 
            {
                lastDtmfKey=0;
                inputMode=1;
                ok = 1;
                displayDtmfPreset();
                while(ok)
                {
                    feedTheDog();
                    delay(16);
                    rssiTick();
                    uartTick();
                    keypadTick(1);
                    key = keypadSinglePress();
                    if(keypadPTT())
                    {
                        ok = 0;
                        playDtmfOnPTT = 1;
                    }
                    else
                    if(key<10)
                    {
                        lastDtmfPreset = lastDtmfKey==1 ? 10+key : key;
                        lastDtmfKey=key;
                        dtmfSeek(0);
                        displayDtmfPreset();                     
                    }
                    else
                    switch(key)
                    {
                        case KEY_EXIT:
                            ok = 0;
                            break;
                        case KEY_UP:
                            dtmfSeek(1);
                            goto PRESETSHOW;
                        case KEY_DOWN:
                            dtmfSeek(0xff);
                            PRESETSHOW:
                            displayDtmfPreset();                           
                            break;                        
                    }
                }
                inputMode=0;
                lcdCls();
                displayRefreshFull();
                //timersReset();
            }
            break;
        case LP_DTMFINPUT:
            if(ACTIVE_VFOX.txPower)
            {
                displayDtmfWindow();
                inputPrepareDTMF(9, 28, 100, 2, &manualSeq);
            }
            break;
        case LP_FIXREVERSE:
            ACTIVE_VFO.bits.reversed = 0;
            displayVfoRefreshActiveNoDrawBG();
            channelSaveActive();
            break;
        case LP_REVERSE:
            reverseRxTx();
            bkApplyActiveVfo();
            displayVfoRefreshActiveNoDrawBG();
            channelSaveActive();
            break;
        case LP_EDITCHNAME:
            if(ACTIVE_VFOSTATE.mode)
            {   
                noChName=1;                         
                displayVfoRefreshActiveDrawBG();            
                noChName=0;                         
                inputPrepareString(11, VFO_CH_NAMEX, displayVfoPos(settings.activeVfo)+DIS(VFO_CH_NAMEY), 1, ACTIVE_VFO.name);
            }
            break;
        case LP_EDITFREQ_ENTERGRP:
            y = displayVfoPos(settings.activeVfo);
            if(ACTIVE_VFOSTATE.mode && ACTIVE_VFOSTATE.group)
            {
                yy = y+DIS(VFO_GROUPY);
                lcdFill(VFO_GROUPX, yy, 30, 8, COL_FWBGROUND);
                inputAsGroup = 1;
                inputPrepare(2, 0, VFO_GROUPX+6, yy, 0);
            }
            else                        
            {
                inputPrepare(4, 5, VFO_RXXPOS, y+DIS(VFO_RXYPOS), 4);
                inputParseKey(0x99);
            }
            break;
        case LP_FMTUNER:
            if(!ACTIVE_VFOSTATE.mode && !settings.disableFmt && fmtPlan!=0xff)
            {
                
                if(fmtActive)
                {
                    recallVfo();
                }
                else
                {
                    saveVfo();
                    ACTIVE_VFO.rxFreq.value = settings.lastFmtFreq;
                    fmtEqualize(&ACTIVE_VFO);
                }
                validateVfo(settings.activeVfo);
                bkApplyActiveVfo();
                displayVfoRefreshActiveDrawBG();
            }
            break;
        case LP_BLUETOOTH:
            BT_ON ^= 1;
            settings.bluetooth = BT_ON;
            btInUse=0;
            displayRefreshGeneral();
            break;
        case LP_KEYLOCK:
            if(settings.keyLock && settings.pinAction)
            {
                lcdFill(0,64,128,64,COL_VFOTX);
                lcdFill(48,95,32,16,COL_FWBGROUND);
                COL_BGROUND.value = COL_VFOTX.value;
                menuDrawPin();
                COL_BGROUND.value = COL_FWBGROUND.value;
                inputPrepare(4, 0, 48, 95, 2);
                enteringPin = 1;
            }
            else
                toggleKeylock();
            break;
        case LP_FREQCOUNT:
            if(!fmtActive)
                scanFreqCountStart();
            break;
        case LP_SCAN:
            scanStart();
            break;
        case LP_TXENTER:
            if(!fmtActive)
            {
                voicePlay(VOICE_ID_TX_OFFSET_FREQUENCY, 0);
                y = displayVfoPos(settings.activeVfo);
                inputPrepare(4, 5, VFO_TXXPOS, y+DIS(VFO_TXYPOS), 0);
                lcdFill(VFO_TXXPOS-8, y+DIS(VFO_TXYPOS), 68, 8, COL_BGROUND);
                fontCustomSymbol(3, VFO_TXXPOS-8, y+DIS(VFO_TXYPOS), COL_VFOTXFREQ);
                offsetInput=1;
            }            
            break;
        case LP_DUALWATCH:
            settings.dualWatch = !settings.dualWatch;
            bkApplyActiveVfo();
            displayRefreshGeneral();
            break;        
    }
    settingsSave();
}

void toggleKeylock(void)
{
    settings.keyLock=!settings.keyLock;
    voicePlay(settings.keyLock?VOICE_ID_LOCK:VOICE_ID_UNLOCK, 0);
    displayRefreshFull();   
    settingsSave();
}