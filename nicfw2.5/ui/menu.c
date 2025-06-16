const MENU code squelchMenu = {
    VALUE8,
    0,
    9,
    VOICE_ID_SQUELCH,
    &settings.squelch,
    "Squelch",
};

const MENU code squelchNoiseMenu = {
    VALUE8,
    15,
    55,
    VOICE_NONE,
    &settings.sqNoiseLev,
    "Sq Noise Lev"
};

const MENU code noiseCeilingMenu = {
    VALUE8,
    15,
    95,
    VOICE_NONE,
    &settings.noiseCeiling,
    "Noise Ceiling"
};

const MENU code txPowerMenu = {
    VALUE8ZO,
    0,
    255,
    VOICE_ID_POWER,
    &txPowerMenuVal,
    "TX Power",
};

const MENU code scrambleMenu = {
    VALUE8ZO,
    0,
    10,
    VOICE_NONE,
    &settings.scrambleFreq,
    "Scrambler",
};

const MENUOPTS2 code bandwidthMenu = {
    OPTION,
    0,
    1,
    VOICE_ID_CHANNEL_BANDWIDTH,
    &bandwidthMenuVal,
    "Bandwidth",
    { optionWide, optionNarrow }
};

const MENUOPTS2 code dualWatchMenu = {
    OPTION,
    0,
    1,
    VOICE_ID_DUAL_STANDBY,
    &settings.dualWatch,
    "Dual Watch",
    { optionOff, optionOn }
};

const MENUOPTS2 code busyLockMenu = {
    OPTION,
    0,
    1,
    VOICE_ID_BUSY_LOCKOUT,
    &busyLockMenuVal,
    "Busy Lock",
    { optionOff, optionOn }
};

const MENUOPTS4 code modulationMenu = {
    OPTION,
    0,
    3,
    VOICE_NONE,
    &modulationMenuVal,
    "Modulation",
    { AUTO, FM, AM, USB }
};

const MENU16 code txCtcssMenu = {
    VALUECTS,
    0,
    3000,
    1,
    VOICE_ID_CTCSS,
    &txSubToneMenuVal,
    "TX CTCSS",
};

const MENU16 code txDcsMenu = {
    VALUEDCS,
    0,
    0x1ff,
    0,
    VOICE_ID_DCS,
    &txSubToneMenuVal,
    "TX DCS",
};

const MENU16 code rxCtcssMenu = {
    VALUECTS,
    0,
    3000,
    1,
    VOICE_ID_CTCSS,
    &rxSubToneMenuVal,
    "RX CTCSS",
};

const MENU16 code rxDcsMenu = {
    VALUEDCS,
    0,
    0x1ff,
    0,
    VOICE_ID_DCS,
    &rxSubToneMenuVal,
    "RX DCS",
};

const MENU16 code stepMenu = {
    VALUE16,
    1,
    50000,
    2,
    VOICE_ID_FREQUENCY_STEP,
    &settings.step,
    "Step",
};

const MENUOPTS3 pttModeMenu = {
    OPTION,
    0,
    2,
    VOICE_NONE,
    &settings.pttMode,
    "PTT Mode",
    { DUAL, SINGLE, HYBRID }
};

const MENUOPTS2 code txModMeterMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.txModMeter,
    "TX Mod Meter",
    { optionOff, optionOn }
};

const MENU code micGainMenu = {
    VALUE8,
    0,
    31,
    VOICE_NONE,
    &settings.micGain,
    "Mic Gain"
};

const MENU code txDeviationMenu = {
    VALUE8,
    0,
    99,
    VOICE_NONE,
    &settings.txDeviation,
    "TX Deviation"
};

const MENU code xtal671Menu = {
    VALUE8S,
    0,
    255,
    VOICE_NONE,
    //&settings.xtal671,
    &tuning.xtal671,
    "XTAL 671"
};

const MENU16 code rxSplitMenu = {
    VALUE16,
    2000,
    4000,
    1,
    VOICE_NONE,
    &settings.rxSplit,
    "RX VHF->UHF"
};

