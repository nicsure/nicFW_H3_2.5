
void i2cDelay(void);
void i2cSDA(const bit);
const bit i2cReadSDA(void);
void i2cSCK(const bit);
void i2cIO(const bit);
void i2cStart(void);
void i2cStop(void);
const u8 i2cGet(const u8);
const bit i2cSend(u8);
void i2cRead(u8* destination, u8);
void i2cWrite(u8* source, u8 length);




