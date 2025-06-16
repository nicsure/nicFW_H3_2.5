

void soundBeep(const u8 duration, const u16 waveLength)
{
    //u16 i, dsEnd;
    u16 i;
    if(xmitActive) return;
    //dsEnd = (u16)ticksPassed + (u16)duration;
    ticksPassed=0;
    bkSetModulation(0, 0);
    POW_2822 = 1;
    EA=1;
    //while(ticksPassed < dsEnd)
    while(ticksPassed < duration)
    {
        BEEP ^= 1;
        for(i = 0; i != waveLength; i++)
        {
            feedTheDog();
        }
    }
    BEEP = 0;
    bkSetModulation(currentModulation, 1);
}

void soundBlip(const u8 duration, const u16 waveLength, const u8 twice)
{
    if(settings.keyTones)
    {
        soundBeep(duration, waveLength);
        if(twice)
        {
            delay(100);
            soundBeep(duration, waveLength);
        }
    }
}