const MENU16 code txSplitMenu = {
    VALUE16,
    2000,
    4000,
    1,
    VOICE_NONE,
    &settings.txSplit,
    "TX VHF->UHF"
};

const MENUOPTS3 code toneMonitorMenu = {
    OPTION,
    0,
    2,
    VOICE_NONE,
    &settings.toneMonitor,
    "Tone Monitor",
    { optionOff, optionOn, CLONE }
};

const MENUOPTS4 code battStyleMenu = {
    OPTION,
    0,
    3,
    VOICE_NONE,
    &settings.battStyle,
    "Batt Style",
    { optionOff, ICON, PERCENT, VOLTS }
};

const MENUOPTS4 code keyTonesMenu = {
    OPTION,
    0,
    3,    
    VOICE_ID_BEEP_PROMPT,
    &settings.keyTones,
    "Key Tones",
    { optionOff, optionOn, DIFFERENTIAL, VOICE }
};

const MENU16 code scanRangeMenu = {
    VALUE16,
    1,
    60000,
    2,
    VOICE_NONE,
    &settings.scanRange,
    "VFO Scan Range"
};

const MENU16 code scanPersistMenu = {
    VALUE16,
    0,
    200,
    1,
    VOICE_NONE,
    &settings.scanPersist,
    "Scan Persist"
};

const MENU code scanResumeMenu = {
    VALUE8ZO,
    0,
    250,
    VOICE_NONE,
    &settings.scanResume,
    "Scan Resume"
};

const MENU code ultraScanMenu = {
    VALUE8ZO,
    0,
    20,
    VOICE_NONE,
    &settings.ultraScan,
    "Scan Ultra"
};

const MENU code lcdBlMenu = {
    VALUE8,
    0,
    35,
    VOICE_ID_BACKLIGHT_SELECTION,
    &settings.lcdBrightness,
    "LCD Brightness",
};

const MENU code lcdTimeoutMenu = {
    VALUE8ZO,
    0,
    250,
    VOICE_NONE,
    &settings.lcdTimeout,
    "LCD Timeout"
};

const MENU code breatheMenu = {
    VALUE8ZO,
    0,
    30,
    VOICE_NONE,
    &settings.breathe,
    "Heartbeat"
};

const MENU code dtmfDevMenu = {
    VALUE8,
    0,
    127,
    VOICE_NONE,
    &settings.dtmfDev,
    "DTMF Volume"
};

const MENU16 dtmfEndPauseMenu = {
    VALUE16,
    0,
    20,
    1,
    VOICE_NONE,
    &settings.dtmfEndPause,
    "DTMF SeqEnd",
};


const MENUOPTS3 code dtmfDecodeMenu = {
    OPTION,
    0,
    2,    
    VOICE_NONE,
    &settings.dtmfDecode,
    "DTMF Decode",
    { optionOff, optionAlways, optionSquelched }
};

const MENU16 code repeaterToneMenu = {
    VALUE16,
    100,
    4000,
    0,
    VOICE_ID_REPEATER,
    &settings.repeaterTone,
    "Repeater Tone",
};

const MENU code gammaMenu = {
    VALUE8,
    0,
    3,
    VOICE_NONE,
    &settings.gamma,
    "LCD Gamma"
};

const MENU code powerMenu = {
    VALUE8ZO,
    0,
    20,
    VOICE_NONE,
    &settings.powerSave,
    "Power Save"
};

const MENUOPTS4 code steMenu = {
    OPTION,
    0,
    3,
    VOICE_NONE,
    &settings.ste,
    "Sq Tail Elim",
    { optionOff, RX_LABEL, TX_LABEL, BOTH }
};

const MENUOPTS3 code sBarStyleMenu = {
    OPTION,
    0,
    2,
    VOICE_NONE,
    &settings.sBarStyle,
    "S-Bar Style",
    { SEGMENT, STEPPED, SOLID }
};

const MENU code rfGainMenu = {
    VALUE8ZO,
    0,
    42,
    VOICE_NONE,
    &settings.rfGain,
    "RF Gain"
};

