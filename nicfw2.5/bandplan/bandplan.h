const u8 planMatch(const u32*);
const u8 planModulation(const planInfo*, const u8);
const u8 planBandwidth(const planInfo*, const u8);
const u8 planPower(const planInfo*, const u8);
void planApply(const u8 vfoPosition);
const u8 planIsValid(void);
void planFindFMT(void);
void planWrapVfo(const u8 vfoPosition);