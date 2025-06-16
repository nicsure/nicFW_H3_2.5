
/*
void HOLD(void)
{
    RXB_LED=1;
    delay(500);
    RXB_LED=0;
    TXB_LED=1;
    while(KEY_L2) 
    {
        feedTheDog();
    }
    TXB_LED=0;
    delay(1000);
}
*/

void clearXram(void)
{
    u8* xdata XRAM;
    XRAM = (u8*)bkReg;
    for(; XRAM!=&xvarsEnd; XRAM++)
    {
        *XRAM = 0;
    }
}

void init(void)
{    
    clearXram();
    P0CON = 0xff;
    P1CON = 0xdd;
    P2CON = 0xc6;
    P3CON = 0xef;
    P4CON = 0xfe;
    P5CON = 0xfd;
    exP34Mode = 1;
    P0 = 0xf;
    P1 = 0x02; //0xa;
    P2 = 0x40;
    P3 = 0;
    P4 = 0xb1;
    P5 = 0x20;
    TMCON &= 0xf7;
    TMOD |= 1;
    TL0 = 0; //0xe0;
    TH0 = 0; //0xb1;
    TR0 = 0;
    ET0 = 1;
    TR0 = 1;
    ROMBNK = 0x0;
    UKSFR_DE = 8;
    UKSFR_DE |= 0x60;
    UKSFR_DE |= 0x80;
    exZrdMode = 0xa0;
    EA = 1;
    EXA3 = 0x50;
    exWdT0 = 4;
    exWdT1 = 5;
    exP04Mode = 3;
    exP05Mode = 3;
    feedTheDog();
    TMCON &= 0x1f;
    TMCON |= 0xe0;
    IOHCON0 = 0xaa;
    IOHCON0 = 0x55;
    IOHCON1 |= 2;
    COL_BGROUND.value = COL_FWBGROUND.value;
    lcdInit();
    BT_ON = 1;
    settings.lcdBrightness = 28;
    displayLogo();
    pwmInit();
    pwmSetPa(0);
    memFill(dtmfDigitBuffer, 11, 32);
	sinceLastDtmfDigit=10;
	dtmfDigitBuffer[11]=0;
    //lcdFill(0,0,128,128,COL_BLACK);
    //fontDraw8x16(DIFFERENTIAL,4,40,COL_MENU);
    //while(KEY_L1)
    //{
    //    delay(500);
    //    HLED ^= 1;
    //    feedTheDog();
    //}



    FONT_SCK = 0;
    FONT_CS = 1;
    FONT_SI = 0;

    settings.rxSplit = 2800;
    settings.txSplit = 2800;
    settings.squelch = 2;
    settings.step = 1250;
    settings.micGain = 25;
    settings.txDeviation = 64;
    settings.scanRange = 100;    
    settings.repeaterTone = 1750;
    settings.dtmfDev = 32;
    settings.sqNoiseLev = 47;
    settings.voxTail = 20;
    settings.pin = 1234;
    settings.stDev = 74;
    settings.noiseCeiling = 53;
    amGain=40;

    step833Counter = 1;

    channelLoadMap();

    if(KEY_L3)
        settingsLoad();
    else
    {
        HLED=1;
        feedTheDog();
        delay(500);
        feedTheDog();
        HLED=0;
    }

    if(!settings.gain0 || settings.gain0>42 ||
        !settings.gain1 || settings.gain1>42 ||
        !settings.gain2 || settings.gain2>42 ||
        !settings.gain3 || settings.gain3>42) {
         bkResetAgcTables();
    }
    if(settings.rfiCompAmount>30) settings.rfiCompAmount=0;

    if(settings.pinAction==2)
        settings.keyLock=1;

    uartInit();

    //uartSendByte(sizeof(settings));

    //U16 tmp1;
    //tmp1.value = (u16)&xdataEnd;
    //btInUse=0;
    //uartSendByte(tmp1.bytes.hi);
    //btInUse=0;
    //uartSendByte(tmp1.bytes.lo);


    lcdGamma();
    lcdInvert(settings.lcdInverted);

    eepromRead(0x1a00, planMagic.array, 202);    
    if(planIsValid())
    {
        //eepromRead(0x1dff, (u8*)&vhfPeakSetting, 1);
        //eepromRead(0x1dfd, (u8*)&uhfPeakSetting, 1);  
        //eepromRead(0x1dfb, (u8*)&xtal671, 1);  
        planFindFMT();
    }
    //else
    //{
    //    vhfPeakSetting = 255;
    //    uhfPeakSetting = 255;
    //    xtal671 = 0;
    //}
    calibLoad();

    bkReg[0x30].value = 0xBFF1;
    bkInit();

    bkSet30(0);
    bkSetModulation(0, 0);
    
    BEEP=0;
    scanDirection = 1;
    externalKey=KEY_NONE;


    keypadPressed = KEY_NONE;
    singlePress = KEY_NONE;
    longPress = KEY_NONE;

    delay(1000);
    while(!KEY_L2)
        feedTheDog();
    pwmSetBl(0);
    lcdCls();
    settings.activeVfo = settings.activeVfo ? 0 : 1; // potential code shrink
    radioToggleVfoMode(ACTIVE_VFOSTATE.mode, ACTIVE_VFOSTATE.group, 0);
    settings.activeVfo = settings.activeVfo ? 0 : 1;
    radioToggleVfoMode(ACTIVE_VFOSTATE.mode, ACTIVE_VFOSTATE.group, 0);
    lcdTimer = settings.lcdTimeout;
    BT_ON = settings.bluetooth;
    displayRefreshFull();
    displayRefreshGeneral();
    lcdBacklight(1);
    initComplete = 1;
    


}

void loop(void)
{
    while(1)
    {
        feedTheDog();
        uartTick();
        if(!(inputMode & INPUTMODE_SERIAL)) {
            timers();
        }
    }
}

void settingsLoad(void)
{
    eepromRead(EEPROM_SETTINGS_ADDR, (u8*)&settings, 2);
    if(settings.magic==SETTINGSMAGIC)
    {
        eepromRead(EEPROM_SETTINGS_ADDR, (u8*)&settings, sizeof(settings));
    }
}

void settingsSave(void)
{
    reqSettingsSave = 1;
}

void settingsWrite(void)
{
    settings.magic=SETTINGSMAGIC;
    eepromWrite(EEPROM_SETTINGS_ADDR, (u8*)&settings, sizeof(settings));
    calibSave();
}

void feedTheDog(void)
{
    IOHCON0 = 0xaa;
    IOHCON0 = 0x55;
    IOHCON1 |= 1;
}