const MENU code gain0Menu = {
    VALUE8,
    1,
    42,
    VOICE_NONE,
    &settings.gain0,
    "AGC Table 0"
};
const MENU code gain1Menu = {
    VALUE8,
    1,
    42,
    VOICE_NONE,
    &settings.gain1,
    "AGC Table 1"
};
const MENU code gain2Menu = {
    VALUE8,
    1,
    42,
    VOICE_NONE,
    &settings.gain2,
    "AGC Table 2"
};
const MENU code gain3Menu = {
    VALUE8,
    1,
    42,
    VOICE_NONE,
    &settings.gain3,
    "AGC Table 3"
};
const MENU code rfiCompMenu = {
    VALUE8ZO,
    0,
    30,
    VOICE_NONE,
    &settings.rfiCompAmount,
    "RFI Comp",
};


const MENU code addGroupMenu = {
    VALUE8L,
    0,
    15,
    VOICE_NONE,
    &addGroupTrigger,
    "Add Group"
};

const MENU code delGroupMenu = {
    VALUE8L,
    0,
    15,
    VOICE_NONE,
    &delGroupTrigger,
    "Remove Group"
};

const MENU code voxMenu = {
    VALUE8ZO,
    0,
    15,
    VOICE_ID_VOX,
    &settings.vox,
    "VOX",
};

const MENU16 voxTailMenu = {
    VALUE16,
    5,
    50,
    1,
    VOICE_ID_VOX,
    &settings.voxTail,
    "VOX Tail",
};

const MENU code txTimeoutMenu = {
    VALUE8ZO,
    0,
    250,
    VOICE_ID_TRANSMIT_OVER_TIME,
    &settings.txTimeout,
    "TX Timeout",
};

const MENU code dimmerMenu = {
    VALUE8ZO,
    0,
    14,
    VOICE_NONE,
    &settings.dimmer,
    "Dim Brightness",
};

const MENU code dtmfSpeedMenu = {
    VALUE8,
    0,
    20,
    VOICE_NONE,
    &settings.dtmfSpeed,
    "DTMF Speed",
};

const MENUOPTS2 code noiseGateMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.noiseGate,
    "Noise Gate",
    { optionOff, optionOn }
};

const MENU code scanUpdateMenu = {
    VALUE8ZO,
    0,
    50,
    VOICE_NONE,
    &settings.scanUpdate,
    "Scan Update",
};

const MENUOPTS4 code aslMenu = {
    OPTION,
    0,
    3,
    VOICE_NONE,
    &settings.asl,
    "ASL Support",
    { optionOff, &COSI[2], USB, COSI }
};

const MENUOPTS3 code wlCloneMenu = {
    OPTION,
    0,
    2,
    VOICE_NONE,
    &wlCloneTrigger,
    "Wireless Copy",
    { CANCEL, RECEIVE, SEND }
};

const MENUOPTS2 code disableFmtMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.disableFmt,
    "Disable FMT",
    { optionNo, optionYes }
};

const MENU16 code pinMenu = {
    VALUE16,
    1000,
    9999,
    0,
    VOICE_NONE,
    &settings.pin,
    "PIN",
};

const MENUOPTS3 code pinActionMenu = {
    OPTION,
    0,
    2,
    VOICE_NONE,
    &settings.pinAction,
    "PIN Action",
    { optionOff, optionOn, POWERON }
};

const MENU code afFiltersMenu = {
    VALUE8,
    0,
    8,
    VOICE_NONE,
    &settings.afFilters,
    "AF Filters",
};

const MENUOPTS2 code sBarAlwaysOnMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.sBarAlwaysOn,
    "SBar AlwaysOn",
    { optionOff, optionOn }
};

const MENUOPTS4 code pttIDMenu = {
    OPTION,
    0,
    3,
    VOICE_NONE,
    &pttIDMenuVal,
    "PTT ID",
    { optionOff, BOT, EOT, BOTH }
};

const MENU code dwDelayMenu = {
    VALUE8,
    1,
    30,
    VOICE_NONE,
    &settings.dwDelay,
    "DualWatch Delay",
};

