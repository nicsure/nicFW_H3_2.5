#define LCD_ENDSEQ 0xff
#define LCD_DELAY  0xfe
#define LCD_SETRST 0xfd
#define LCD_CLRRST 0xfc
#define LCD_CLRCD  0xfb

void lcdInit(void);
void lcdFill(const u8, const u8, const u8, const u8, const COLOR);
void lcdCls(void);
void lcdRegion(u8, const u8, u8, const u8);
void lcd2Byte(const u8, const u8);
void lcdBacklight(const bit on);
void lcdSleep(const bit asleep);
void lcdGamma(void);
void lcdInvert(const u8 inverted);