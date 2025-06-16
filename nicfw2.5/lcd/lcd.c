
u8 code initSeq[] = {
    LCD_SETRST, LCD_DELAY, 100, LCD_CLRRST, LCD_DELAY, 100, LCD_SETRST, LCD_DELAY, 150,
    LCD_CLRCD, 0x11, LCD_DELAY, 120,
    LCD_CLRCD, 0xb1, 0x02, 0x35, 0x36,
    LCD_CLRCD, 0xb2, 0x02, 0x35, 0x36,
    LCD_CLRCD, 0xb3, 0x02, 0x35, 0x36, 0x02, 0x35, 0x36,
    LCD_CLRCD, 0xb4, 0x03,
    LCD_CLRCD, 0xc0, 0xa2, 0x02, 0x84,
    LCD_CLRCD, 0xc1, 0xc5,
    LCD_CLRCD, 0xc2, 0x0d, 0x00,
    LCD_CLRCD, 0xc3, 0x8d, 0xea,
    LCD_CLRCD, 0xc4, 0x8d, 0xee,
    LCD_CLRCD, 0xc5, 0x1a,
    LCD_CLRCD, 0x36, 0x80,
    LCD_CLRCD, 0xe0, 0x03, 0x1b, 0x09, 0x0e, 0x32, 0x2d, 0x28, 0x2c, 0x2b, 0x29, 0x30, 0x3b, 0x00, 0x01, 0x02, 0x10,
    LCD_CLRCD, 0xe1, 0x03, 0x1b, 0x09, 0x0e, 0x32, 0x2e, 0x28, 0x2c, 0x2b, 0x28, 0x31, 0x3c, 0x00, 0x01, 0x02, 0x10,
    LCD_CLRCD, 0x3a, 0x05,
    LCD_CLRCD, 0x29, LCD_DELAY, 50,
    LCD_ENDSEQ,
};

void lcdBacklight(const bit on)
{
    pwmSetBl( on ? (settings.lcdBrightness)+34 : settings.dimmer?(settings.dimmer)+34:0 );
    KEY_LED = on;
    if(on) lcdTimer = settings.lcdTimeout;
    lcdSleep(settings.dimmer?0:!on);
}

void lcdByte(const u8 byt)
{
    LCD_ACK = 0;
    //if(rfiAdjust) delayRfi();
    LCD_CMD = byt;
    do
    {
        ACC = LCD_ACK;
    }
    while(!ACC_7);
    LCD_CD = 1;   
    //if(rfiAdjust) delayRfi();
}

void lcd2Byte(const u8 b1, const u8 b2)
{
    lcdByte(b1);    
    lcdByte(b2);    
}

void lcdCmd(const u8 cmd)
{
    LCD_CD = 0;
    lcdByte(cmd);
}

void lcdInit(void)
{
    u8 i = 0;
    while(1)
    {
        u8 cmd = initSeq[i++];
        switch(cmd)
        {
            case LCD_ENDSEQ:
                KEY_LED = 1;        
                return;
            case LCD_DELAY:
                delay(initSeq[i++]);
                break;
            case LCD_SETRST:
                LCD_RST = 1;
                break;
            case LCD_CLRRST:
                LCD_RST = 0;
                break;
            case LCD_CLRCD:
                LCD_CD = 0;
                break;
            default:
                lcdByte(cmd);        
                break;
        }
    }
}

void lcdRegion(u8 x1, const u8 y1, u8 x2, const u8 y2)
{    
    x1+=0x20;
    x2+=0x20;
    lcdCmd(0x2a);
    lcd2Byte(0, y1);
    lcd2Byte(0, y2);
    lcdCmd(0x2b);
    lcd2Byte(0, x1);
    lcd2Byte(0, x2);
    lcdCmd(0x2c);
}

void lcdFill(const u8 x, const u8 y, const u8 w, const u8 h, const COLOR col)
{
    u16 cnt;
    //const COLOR* col2 = dimColor ? &lcdDimColor(col) : &col;
    remoteFill(x, y, w, h, col);
    lcdRegion(x, y, x+w-1, y+h-1);
    cnt = (u16)h*(u16)w;
    while(cnt != 0 && !(cnt&0x8000))
    {
        lcd2Byte(col.bytes.c2, col.bytes.c1);
        cnt--;
    }
}

void lcdCls(void)
{
    lcdFill(0,0,128,128,COL_BGROUND);
}

void lcdSleep(const bit asleep)
{
    lcdCmd(asleep?0x10:0x11);
    lcdCmd(asleep?0x28:0x29);
}

void lcdGamma(void)
{
    lcdCmd(0x26);
    lcdByte(1<<settings.gamma);
}

void lcdInvert(const u8 inverted)
{
    lcdCmd(inverted?0x21:0x20);
}