const MENUOPTS code ifFreqMenu = {
    OPTION,
    0,
    6,
    VOICE_NONE,
    &settings.ifFreq,
    "IF (kHz)",
    { IF1, IF2, IF3, IF4, IF5, IF6, IF7 }
};

const MENU code stDevMenu = {
    VALUE8,
    0,
    127,
    VOICE_NONE,
    &settings.stDev,
    "SubTone Dev",
};

const MENUOPTS2 code vfoLockMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.vfoLock,
    "VFO DW Lock",
    { optionOff, optionOn }
};

const MENUOPTS2 code bluetoothMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.bluetooth,
    "Bluetooth",
    { optionOff, optionOn }
};

const MENUOPTS2 code txCurrentMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.txCurrent,
    "TX Current",
    { optionOff, optionOn }
};

const MENUOPTS2 code amAgcMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.amAgc,
    "AM AGC Fix",
    { optionOff, optionOn }
};



void menuDrawPin(void)
{
    fontDraw8x8(pinMenu.title, 40, 74, COL_MENU, 1); // enable later
}

const void* code menus[] = {
    &squelchMenu,
    &stepMenu,

    &bandwidthMenu,
    &txPowerMenu,
    &modulationMenu,
    &busyLockMenu,
    &txCtcssMenu,
    &txDcsMenu,
    &rxCtcssMenu,
    &rxDcsMenu,
    &addGroupMenu,
    &delGroupMenu,
    &pttIDMenu,

    &scrambleMenu,

    &scanRangeMenu,
    &scanPersistMenu,
    &scanResumeMenu,
    &ultraScanMenu,
    &scanUpdateMenu,

    &txTimeoutMenu,
    &txModMeterMenu,
    &pttModeMenu,    
    &micGainMenu,    
    &dtmfDecodeMenu,
    &repeaterToneMenu,
    &voxMenu,
    &voxTailMenu,

    &toneMonitorMenu,
    &dualWatchMenu,


    &battStyleMenu,
    &lcdBlMenu,
    &dimmerMenu,
    &lcdTimeoutMenu,
    &breatheMenu,
    &powerMenu,



    &steMenu,


    &keyTonesMenu,
    &wlCloneMenu,
    &pinMenu,
    &pinActionMenu,
    &bluetoothMenu,
};

const void* code menus_adv[] = {
    &squelchNoiseMenu,
    &noiseCeilingMenu,
    &txDeviationMenu,
    &dtmfDevMenu,
    &dtmfSpeedMenu,
    &dtmfEndPauseMenu,
    &dwDelayMenu,
    &vfoLockMenu,
    &noiseGateMenu,
    &xtal671Menu,
    &rxSplitMenu,
    &txSplitMenu,
    &gammaMenu,
    &sBarStyleMenu,
    &sBarAlwaysOnMenu,
    &rfGainMenu,
    &stDevMenu,
    &disableFmtMenu,
    &aslMenu,
    &afFiltersMenu,
    &ifFreqMenu,
    &txCurrentMenu,
    &gain0Menu,
    &gain1Menu,
    &gain2Menu,
    &gain3Menu,    
    &rfiCompMenu,
    &amAgcMenu,
};

void menuDrawBank(void)
{
    lcdFill(0, 32, 128, 30, COL_MENU);
    lcdFill(2, 34, 124, 26, COL_FWBGROUND);
    fontDraw8x16(menuAdvanced?"Advanced Menu":"User Menu", 5, 41, COL_MENUEDIT);
}

void menuInit(void)
{
    menuTens = 0;
    menuEdit = 0;
    inputMode |= INPUTMODE_MENU;
    channelActiveToMenu();
    menuDrawBank();
    menuDraw(NEWVALUE_1ST);
    voicePlay(VOICE_ID_MENU, 0);
}

