void scopeDraw(void)
{
    u8 x, bw, hiSig, vpos, sig, t;
    u32 freq;
    u16 sig16;
    COLOR sbCol;
    squelchOpen = 0;
    if(skipNextScope)
    {
        skipNextScope--;
        return;
    }
    if(inputMode)
        return;
    vpos = displayVfoPos(settings.activeVfo^1);
    freq = ACTIVE_VFO.rxFreq.value;
    freq -= (u32)settings.step << 5;
    SPRINT_NUMBER(TXT, freq, 4, 5, 1, 1);
    fontDraw6x8(TXT, 0, SBAR_DPTT_YPOS, COL_VFORXFREQ);
    hiSig=0;
    bw = SCOPE_SOLID?2:1;
    for(x = 0; x!=128; x+=2)
    {
        bkSet30(0);
        bkSetFreqRegs(freq);
        bkAfDacOff();
        delay(16);
        keypadTick(1);
        if(anyKeyInUse)
        {
            skipNextScope = 25;
            break;
        }
        feedTheDog();

        sig16 = bkGetRssi();
        if(sig16<noiseFloor) 
            sig16=noiseFloor-sig16;
        else
            sig16-=noiseFloor;
        sig = sig16>>1;
        if(sig>VFO_HEIGHT) sig=VFO_HEIGHT;
        if(!sig) sig=1;
        if(sig>hiSig)
        {
            hiSig=sig;
            topFreq=freq;
        }
        freq+=settings.step;
        t = VFO_HEIGHT-sig;
        sbCol.value = x==64 ? COL_SCOPEBARMID.value : COL_SCOPEBAR.value;
        lcdFill(x, vpos, bw, t, COL_FWBGROUND);
        lcdFill(x, vpos+t, bw, sig, sbCol);
    }
    ticksPassed=0;
    if(!anyKeyInUse && !skipNextScope)
    {
        hiFreq=topFreq;
        SPRINT_NUMBER(TXT, freq, 4, 5, 1, 1);
        fontDraw6x8(TXT, 68, SBAR_DPTT_YPOS, COL_VFORXFREQ);    
        SPRINT_NUMBER(TXT, hiFreq, 4, 5, 1, 1);
        fontDraw8x8(TXT, 24, SMETER_DPTT_YPOS, COL_VFOTXFREQ, 0);          
    }
}

void scopeStop(void)
{
    scopeActive=0;
    bkApplyVfo(settings.activeVfo);
    displayRefresh(1);
}