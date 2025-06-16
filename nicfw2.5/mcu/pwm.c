void pwmInit(void)
{
    exP41Mode = 5;
    exPwmInit = 0;
    exPwmCon1 |= 3;
    exPwmFlow = 5;
    exPwmCon4 |= 3;
    exPwmMask &= 0xfc;
    exPwm2Clr = 0;
    exPwmCon3 |= 3;
    exPwm2Dc = 0xc800;
    exPwm2Per = 0;
    exPwmCon2 |= 3;

    exP22Mode = 5;
    exPwm1Clr = 0;
    exPwm1Dc = 0xc800;
    exPwm1Per = 0;
}

void pwmSetBl(const u8 dc)
{
    lcdSleep(!dc);
    exPwmCon2 &= 0xfe;
    exPwm1Per = dc<<8;
    exPwmCon2 |= 1;
}

void pwmSetPa(const u8 pwr)
{    
    exPwmCon2 &= 0xfd;
    exPwm2Per = pwr<<8;
    exPwmCon2 |= 2;
}