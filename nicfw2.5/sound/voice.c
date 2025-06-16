void voiceInit(void)
{
    i2cTarget=I2CVOICE;
    i2cIO(GPIO_OUTPUT);
    i2cSCK(1);
    delay(20);
    i2cSCK(0); 
}

void voiceSend(u8 byt)
{
    u8 i;
    for(i = 0; i < 8; i++)
    {
        i2cSDA(!(byt&0x80));
        delay(1);
        i2cSCK(1);
        delay(1);
        i2cSCK(0);
        byt<<=1;
        delay(1);
    }
}

void voicePlay(const u8 id, const u8 pause)
{
    u8 ms10;
    bit unmuted;
    if(xmitActive || fmtActive || settings.keyTones!=3) return;

    unmuted = (bkReg[0x30].bytes.hi != 0xBD);
    
    if(unmuted) bkSetModulation(0, 0);
    delay(5);
    POW_2822=1;

    voiceInit();
    voiceSend(159-id);

    if(pause || unmuted)
    {
        ms10 = pause==1 ? voiceTableDelay10ms[id] : pause;
        ms10 += (ms10>>2);
        EA=0;
        while(ms10--)
        {
            delay(9);
            feedTheDog();
        }
        EA=1;
    }

    bkSetModulation(currentModulation, 1);
}