void menuTick(void)
{
    u16 newVal;
    u8 key, nm, tens, units;
    void* menu;    
    key = keypadSinglePress();
    if(longPress==KEY_UP || longPress==KEY_DOWN) key=longPress;
    if(menuEdit)
    {
        if(inputState==INPUT_CANCELLED)
        {
            newVal = menuTemp;
        }
        else
        if(inputState==INPUT_APPLIED)
        {
            newVal = (u16)inputValue;
        }
        else
        if(key<10)
        {
            lcdFill(0, 95, 128, 16, menuBG);
            inputPrepare(menuUnits, menuDecimals, 13, 95, FONT8X16NUM);
            inputParseKey(key);
            return;
        }
        else
        switch(key)
        {
            case KEY_HASH:
                if(octalInput)
                    newVal = NEWVALUE_KEEPOLD;
                else
                    return;
                break;
            case KEY_EXIT:
                newVal = menuTemp;                
                menuEdit = 0;
                voicePlay(VOICE_ID_CANCEL, 0);
                break;                
            case KEY_MENU:
                newVal = NEWVALUE_1ST;
                menuEdit = 0;
                voicePlay(VOICE_ID_CONFIRM, 0);                
                break;
            case KEY_UP:
                newVal = NEWVALUE_ADD1;
                break;            
            case KEY_DOWN:
                newVal = NEWVALUE_SUB1;
                break;            
            default:
                return;
        } 
        inputState=INPUT_IDLE;      
        menuDraw(newVal);
    }
    else
    {
        if(key<10)
        {
            nm = key;
            if(menuTens)
            {
                nm+=(menuNumber*10);
                menuTens=0;
            }
            else
                menuTens=1;
            if(nm>MENU_COUNT) 
            {
                nm = key;
                menuTens=0;
            }
            menuNumber=nm;
        }
        else    
        switch(key)
        {
            case KEY_HASH:
                menuAdvanced=!menuAdvanced;
                menuDrawBank();
                break;            
            case KEY_FLSH:
                fontDraw6x8(CRC, 39, 116, COL_MENU);
                fontDraw6x8(crc32()?OK:BAD, 60, 116, COL_MENU);
                return;
            case KEY_EXIT:
                voicePlay(VOICE_ID_MENU, 1);
                voicePlay(VOICE_ID_OFF, 0);
                octalInput=0;
                channelActiveFromMenu();
                validateVfo(settings.activeVfo);
                inputMode &= ~INPUTMODE_MENU;
                lcdCls();
                bkApplyActiveVfo();
                displayRefreshFull();
                settingsSave();
                return;
            case KEY_MENU:
                if(menuUnits)
                {
                    menuEdit=1;
                    menuTens=0;
                    if(menuVoice != 0xff)
                    {
                        menu = menusBank[menuNumber];
                        if(menu == &txCtcssMenu || menu == &txDcsMenu) // enable later
                            voicePlay(VOICE_ID_TRANSMIT_OVER_TIME, 0x40);
                        if(menu == &voxTailMenu)
                            voicePlay(VOICE_ID_OFF, 1);
                        voicePlay(menuVoice, 0);
                        break;
                    }
                    voicePlay(VOICE_ID_MENU, 1);
                    if(menuNumber<11)
                        voicePlay(menuNumber, 0);
                    else if(menuNumber<21)
                        voicePlay(menuNumber+47, 0);
                    else
                    {
                        tens = menuNumber/10;
                        units = menuNumber%10;
                        voicePlay(tens+65, units?1:0);
                        if(units)
                            voicePlay(units, 0);
                    }                    
                }
                break;
            case KEY_UP:
                menuNumber++;
                break;
            case KEY_DOWN:
                menuNumber--;
                break;
            default:
                return;
        }
        if(menuNumber==0xFF) menuNumber=MENU_COUNT;
        if(menuNumber>MENU_COUNT) menuNumber=0;
        menuDraw(NEWVALUE_1ST);
    }
}

