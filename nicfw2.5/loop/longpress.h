
#define LP_SCAN 0
#define LP_TXENTER 1
#define LP_DUALWATCH 2
#define LP_FREQCOUNT 3
#define LP_KEYLOCK 4
#define LP_BLUETOOTH 5
#define LP_FMTUNER 6
#define LP_EDITFREQ_ENTERGRP 7
#define LP_EDITCHNAME 8
#define LP_REVERSE 9
#define LP_FIXREVERSE 10
#define LP_DTMFINPUT 11
#define LP_DTMFPRESETS 12
#define LP_RFICOMP 13
#define LP_SCANPRESET_LCDINVERT 14
#define LP_SCOPE 15
#define LP_SHIFT 16
#define LP_DUALPTT 17
#define LP_SINGLEPTT 18
#define LP_HYBRIDPTT 19
#define LP_VFOLOCK 20

#define LP_KEYREPEAT 0xff


const u32 code defaultFreq = 14400000l;
const u32 code deadFreq = 70000000l;

const u8 code lpActionTable[] = { 
    LP_EDITFREQ_ENTERGRP, // 0
    LP_EDITCHNAME,  // 1
    LP_DTMFINPUT,   // 2
    LP_SCAN,        // 3
    LP_SCANPRESET_LCDINVERT,  // 4
    LP_REVERSE,     // 5
    LP_RFICOMP,     // 6
    LP_FREQCOUNT,   // 7
    LP_FMTUNER,     // 8
    LP_DUALWATCH,   // 9
    LP_SHIFT,       // menu
    LP_KEYREPEAT,   // up
    LP_KEYREPEAT,   // down
    LP_TXENTER,     // exit
    LP_KEYLOCK,     // star
    LP_DTMFPRESETS, // hash
};

const u8 code lpShiftActionTable[] = { 
    LP_VFOLOCK,     // 0
    LP_BLUETOOTH,   // 1
    LP_SCOPE,       // 2
    LP_SCAN,        // 3
    LP_SCANPRESET_LCDINVERT,  // 4
    LP_FIXREVERSE,  // 5
    LP_RFICOMP,     // 6
    LP_DUALPTT,     // 7
    LP_SINGLEPTT,   // 8
    LP_HYBRIDPTT,   // 9
    LP_SHIFT,       // menu
    LP_KEYREPEAT,   // up
    LP_KEYREPEAT,   // down
    LP_TXENTER,     // exit
    LP_KEYLOCK,     // star
    LP_DTMFPRESETS, // hash
};



void longpressAction(u8 key);
void toggleKeylock(void);