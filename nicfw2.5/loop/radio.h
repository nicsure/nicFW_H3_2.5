void radioLoopTick(void);
void validateVfo(const u8 vfoPosition);
void radioClearFilters(void);
void radioSetFilters(const bit rx, const bit vhf);
void radioSwapVfo(void);
void radioToggleVfoModeAndGroup(u8 newMode, u8 group, const u8 chstep, const u8 grpDir);
void radioToggleVfoMode(u8 newMode, u8 group, const u8 chstep);
const s16 step833(const u8 dir);
void radioSetScanStartFreqToVfo(void);
void radioSetLED(const u8 led, const u8 state);


