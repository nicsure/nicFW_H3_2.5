typedef unsigned char        u8;
typedef unsigned short int   u16;
typedef unsigned long int    u32;

typedef signed char          s8;
typedef signed short int     s16;
typedef signed long int      s32;

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1
#define GPIO_HIGH 1
#define GPIO_LOW 0

#define I2CEEPROM 0
#define I2CFMRADIO 1
#define I2CVOICE 2

#define RXALED 1
#define TXALED 2
#define RXBLED 4
#define TXBLED 8

#define KEY_PTTA 0x10
#define KEY_PTTB 0x11
#define KEY_FLSH 0x12
#define KEY_PTTE 0x13
#define KEY_0 0x00
#define KEY_1 0x01
#define KEY_2 0x02
#define KEY_3 0x03
#define KEY_4 0x04
#define KEY_5 0x05
#define KEY_6 0x06
#define KEY_7 0x07
#define KEY_8 0x08
#define KEY_9 0x09
#define KEY_MENU 0x0A
#define KEY_UP 0x0B
#define KEY_DOWN 0x0C
#define KEY_EXIT 0x0D
#define KEY_STAR 0x0E
#define KEY_HASH 0x0F
#define KEY_NONE 0xFF
#define KEY_LONGACTIONED 0xFE
#define KEYL_0 0x20
#define KEYL_1 0x21
#define KEYL_2 0x22
#define KEYL_3 0x23
#define KEYL_4 0x24
#define KEYL_5 0x25
#define KEYL_6 0x26
#define KEYL_7 0x27
#define KEYL_8 0x28
#define KEYL_9 0x29
#define KEYL_MENU 0x2A
#define KEYL_UP 0x2B
#define KEYL_DOWN 0x2C
#define KEYL_EXIT 0x2D
#define KEYL_STAR 0x2E
#define KEYL_HASH 0x2F

#define DOUBLE_SIZE 1
#define NORMAL_SIZE 0

#define FONT6X8NUM 0
#define FONT8X8NUM 1
#define FONT8X16NUM 2

#define LOOPMODE_RADIO 0
#define LOOPMODE_FMTUNER 1
#define LOOPMODE_SCOPE 2
#define LOOPMODE_SCAN 4
#define LOOPMODE_SCANMONITOR 8
#define LOOPMODE_FREQCOUNTER 16
#define LOOPMODE_SCANFMT 32

#define INPUTMODE_NONE 0
#define INPUTMODE_MENU 1
#define INPUTMODE_INPUT 2
#define INPUTMODE_SERIAL 4

#define EEPROM_SETTINGS_ADDR 0x1900

//#define HI_NOISE_LEVEL 0x37

#define SPRINT_NUMBER(b, v, u, d, p, z) sp_Value=(v); sp_Decimals=(d); sp_Units=(u); sprint_number((b), (p), (z)); 

typedef struct
{
    u8 latch : 1;
    u8 tank : 7;
} KEY;

typedef union
{
    u8 value;
    struct {
        u8 hi : 4;
        u8 lo : 4;
    } nibbles;
} U8;

typedef union
{
    u16 value;
    struct
    {
        u8 hi;
        u8 lo;
    } bytes;
    struct
    {
        u16 n3 : 4;
        u16 n2 : 4;
        u16 n1 : 4;
        u16 n0 : 4;
    } nibbles;
    u8 array[2];
} U16;

typedef union
{
    u32 value;
    struct
    {
        u8 byte3;
        u8 byte2;
        u8 byte1;
        u8 byte0;
    } bytes;
    struct
    {
        u16 hi;
        u16 lo;
    } words;
    struct
    {
        U16 hi;
        U16 lo;
    } wordsU;
    struct
    {			
        u16 tone : 14;
        u16 isInverted : 1;
        u16 isDCS : 1;
        u16 unused : 16;
    } subTone;
} U32;

typedef union
{
    u16 value;
    struct
    {
        u16 r : 5;
        u16 gl : 3;
        u16 gh : 3;
        u16 b : 5;
    } RGB;
    struct
    {
        u8 c2;
        u8 c1;
    } bytes;
} COLOR;


typedef struct 
{
    U32 rxFreq;
    U32 txFreq;
    U16 rxSubTone;
    U16 txSubTone;
    u8 txPower;
    union
    {
        u16 value;
        struct
        {
            u16 g0 : 4;
            u16 g1 : 4;
            u16 g2 : 4;
            u16 g3 : 4;
        } single;
    } groups;
    struct
    {
        u8 bandwidth : 1;
        u8 modulation : 2;
        u8 position : 1;
        u8 pttID : 2;
        u8 reversed : 1;
        u8 busyLock : 1;
    } bits;
    char reserved[4];
    char name[12];
} channelInfo;

typedef struct 
{
    u8 number;
    u8 rxplan;
    u8 txplan;
    u8 modulation;
    u8 txPower;
    u8 rxBandwidth;
    u8 txBandwidth;
    u8 rxIsVhf;
    u8 txIsVhf;
    u8 isFmTuner;
} channelXtra;


typedef struct 
{
    u32 startFreq;
    u32 endFreq;
    u8 maxPower;
    struct
    {
        u8 txAllowed : 1;
        u8 wrap : 1;
        u8 modulation : 3;
        u8 bandwidth : 3;
    } bits;
} planInfo;

typedef struct 
{
    U32 startFreq;
    u16 range;
    u16 step;
    u8 resume;
    u8 persist;
    struct {
        u8 modulation : 2;
        u8 ultrascan : 6;
    } bits;
    char label[9];
} scanPresetInfo;

