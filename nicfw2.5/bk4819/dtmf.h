u16 code dtmfTableA[] = {
    941,
    697,
    697,
    697,
    770,
    770,
    770,
    852,
    852,
    852,
    697,
    770,
    852,
    941,
    941,
    941
};

u16 code dtmfTableB[] = {
    1336,
    1209,
    1336,
    1477,
    1209,
    1336,
    1477,
    1209,
    1336,
    1477,
    1633,
    1633,
    1633,
    1633,
    1209,
    1477
};        

void dtmfPlay(const u8 digit);
void dtmfSeqToString(const dtmfSequence* sequence, const char fill, char* target);
void dtmfSeqFromString(void);
const u8 dtmfExtractDigit(const dtmfSequence* sequence, const u8 position);
const u16 dtmfGetSpeed(void);
void dtmfGetPresetName(const u8 seqNum);
void dtmfGetPresetSeq(const u8 seqNum);
const u8 dtmfSeek(u8 dir);
void dtmfPlaySeq(const dtmfSequence* sequence, const u8 id);
void dtmfPlayPTTID(void);
u8 dtmfDetect(void);
void dtmfAddDetectedDigit(const u8 digit);
void dtmfSearchPresets(void);