void menuDraw(const u16 newValue)
{
    
    void* menu;
    char* title;
    char* value;
    bit zeroIsOff;
    MENU* ms;
    MENU16* ms16;
    u8 v, max;
    menuBG.value = menuEdit?COL_MENUEDITBG.value:COL_MENUBG.value;
    // COL_MENUEDITBG
    octalInput = 0;
    lcdFill(0, 64, 128, 25, COL_MENU);
    lcdFill(0, 89, 128, 37, menuBG);
    menu = menusBank[menuNumber];
    zeroIsOff = 0;
    switch(MENU_TYPE)
    {
        default: return;
        case VALUEDCS:
            {
                ms16 = (MENU16*)menu;
                title = ms16->title;
                menuVoice = ms16->voicePrompt;
                if(MENU_VAR16 && !(MENU_VAR16 & 0x8000))
                {
                    MENU_VAR16 &= 0xbfff;
                    menuUnits=0;
                    value=(char*)NA;
                    break;
                }
                octalInput = 1;
                menuDecimals=0;
                menuUnits=3;
                switch(newValue)
                {
                    case NEWVALUE_KEEPOLD:
                        if(MENU_VAR16)
                            MENU_VAR16 ^= 0x4000;
                        break;
                    case NEWVALUE_1ST:
                        menuTemp = MENU_VAR16;
                        break;
                    case NEWVALUE_ADD1: 
                        MENU_VAR16 = nextDcs(1, MENU_VAR16); 
                        break;
                    case NEWVALUE_SUB1:
                        MENU_VAR16 = nextDcs(0, MENU_VAR16); 
                        break;
                    default: MENU_VAR16 = newValue;
                }
                sprint_dcs(MENU_VAR16);
                value=TXT;
            }
            break;

        case VALUECTS:
        case VALUE16ZO:
            zeroIsOff = 1;
            goto VALUE16JUMP;
        case VALUE16:
            VALUE16JUMP:
            {
                ms16 = (MENU16*)menu;
                title = ms16->title;
                menuVoice = ms16->voicePrompt;
                if(MENU_TYPE == VALUECTS && (MENU_VAR16 & 0x8000))
                {
                    menuUnits=0;
                    value=(char*)NA;
                    break;
                }
                switch(newValue)
                {
                    case NEWVALUE_KEEPOLD: break;
                    case NEWVALUE_1ST: menuTemp = MENU_VAR16; break;
                    case NEWVALUE_ADD1:
                        if(MENU_TYPE == VALUECTS)
                            MENU_VAR16 = nextCtcss(1, MENU_VAR16); 
                        else
                            (MENU_VAR16)++; 
                        break;
                    case NEWVALUE_SUB1:
                        if(MENU_TYPE == VALUECTS)
                            MENU_VAR16 = nextCtcss(0, MENU_VAR16); 
                        else
                            (MENU_VAR16)--;
                        break;
                    default: MENU_VAR16 = newValue;
                }           
                menuDecimals=ms16->decimals;
                menuUnits=countDigits(ms16->max/(u16)Pow10(ms16->decimals));
                if(MENU_VAR16 == 0xFFFF || MENU_VAR16 < ms16->min) MENU_VAR16=ms16->max; else
                if(MENU_VAR16 > ms16->max) MENU_VAR16=ms16->min;
                if(!zeroIsOff || MENU_VAR16)
                {
                    SPRINT_NUMBER(TXT, MENU_VAR16, menuUnits, menuDecimals?menuDecimals:255, 1, 1);
                    value = TXT;
                }
                else
                    value = (char*)optionOff;                
            }          
            break;
        case VALUE8ZO:
            zeroIsOff = 1;
            goto VALUE8JUMP;
        case VALUE8:
        case VALUE8S:
        case VALUE8L:
            VALUE8JUMP:
            {
                ms = (MENU*)menu;
                switch(newValue)
                {
                    case NEWVALUE_KEEPOLD: break;
                    case NEWVALUE_1ST:
                        menuTemp = MENU_VAR;
                        break;
                    case NEWVALUE_ADD1: (MENU_VAR)++; break;
                    case NEWVALUE_SUB1: (MENU_VAR)--; break;
                    default: MENU_VAR = (u8)newValue;
                }
                if(MENU_VAR == 0xFF && ms->max!=0xff) MENU_VAR=ms->max; else
                if(MENU_VAR < ms->min) MENU_VAR=ms->max; else
                if(MENU_VAR > ms->max) MENU_VAR=ms->min;
                title = ms->title;
                menuVoice = ms->voicePrompt;
                menuUnits = countDigits(ms->max);
                menuDecimals = 0;
                if(menu == &lcdBlMenu)
                    lcdBacklight(1);
                if(menu == &gammaMenu)
                    lcdGamma();
                if(!zeroIsOff || MENU_VAR)
                {
                    if(MENU_TYPE==VALUE8S)
                    {
                        v = (u8)(MENU_VAR&0xff);
                        TXT[0] = (v&0x80) ? '-':'+';
                        TXT[1] = 0;
                        SPRINT_NUMBER(&TXT[1], TXT[0]=='-'?(v^0xff)+1:v, menuUnits, 255, 1, 1);
                    }
                    else
                    if(MENU_TYPE==VALUE8L)
                    {
                        if(!ACTIVE_VFOSTATE.mode)
                            memCpy2(NA, TXT, 4);
                        else
                        if(!MENU_VAR)
                            memCpy2(CANCEL, TXT, 7);
                        else
                        {
                            TXT[0]=MENU_VAR+64;
                            TXT[1]=0;
                        }
                    }
                    else
                    {
                        if(menu == &scrambleMenu) {
                            SPRINT_NUMBER(TXT, (MENU_VAR*100)+2500, 4, 255, 1, 1); 
                            fontChipDrawText(TXT, &FONT8x16, 53, 95, COL_MENU, 0);
                        }                          
                        SPRINT_NUMBER(TXT, MENU_VAR, menuUnits, 255, 1, 1);                    
                    }
                    value = TXT;
                }
                else
                    value = (menu==&rfGainMenu)?(char*)AGC:(char*)optionOff;
            }
            break;
        case OPTION:
            {
                ms = (MENU*)menu;
                switch(newValue)
                {
                    case NEWVALUE_KEEPOLD: break;
                    case NEWVALUE_1ST:
                        menuTemp = MENU_VAR;
                        if(menu==&wlCloneMenu && MENU_VAR)
                        {
                            fskWlClone(MENU_VAR==2);
                            MENU_VAR=0;
                            return;
                        }                        
                        break;
                    case NEWVALUE_ADD1: (MENU_VAR)++; break;
                    case NEWVALUE_SUB1: (MENU_VAR)--; break;
                    default: MENU_VAR = newValue;
                }
                menuUnits = 1;
                menuDecimals = 0;
                if(MENU_VAR == 0xFF) MENU_VAR=ms->max; else
                if(MENU_VAR > ms->max) MENU_VAR=0;
                title = ms->title;
                menuVoice = ms->voicePrompt;


                value = ((MENUOPTS*)menu)->opts[MENU_VAR];
            }
            break;
    }
    COL_BGROUND.value = menuBG.value;
    fontChipDrawText(value, &FONT8x16, 13, 95, menuEdit?COL_MENUEDIT:COL_MENU, 0);
    if(menu==&noiseCeilingMenu) {
        ceilingMenuActive = 1;
    } else {
        ceilingMenuActive = 0;
    }    
    if(menu==&txPowerMenu)
    {
        ms = (MENU*)menu;
        max = MENU_VAR;
        if(txMaxPowerMenuVal<max)
            max=txMaxPowerMenuVal;
        sprint_power(max, ACTIVE_VFOX.txIsVhf);
        fontDraw8x16(TXT, 82, 95, COL_MENUEDIT);
    }    

    TXT[2]='/';
    SPRINT_NUMBER(TXT, menuNumber, 2, 255, 0, 0);    
    SPRINT_NUMBER(&TXT[3], MENU_COUNT, 2, 255, 0, 1);    
    
    
    fontChipDrawText(TXT, &FONT6x8, 5, 116, COL_MENU, 0);
    fontChipDrawText(VERSION, &FONT6x8, 80, 116, COL_MENU, 0);
    COL_BGROUND.value = COL_MENU.value;
    fontChipDrawText(title, &FONT8x16, 5, 70, menuBG, 0);
    COL_BGROUND.value = COL_FWBGROUND.value; 
    
}