typedef struct
{
    u32 base;
    u8 byteSize;
    u8 width;
    u8 number;
} chipFont;

typedef struct {
    struct {
        u16 d0 : 4;
        u16 d1 : 4;     // byte 1
        u16 length : 4; // byte 0
        u16 d2 : 4;
		} first;
		struct {
        u16 d3 : 4;     // byte 2
        u16 d4 : 4;
        u16 d5 : 4;     // byte 3
        u16 d6 : 4;
    } second;
    struct {
        u8 d7 : 4;      // byte 4
        u8 d8 : 4;
    } third;
} dtmfSequence;

typedef struct {
    dtmfSequence sequence;
    char label[7];
} dtmfPreset;


typedef struct {
    u16 magic;                  // 0x00
    u8 squelch;                 // 0x02
    u8 dualWatch;               // 0x03
    u8 autoFloor;               // 0x04
    u8 activeVfo;               // 0x05
    u16 step;                   // 0x06
    u16 rxSplit;                // 0x08
    u16 txSplit;                // 0x0a
    u8 pttMode;                 // 0x0c
    u8 txModMeter;              // 0x0d
    u8 micGain;                 // 0x0e
    u8 txDeviation;             // 0x0f
    s8 UNUSED_xtal671;          // 0x10
    u8 battStyle;               // 0x11
    u16 scanRange;              // 0x12      
    U16 scanPersist;            // 0x14
    u8 scanResume;              // 0x16
    u8 ultraScan;               // 0x17
    u8 toneMonitor;             // 0x18
    u8 lcdBrightness;           // 0x19
    u8 lcdTimeout;              // 0x1a
    u8 breathe;                 // 0x1b
    u8 dtmfDev;                 // 0x1c
    u8 gamma;                   // 0x1d
    u16 repeaterTone;           // 0x1e
    struct {                    // 0x20
        u8 group;
        u8 lastGroup;
        u8 groupModeChannels[16];
        u8 mode;
    } vfoState[2];
    u8 keyLock;                 // 0x46
    u8 bluetooth;               // 0x47
    u8 powerSave;               // 0x48
    u8 keyTones;                // 0x49
    u8 ste;                     // 0x4a
    u8 rfGain;                  // 0x4b
    u8 sBarStyle;               // 0x4c
    u8 sqNoiseLev;              // 0x4d
    u32 lastFmtFreq;            // 0x4e
    u8 vox;                     // 0x52
    u16 voxTail;                // 0x53
    u8 txTimeout;               // 0x55
    u8 dimmer;                  // 0x56
    u8 dtmfSpeed;               // 0x57
    u8 noiseGate;               // 0x58
    u8 scanUpdate;              // 0x59
    u8 asl;                     // 0x5a
    u8 disableFmt;              // 0x5b
    u16 pin;                    // 0x5c
    u8 pinAction;               // 0x5e
    u8 lcdInverted;             // 0x5f
    u8 afFilters;               // 0x60
    u8 ifFreq;                  // 0x61
    u8 sBarAlwaysOn;            // 0x62
    u8 setVfo;                  // 0x63
    u8 vfoLock;                 // 0x64
    u8 dwDelay;                 // 0x65
    u8 stDev;                   // 0x66
    u8 txCurrent;               // 0x67

    u8 gain0;                   // 0x68
    u8 gain1;                   // 0x69
    u8 gain2;                   // 0x6a
    u8 gain3;                   // 0x6b

    u8 rfiCompAmount;           // 0x6c

    u8 scrambleFreq;            // 0x6d

    u8 dtmfDecode;              // 0x6e

    u16 dtmfDelay;              // 0x6f
    u16 dtmfEndPause;           // 0x71

    u8 noiseCeiling;            // 0x73
    u8 amAgc;                   // 0x74

    u8 filler[11];
} settingsBlock;

typedef struct {
    u8 filler[27];
    s8 xtal671;
    u8 uhfPeakWatts;
    u8 uhfPeakSetting;
    u8 vhfPeakWatts;
    u8 vhfPeakSetting;
} tuningBlock;

typedef struct {
    dtmfPreset dtmfPresets[20];
    struct {
        char label[6];
    } groupLabels[16];
} settings2;


typedef struct {
    u8 filler[28];    
    u8 maxPowerVhf;
    u8 maxSettingVhf;
    u8 maxPowerUhf;
    u8 maxSettingUhf;
    u8 powerTableVhf[256];
    u8 powerTableUhf[256];
} settings3;


#define FONT6x8 CHIPFONT[0]
#define FONT8x8 CHIPFONT[1]
#define FONT8x16 CHIPFONT[2]

#define VFOSTATE(x) (settings.vfoState[x])
#define ACTIVE_VFOSTATE (settings.vfoState[settings.activeVfo])
#define ACTIVE_VFO (VFO[settings.activeVfo])
#define APPLIED_VFO (VFO[appliedVfo])
#define ACTIVE_VFOX (VFOX[settings.activeVfo])
#define APPLIED_VFOX (VFOX[appliedVfo])
#define ACTIVE_RXPLAN (plans[VFOX[settings.activeVfo].rxplan])
#define ACTIVE_TXPLAN (plans[VFOX[settings.activeVfo].txplan])
#define VFOA_ISACTIVE (!settings.activeVfo)
#define VFOB_ISACTIVE (settings.activeVfo)

#define C16(x) ((U16*)&x)
#define C32(y) ((U32*)&y)

#define GREEN(g) .gh = g>>2, .gl = (g&3)<<1


