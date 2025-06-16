const u8 calibPwmToPower(const u8 dutyCycle, const bit isVhf)
{
    u16 addr;
    if(calibIsValid())
    {
        addr = 0x1e00 + dutyCycle;
        if(!isVhf)
            addr+=0x100;
        eepromRead(addr, (u8*)&calibPwr, 1);
        return calibPwr;
    }
    else   
    {
        return dutyCycle/3;
    }
}

const u8 calibIsValid(void)
{
    u8 vhfMagic, uhfMagic;
    eepromRead(0x1e00, (u8*)&vhfMagic, 1);
    eepromRead(0x1f00, (u8*)&uhfMagic, 1);
    return uhfMagic==0xd1 && vhfMagic==0x57;
}

void calibLoad(void)
{
    eepromRead(0x1de0, (u8*)&tuning, 32);
    if(!calibIsValid())
    {
        tuning.uhfPeakSetting = 150;
        tuning.vhfPeakSetting = 150;
        tuning.xtal671 = 0;
    }
}

void calibSave(void)
{
    eepromWrite(0x1de0, (u8*)&tuning, 32);
}