void eepromInit(const u16 eaddr)
{
    i2cTarget=I2CEEPROM;
    i2cDelay();
    i2cStart();
    i2cSend(0xa0);
    i2cSend((eaddr>>8) & 0xff);
    i2cSend(eaddr & 0xff);
}

void eepromRead(const u16 eaddr, u8* destination, const u8 size)
{
    eepromInit(eaddr);
    i2cStart();
    i2cSend(0xa1);
    i2cRead(destination, size);
    i2cStop();
}

void eepromBurn(const u16 eaddr, const u8* source)
{
    eepromInit(eaddr);
    i2cWrite(source, 32);
    i2cStop();
    delay(10);    
}

void eepromWrite(u16 eaddr, u8* source, u8 size)
{
    if((size&31) || (eaddr&31))
    {
        return;
    }
    while(size)
    {
        eepromRead(eaddr, eepromReadBuffer, 32);
        if(!memCmp2(source, eepromReadBuffer, 32))
        {
            eepromBurn(eaddr, source);
        }
        eaddr+=32;
        source+=32; // adding to a pointer? naughty ;)
        size-=32;
    }
}
