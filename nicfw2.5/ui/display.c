
void displayDrawMeter(const u8 sig, const u8 mode)
{
    u8 adjsig, floorDbm, sigDbm, plus, sunit, i, z, green;
    char floorSign, sigSign;
    COLOR col;

    z = lastSig > sig ? lastSig - sig : sig - lastSig;

    if(squelchOpen && settings.rfiCompAmount && z<settings.rfiCompAmount && sig)
    {
        skipMeter = 1;
        return;
    }

    lastSig=sig;
    skipMeter=0;    


    if(inputMode || scopeActive) return;
    if(remoteActive)
    {
        remoteSendSBarYPos();
        uartSendByte(103);
        uartSendByte(sig);
        uartSendByte(xmitActive);
        uartSendNull();
    }
    adjsig = sig;
    if(mode==1) // tx
    {
        lcdFill(0, displayGetSBAR_YPOS(), 108, 8, COL_BGROUND);
        col.value = COL_SMETERTX.value;
        fontDraw8x8(TX_LABEL, 108, displayGetSBAR_YPOS(), COL_SMETERTX, 0);
    }
    else
    if(!(mode&1)) // rx
    {        
        // (reg/2)-160 = dbm
        floorDbm = (s8)(noiseFloor>>1) - 160;
        sigDbm = (s8)(bkReg[0x67].value>>1) - 160;
        floorSign = floorDbm&0x80?'-':'+';
        sigSign = sigDbm&0x80?'-':'+';
        if(floorSign=='-') floorDbm=(floorDbm^0xff)+1;
        if(sigSign=='-') sigDbm=(sigDbm^0xff)+1;
        // 012345678
        // -160/-160
        SPRINT_NUMBER(&TXT[1], sigDbm, 3, 255, 0, 0);
        SPRINT_NUMBER(&TXT[6], floorDbm, 3, 255, 0, 1);
        TXT[0]=sigSign;
        TXT[4]='/';
        TXT[5]=floorSign;
        if(mode==0)
        {
            fontDraw6x8(TXT, 45, displayGetSBAR_YPOS(), COL_DBM);
            fontDraw8x8(RX_LABEL, 108, displayGetSBAR_YPOS(), squelchOverride ? COL_SMETERMID : COL_SMETERLOW, 0);
        }
        if(mode==2)
        {
            lcdFill(45, displayGetSBAR_YPOS(), 54, 8, COL_BGROUND);
            if(RXA_LED)
                fontDraw8x8(STN_LABEL, 100, displayGetSBAR_YPOS(), COL_SMETERLOW, 0);
            else
                lcdFill(100, displayGetSBAR_YPOS(), 28, 8, COL_BGROUND);
        }


        plus = 0;
        sunit = sig/6;
        if(sunit>8)
        {
            sunit = 9;
            plus = sig-54;
        }
        TXT[0]='S';
        SPRINT_NUMBER(&TXT[1], sunit, 1, 255, 0, 1);
        fontChipDrawText(TXT, &FONT8x8, 4, displayGetSBAR_YPOS(), COL_SUNIT, 0);
        if(plus)
        {
            TXT[0]='+';
            SPRINT_NUMBER(&TXT[1], plus, 2, 255, 0, 1);
            fontChipDrawText(TXT, &FONT8x8, 20, displayGetSBAR_YPOS(), COL_PUNIT, 0);
        }
        else
            lcdFill(20, displayGetSBAR_YPOS(), 24, 8, COL_BGROUND);

        adjsig = (u8)(((u16)sig*27)>>4);
    }
    else // none
    {
        lcdFill(0, displayGetSBAR_YPOS(), 128, 8, COL_BGROUND);
    }
    remoteSuspendFill = 1;
    for(i=0, z=1; i<120; i+=2, z++)
    {
        if(z==5) z=0; 
        if(i>=adjsig)
        {
            col.value=COL_SMETEROFF.value;
        }
        else
        if(!(mode&1))
        {            
            green = i < 90 ? 61 : 240-(i<<1);
            col.RGB.r = i > 31 ? 31 : i;
            col.RGB.b = fmtActive ? 16 : 0; 
            col.RGB.gl = green & 0x07; // 000111
            col.RGB.gh = (green & 0x38)>>3; // 111000
        }
        switch(settings.sBarStyle)
        {
            default: // segment
                lcdFill(i+4, displayGetSMETER_YPOS(), 1, 6, col);
                break;
            case 1: // stepped
                lcdFill(i+4, displayGetSMETER_YPOS() + (z?3:0), 1, z?3:6, col);
                break;
            case 2: // solid
                lcdFill(i+4, displayGetSMETER_YPOS(), 2, 6, col);
                break;
        }
    }
    remoteSuspendFill = 0;
}

