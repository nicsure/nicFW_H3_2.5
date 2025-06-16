void displayLogo(void)
{
    u16 addr;
    u8 m, c;
    addr = 0;
    lcdCls();
    pwmSetBl(64);
    lcdRegion(0,32,127,95);
    while(C16(addr)->bytes.hi != 4)
    {
        for(m=1; m!=0; m<<=1)
        {
            c = (logo[addr]&m)?0xff:0;
            lcd2Byte(c, c);
        }
        addr++;
    }
}