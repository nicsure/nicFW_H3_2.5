const char code NT[] = "N/T ";
const char code VFOn[] = "VFO-%";
const char code GRPn[] = "GRP-%";
const char code CHn[] = "CH%%%";
const char code SCANNING[] = "Scanning   ";
const char code ACTIVITY[] = "Activity   ";
const char code MONITORING[] = "Monitoring ";
const char code FREQCOUNT[] = "Freq Count ";


void displayDrawMeter(const u8 sig, const u8 mode);
void displayDrawExNoise(const u8 value, const bit txMod);
void displayFreq(const u32* freq, const u8 x, const u8 y, const COLOR col, u8 decimals, const bit dp);
void displayVfo(const u8 vfoNumber, const bit drawBG);
const u8 displayVfoPos(const u8 vfoNumber);
void displayRefresh(const bit drawBG);
void displayVfoRefresh(const u8 vfoNumber, const bit drawBG);
void displayRefreshGeneral(void);
void displayToneMonitor(void);
const u8 flagsYPOS(void);
const u8 DIS(const u8 val);
const u8 displayGetSMETER_YPOS(void);
const u8 displayGetSBAR_YPOS(void);
void displayVfoRefreshActiveDrawBG(void);
void displayVfoRefreshActiveNoDrawBG(void);
void displayRefreshFull(void);
const char* getModName(const u8 modulation);
void displayBlankSBarDPTT(void);
void remoteSendSBarYPos(void);
const u16 colVfo(void);