const u8 displayGetSMETER_YPOS(void)
{
    return settings.pttMode==1 ? SMETER_SPTT_YPOS : SMETER_DPTT_YPOS;
}

const u8 displayGetSBAR_YPOS(void)
{
    return settings.pttMode==1 ? SBAR_SPTT_YPOS : SBAR_DPTT_YPOS;
}

void displayDrawExNoise(const u8 value, const bit txMod)
{
    u8 w;
    COLOR col;
    if(inputMode || scopeActive || skipMeter) return;
    col.value = txMod?COL_SMETERTXMOD.value:COL_SMETEREXNOISE.value;
    if(remoteActive)
    {
        uartSendByte(104);
        uartSendByte(value);
        uartSendByte(xmitActive);
        uartSendNull();
    }
    remoteSuspendFill = 1;
    w = value>120?120:value;
    lcdFill(4, displayGetSMETER_YPOS()+7, w, 1, col);
    lcdFill(w, displayGetSMETER_YPOS()+7, 120-w, 1, COL_BGROUND);
    remoteSuspendFill = 0;
}

const char* code getModName(const u8 modulation)
{
    switch(modulation)
    {
        default: return (code char*)&FM;
        case 2: return (code char*)&AM;
        case 3: return (code char*)&USB;
        case 4: return (code char*)&NR;
    }
}

const char* code displayModName(const channelXtra* vfox)
{
    if(vfox->isFmTuner) return (code char*)&FMT;
    return getModName(vfox->modulation);
}

void displayVfoRefresh(const u8 vfoNumber, const bit drawBG)
{
    displayVfo(vfoNumber, drawBG);
}

void displayVfoRefreshActiveDrawBG(void)
{
    displayVfoRefresh(settings.activeVfo, 1);
}

void displayVfoRefreshActiveNoDrawBG(void)
{
    displayVfoRefresh(settings.activeVfo, 0);
}


const u8 flagsYPOS(void)
{
    return settings.pttMode==1 ? FLAGS_YPOS_SINGLE : FLAGS_YPOS_DUAL;
}

void displayRefreshGeneral(void)
{
    u8 ypos;
    ypos = flagsYPOS();
    if(dtmfDisplayTime) {
        fontDraw8x8((char*)dtmfDigitBuffer, 0, ypos, COL_SMETERMID, 0);
        return;
    }    
    if(!scopeActive)
    {
        displayDrawMeter(0, 3);    
        displayDrawExNoise(0, 0);
    }
    if(!inputMode)
    {
        if(settings.vfoLock && settings.dualWatch && settings.pttMode)
        {
            TXT[1]=0;
            TXT[0] = settings.setVfo+65;
            fontDraw8x8(TXT, FLAGS_DWX, ypos, COL_VFOLABELS, 0);
        }
        else
            fontCustomSymbol(settings.dualWatch?0:13, FLAGS_DWX, ypos, COL_VFOLABELS);
        fontCustomSymbol(settings.keyLock?7:lpShift?9:13, FLAGS_KLX, ypos, COL_VFOLABELS);
        fontCustomSymbol(settings.bluetooth?12:13, FLAGS_BTX, ypos, COL_VFOCORNER2);
        fontCustomSymbol(settings.vox?6:13, FLAGS_VOXX, ypos, COL_VFOCORNER2);
        fontCustomSymbol(settings.pttMode?16:15, FLAGS_PTTMODE, ypos, COL_VFOCORNER2);

        //if(rfiAdjust) TXT[0]='@'; else
        if(settings.asl==1) TXT[0]='C'; else
        if(settings.asl==2) TXT[0]='U'; else
        if(settings.asl==3) TXT[0]='I'; else
        if(settings.scrambleFreq) TXT[0]='!'; else TXT[0]=' ';
        TXT[1]=0;
        fontDraw8x8(TXT, FLAGS_ASLX, ypos, COL_ASLFLAG, 0);
    }
}

