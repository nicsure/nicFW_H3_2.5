#define INPUT_IDLE 0
#define INPUT_APPLIED 1
#define INPUT_CANCELLED 2


void inputPrepare(const u8 units, const u8 decimals, const u8 x, const u8 y, const u8 font);
void inputTick(void);
void inputParseKey(const u8 key);
void inputLongPress(const u8 key);
void inputStringParseKey(const u8 key);
void inputPrepareString(const u8 charCount, const u8 x, const u8 y, const u8 font, const char* source);
void inputDtmfParseKey(const u8 key);
void inputPrepareDTMF(const u8 digitCount, const u8 x, const u8 y, const u8 font, const dtmfSequence* sequence);