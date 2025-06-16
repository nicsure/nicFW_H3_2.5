


void i2cDelay(void)  
{
    //__data u8 j = 0x2d;
    u8 j = 0x2d;
    while(--j != 0) { }
}

void i2cSDA(const bit level)
{
    switch(i2cTarget)
    {
        case I2CEEPROM:
            EEPROM_SDA = level;
            break;
        case I2CVOICE:
        case I2CFMRADIO:
            SDA5807 = level;
            break;
    }
    i2cDelay();
}

const bit i2cReadSDA(void)
{    
    switch(i2cTarget)
    {
        case I2CEEPROM:
            return EEPROM_SDA;
        case I2CVOICE:
        case I2CFMRADIO:
            return SDA5807;
    }
    return 0;
}

void i2cSCK(const bit level)
{
    switch(i2cTarget)
    {
        case I2CEEPROM:
            EEPROM_SCK = level;
            break;
        case I2CFMRADIO:
            SCK5807 = level;
            break;
        case I2CVOICE:
            VOICE_SCK = level;
            break;
    }
    i2cDelay();
}

void i2cIO(const bit isOutput)
{
    switch(i2cTarget)
    {
        case I2CEEPROM:
            P5CON = isOutput ? 0xFD : 0xFC;
            break;
        case I2CVOICE:
        case I2CFMRADIO:
            P3CON = isOutput ? 0xef : 0xaf;
            break;
    }
    i2cDelay();
}

void i2cStart(void)
{
    EA=0;
    i2cSDA(GPIO_HIGH);
    i2cSCK(GPIO_HIGH);
    i2cSDA(GPIO_LOW);
    i2cSCK(GPIO_LOW);
}

void i2cStop(void)
{
    i2cSCK(GPIO_LOW);
    i2cSDA(GPIO_LOW);
    i2cSCK(GPIO_HIGH);
    i2cSDA(GPIO_HIGH);
    EA=1;
}

const u8 i2cGet(const u8 last)
{
    u8 r = 0;
		u8 i;
    i2cIO(GPIO_INPUT);
    for(i=0; i<8; i++)
    {
        i2cSCK(GPIO_LOW);
        i2cSCK(GPIO_HIGH);
        r<<=1;
        if(i2cReadSDA())
        {
            r|=1;
        }
    }
    i2cSCK(GPIO_LOW);
    i2cIO(GPIO_OUTPUT);
    i2cSDA(last);
    i2cSCK(GPIO_HIGH);
    i2cSCK(GPIO_LOW);
    return r;
}

const bit i2cSend(u8 byt)
{
    bit r=1; // return success/failure flag, also doubles as an attempt counter
		u8 ii;
    i2cSCK(GPIO_LOW);
    for(ii=0; ii<8; ii++)
    {
        i2cSDA(byt & 0x80);
        byt <<= 1;
        i2cSCK(GPIO_HIGH);
        i2cSCK(GPIO_LOW);
    }
    i2cIO(GPIO_INPUT);
    i2cSDA(GPIO_HIGH); // original also sets this which to me seems pointless as the port is in input mode, but it may be simply timing i don't know
    i2cSCK(GPIO_HIGH);
    while(i2cReadSDA())
    {
			  r^=1;
        if(r)
            break;
    }    
    i2cSCK(GPIO_LOW);
    i2cIO(GPIO_OUTPUT);
    i2cSDA(GPIO_HIGH);
    return r; // here r will be 0 if this failed, or non-zero if it succeeded
}

void i2cRead(u8* destination, u8 length)
{
    u8 cnt = 0;
    while(length--)
    {
        i2cDelay();
        //XRAM[xaddr++] = i2cGet(length==0);
        destination[cnt++] = i2cGet(length==0);
    }
}

void i2cWrite(const u8* source, u8 length)
{
    u8 cnt = 0;
    while(length--)
    {
        //i2cSend(XRAM[xaddr++]);
        i2cSend(source[cnt++]);
    }
}



