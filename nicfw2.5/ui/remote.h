void remoteSendColor(const COLOR col);
void remoteText(const char* text, const chipFont* font, const u8 x, const u8 y, const COLOR col, const bit overSize);
void remoteFill(const u8 x, const u8 y, const u8 w, const u8 h, const COLOR col);
void remoteSymbol(const u8 sym, const u8 x, const u8 y, const COLOR col);
void remoteSendLedStatus(void);