void displayRefresh(const bit drawBG)
{
    if(scopeActive && settings.pttMode==1)
        settings.pttMode=0;
    displayVfoRefresh(0, drawBG);
    displayVfoRefresh(1, drawBG);
    displayRefreshGeneral();   
}

void displayRefreshFull(void)
{
    displayRefresh(1);
}

const u8 displayVfoPos(const u8 vfoNumber)
{
    return settings.pttMode==1 ? VFOS_YPOS : vfoNumber ? VFOB_YPOS : VFOA_YPOS;
    //return !vfoNumber || settings.pttMode==1 ? VFOA_YPOS : VFOB_YPOS;
}

const u8 DIS(const u8 val)
{
    return settings.pttMode==1 ? val<<1 : val;
}

const u16 colVfo(void)
{
    if(xmitActive) return COL_VFOTX.value;
    if(loopMode&(LOOPMODE_SCAN | LOOPMODE_SCANMONITOR | LOOPMODE_FREQCOUNTER)) return COL_VFOSCAN.value;    
    return squelchOpen ? COL_VFORX.value : COL_VFOIDLE.value;
}

void displayVfo(const u8 vfoNumber, const bit drawBG)
{
    bit isActive;
    channelInfo* vfo;
    channelXtra* vfox;
    u8 vpos, LRG;
    u32 upper;
    u32 lower;
    COLOR rxFreqCol;
    u8 symbol;

    if(inputMode) return;
    isActive = (vfoNumber == settings.activeVfo);
    if((settings.pttMode==1 || scopeActive) && !isActive)
        return;
    dimColor=!isActive;
    vfo = &VFO[vfoNumber];
    vfox = &VFOX[vfoNumber];
    vpos = displayVfoPos(vfoNumber);
    upper = xmitActive?vfo->txFreq.value:vfo->rxFreq.value;
    lower = xmitActive?vfo->rxFreq.value:vfo->txFreq.value;
    
    if(isActive && !VFO_CHANGERXFREQNOTBG && settings.pttMode!=1)
    {
        COL_BGROUND.value = colVfo();     
    }

    if(drawBG)
        lcdFill(0, vpos, 128, DIS(VFO_HEIGHT), COL_BGROUND);

    sprint_power(vfox->txPower, vfox->txIsVhf);
    fontDraw6x8(TXT, VFO_POWERX, vpos+DIS(VFO_POWERY), COL_VFOPOWER);
    


    memCpySpc(vfox->number>1 ? vfo->name : &SPACE12, TXT, 12);
    LRG = LARGE_CH_NAME;
    if(isActive && vfox->number<2)
    {
        LRG = 0;
        if(loopMode==LOOPMODE_SCAN)
            memCpySpc(scanActivityMode?ACTIVITY:SCANNING, TXT, 12);
        else 
        if(loopMode==LOOPMODE_SCANMONITOR)
            memCpySpc(MONITORING, TXT, 12);
        else 
        if(loopMode==LOOPMODE_FREQCOUNTER)
            memCpySpc(FREQCOUNT, TXT, 12);
        else
            LRG=LARGE_CH_NAME;
    }
    

    //TXT[LARGE_CH_NAME ? 9 : 12]=0;
    if(!noChName)
        fontDraw8x8(TXT, VFO_CH_NAMEX, vpos+DIS(VFO_CH_NAMEY), COL_VFOCHNAME, LRG);

    if(vfox->number>1 || !isActive || loopMode!=LOOPMODE_SCAN)
    {
        rxFreqCol.value = VFO_CHANGERXFREQNOTBG && isActive ? colVfo() : COL_VFORXFREQ.value;
        displayFreq(&upper, VFO_RXXPOS, vpos+DIS(VFO_RXYPOS), rxFreqCol, 5, 1);
    }
    else
    {
        SPRINT_NUMBER(TXT, scanFreqStart, 4, 5, 1, 0);
        TXT[10]=' ';
        TXT[11]='t';
        TXT[12]='o';
        TXT[13]=0;
        //TXT[14]=0;
        fontDraw8x8(TXT, VFO_RXXPOS, vpos+DIS(VFO_RXYPOS), COL_VFORXFREQ, 0);
        SPRINT_NUMBER(TXT, scanFreqEnd, 4, 5, 1, 0);
        TXT[11]=' ';
        TXT[12]=' ';
        fontDraw8x8(TXT, VFO_RXXPOS, vpos+DIS(VFO_RXYPOS)+8, COL_VFORXFREQ, 0);
    }

    if(isActive && loopMode==LOOPMODE_SCANMONITOR && settings.scanResume)
    {
        SPRINT_NUMBER(TXT, scanningSkip, 10, 255, 1, 1);
        //fontDraw6x8(TXT, VFO_TXXPOS, displayVfoPos(settings.activeVfo)+DIS(VFO_TXYPOS), COL_VFOTXFREQ);        
        fontCustomSymbol(13, VFO_TXXPOS-8, vpos+DIS(VFO_TXYPOS), COL_VFORXFREQ);
        fontDraw6x8(TXT, VFO_TXXPOS, displayVfoPos(settings.activeVfo)+DIS(VFO_TXYPOS), COL_VFOTXFREQ);        
    }
    else
    if(isActive && loopMode==LOOPMODE_SCAN && !(VFOSTATE(vfoNumber).mode))
    {
        //fontCustomSymbol(3, VFO_TXXPOS-8, vpos+DIS(VFO_TXYPOS), COL_VFORXFREQ);
        SPRINT_NUMBER(TXT, upper, 4, 5, 1, 1);
        fontCustomSymbol(3, VFO_TXXPOS-8, vpos+DIS(VFO_TXYPOS), COL_VFORXFREQ);
        fontDraw6x8(TXT, VFO_TXXPOS, vpos+DIS(VFO_TXYPOS), COL_VFOTXFREQ);
    }
    else
    if(upper != lower)
    {
        VFO[vfoNumber].bits.busyLock = 0;
        symbol = lower > upper ? 4 : 5;
        SPRINT_NUMBER(TXT, lower, 4, 5, 1, 1);
        fontDraw6x8(TXT, VFO_TXXPOS, vpos+DIS(VFO_TXYPOS), COL_VFOTXFREQ);
        fontCustomSymbol(symbol, VFO_TXXPOS-8, vpos+DIS(VFO_TXYPOS), COL_VFOTXFREQ);
    }
    else if(!drawBG)
        lcdFill(VFO_TXXPOS-8, vpos+DIS(VFO_TXYPOS), 68, 8, COL_BGROUND);

    if(!VFOSTATE(vfoNumber).mode) // !settings.vfoState[vfoNumber].mode) //  !vfox->mode)
    {
        memCpy2(VFOn, TXT, 6);
        TXT[4] = vfoNumber?'B':'A';
    }
    else
    {
        memCpy2(CHn, TXT, 6);
        SPRINT_NUMBER(&TXT[2], vfox->number-1, 3, 255, 0, 0);      
    }
    fontDraw6x8(TXT,VFO_NAMEX,vpos+DIS(VFO_NAMEY),COL_VFOCORNER);

    channelGroupLabel(VFOSTATE(vfoNumber).group);
    fontDraw6x8(TXT,VFO_GROUPX,vpos+DIS(VFO_GROUPY),COL_VFOCORNER2);

    
        symbol=vfo->bits.busyLock ? 1 : 13;
        if(isActive)
        {
            if(loopMode & LOOPMODE_SCANMONITOR)
                symbol = 14;
            else
            if(loopMode & (LOOPMODE_SCAN | LOOPMODE_FREQCOUNTER))
                symbol = 8;
        }
        fontCustomSymbol(symbol, VFO_SCANSYMX, vpos+DIS(VFO_SCANSYMY), COL_VFOTXFREQ);
    

    TXT[1] = 0; // potential reenable
    TXT[0] = vfo->bits.reversed ? 'R' : ' ';
    fontDraw8x8(TXT, VFO_REVERSEX, vpos+DIS(VFO_REVERSEY), COL_VFOPOWER, 0);

    //TXT[0] = vfox->rxBandwidth ? 'N' : 'W';
    //fontDraw8x8(TXT, VFO_BWX, vpos+DIS(VFO_BWY), COL_VFOLABELS, 0);

    TXT[4]=0;
    TXT[0]=groupLetter(vfo->groups.single.g0);
    TXT[1]=groupLetter(vfo->groups.single.g1);
    TXT[2]=groupLetter(vfo->groups.single.g2);
    TXT[3]=groupLetter(vfo->groups.single.g3);

    if(!settings.vfoState[vfoNumber].group) dimColor=1;
    fontDraw6x8(TXT, VFO_GR_LETTERSX, vpos+DIS(VFO_GR_LETTERSY), COL_VFOLABELS);
    dimColor=!isActive;

    fontDraw8x8(!(vfo->txSubTone.value) ? &SPACE2 : vfo->txSubTone.bytes.hi&0x80 ? "DT" : "CT", VFO_TX_STX, vpos+DIS(VFO_TX_STY), COL_VFOLABELS, 0);

    if(vfo->rxSubTone.value==1050)
    {
        fontCustomSymbol(10, VFO_RX_STX, vpos+DIS(VFO_RX_STY), COL_VFOLABELS);
        fontCustomSymbol(11, VFO_RX_STX+8, vpos+DIS(VFO_RX_STY), COL_VFOLABELS);
    }
    else
        fontDraw8x8(!(vfo->rxSubTone.value) ? &SPACE2 : vfo->rxSubTone.bytes.hi&0x80 ? "DR" : "CR", VFO_RX_STX, vpos+DIS(VFO_RX_STY), COL_VFOLABELS, 0);

    fontDraw8x8(displayModName(vfox), VFO_MODX, vpos+DIS(VFO_MODY), COL_VFOLABELS, 0);

    if(!vfox->isFmTuner)
    {
        TXT[0] = vfox->rxBandwidth ? 'N' : 'W';
        TXT[1]=0;
        fontDraw8x8(TXT, VFO_BWX, vpos+DIS(VFO_BWY), COL_VFOLABELS, 0);
    }


    //if(vfoNumber == settings.activeVfo)
    //{
        COL_BGROUND.value = COL_FWBGROUND.value;        
    //}
    dimColor = 0; // may need undo

}


void displayBlankSBarDPTT(void)
{
    lcdFill(0,SMETER_DPTT_YPOS,128,8,COL_FWBGROUND);
    lcdFill(0,SBAR_DPTT_YPOS,128,8,COL_FWBGROUND);
}

void displayToneMonitor(void)
{
    if(dtmfDisplayTime) { return; } 
    if(!inputMode)
    {
        if(heardTone & 0x8000)
        {
            sprint_dcs(heardTone);
        }
        else
        if(heardTone)
        {
            SPRINT_NUMBER(TXT, heardTone, 3, 1, 1, 1);
        }
        else
            memCpy2(&SPACE5, TXT, 6);
        fontDraw6x8(TXT, FLAGS_TONEMONITORX, flagsYPOS(), COL_VFOLABELS);
    }
    if(settings.toneMonitor==2 && heardTone && ACTIVE_VFO.txSubTone.value!=heardTone)
    {
        ACTIVE_VFO.txSubTone.value = heardTone;
        if(!inputMode)
        {
            displayVfo(settings.activeVfo, 0);
        }
    }
}

void leftJustify(char** mhz, char** khz, u8* khzdisplace)
{
    u8 offset, i, j;
    offset = 0;
    TXT[4]=0;
    for(; 1; offset++)
    {
        if(!VFO_LJ_FREQ || TXT[offset]!=32)
        {
            *mhz = &TXT[offset];
            *khz = &TXT[5];
            *khzdisplace = 64-(offset<<4);
            j = 10;
            for(i=0; i<offset; i++)
            {
                TXT[j++]=32;
                TXT[j++]=32;
            }
            TXT[j]=0;
            return;
        }
    }
}

void displayFreq(const u32* freq, const u8 x, const u8 y, const COLOR col, u8 decimals, const bit dp) // freq is in 10Hz units
{
    COLOR col2;
    char* mhz;
    char* khz;
    u8 khzdisplace, i;
    SPRINT_NUMBER(TXT, *freq, 4, 5, 1, 1);
    leftJustify(&mhz, &khz, &khzdisplace);
    khzdisplace+=x;


    fontChipDrawText(mhz, &FONT8x8, x, y, col, DOUBLE_SIZE); // size = 64,16

    for(i=decimals+5; i<10; i++)
        TXT[i]=32;

    fontChipDrawText(khz, &FONT8x16, khzdisplace, y, col, NORMAL_SIZE); // size = 40, 16
    if(dp)
    {
        col2.value = lowerColor(col).value;
        lcdFill(khzdisplace-2,y+13,2,2, col2);    
    }

}


