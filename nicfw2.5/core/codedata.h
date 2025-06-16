
//u8 code ROM[0xf800] _at_ 0;

const char code SPACE12 = ' ';
const char code SPACE11 = 32;
const char code SPACE10 = 32;
const char code SPACE9 = 32;
const char code SPACE8 = 32;
const char code SPACE7 = 32;
const char code SPACE6 = 32;
const char code SPACE5 = 32;
const char code SPACE4 = 32;
const char code SPACE3 = 32;
const char code SPACE2 = 32;
const char code SPACE1 = 32;
const char code SPACEZERO = 0;

const u32 code FREQ_MAX = 129999999l;


const chipFont code CHIPFONT[3] = {
    { 0x3bfbf, 8, 6, 0 },
    { 0x66c0, 8, 8, 1 },
    { 0x3b7c0, 16, 8, 2 }
};

#define FONT6X8BASE ((u32)CHIPFONT[0])
#define FONT8X8BASE ((u32)CHIPFONT[1])
#define FONT8X16BASE ((u32)CHIPFONT[2])

const u32 code  FREQ_MIN = 1800000l;
const u32 code  FREQ_MAX2 = 130000000l;


volatile u8 code SMETER_DPTT_YPOS = 11;
volatile u8 code SBAR_DPTT_YPOS = 2;
volatile u8 code VFOA_YPOS = 22;
volatile u8 code VFOB_YPOS = 83;
volatile u8 code VFOS_YPOS = 22;
volatile u8 code VFO_RXXPOS = 23;
volatile u8 code VFO_RXYPOS = 19;
volatile u8 code VFO_TXXPOS = 65;
volatile u8 code VFO_TXYPOS = 36;
volatile u8 code VFO_POWERX = 0;
volatile u8 code VFO_POWERY = 36;
volatile u8 code VFO_CH_NAMEX = 38;
volatile u8 code VFO_CH_NAMEY = 0;
volatile u8 code VFO_NAMEX = 0;
volatile u8 code VFO_NAMEY = 0;
volatile u8 code VFO_GROUPX = 0;
volatile u8 code VFO_GROUPY = 9;
volatile u8 code VFO_REVERSEX = 12;
volatile u8 code VFO_REVERSEY = 22;
volatile u8 code VFO_BWX = 38;
volatile u8 code VFO_BWY = 9;
volatile u8 code VFO_GR_LETTERSX = 29;
volatile u8 code VFO_GR_LETTERSY = 36;
volatile u8 code VFO_TX_STX = 55;
volatile u8 code VFO_TX_STY = 9;
volatile u8 code VFO_RX_STX = 78;
volatile u8 code VFO_RX_STY = 9;
volatile u8 code VFO_MODX = 103;
volatile u8 code VFO_MODY = 9;
volatile u8 code VFO_SCANSYMX = 1;
volatile u8 code VFO_SCANSYMY = 22;
volatile u8 code FLAGS_YPOS_DUAL = 70;
volatile u8 code FLAGS_YPOS_SINGLE = 113;
volatile u8 code FLAGS_TONEMONITORX = 69;
volatile u8 code FLAGS_DWX = 1;
volatile u8 code FLAGS_KLX = 11;
volatile u8 code FLAGS_BTX = 21;
volatile u8 code FLAGS_VOXX = 31;
volatile u8 code FLAGS_ASLX = 41;
volatile u8 code FLAGS_BATTX = 103;
volatile u8 code LARGE_CH_NAME = 0;
volatile u8 code SMETER_SPTT_YPOS = 11;
volatile u8 code SBAR_SPTT_YPOS = 2;
volatile u8 code DIM_INACTIVE_VFO = 0;
volatile u8 code VFO_HEIGHT = 45;
volatile u8 code VFO_LJ_FREQ = 0;
volatile u8 code VFO_CHANGERXFREQNOTBG = 0;
volatile u8 code SCOPE_SOLID = 0;
volatile u8 code FLAGS_PTTMODE = 51;

const u32 code  CRC32POLYNOMIAL = 0xEDB88320UL;
const u16 code  PLANMAGIC_ = 0xA46D;
const u16 code  SETTINGSMAGIC = 0xD82F;

//#define RGB565(r, gl, gh, b) ((r << 11) | (gh << 8) | (gl << 5) | (b))

const COLOR code COL_SMETEROFF     = { 0x8210 };
const COLOR code COL_SMETERLOW     = { 0x07C0 };
const COLOR code COL_SMETERMID     = { 0x07FF };
const COLOR code COL_SMETERHIGH    = { 0xA29F };
const COLOR code COL_SMETERTX      = { 0x001F };
const COLOR code COL_SMETERTXMOD   = { 0x07E0 };
const COLOR code COL_SMETEREXNOISE = { 0xF9AD };
const COLOR code COL_SUNIT         = { 0x07FF };
const COLOR code COL_PUNIT         = { 0xA29F };
const COLOR code COL_DBM           = { 0x6E8D };
const COLOR code COL_MENUENTRY     = { 0xD7FF };
const COLOR code COL_BATTICONBODY  = { 0xFE9A };
const COLOR code COL_FWBGROUND     = { 0x0000 };
const COLOR code COL_INPUT         = { 0x87D0 };
const COLOR code COL_MENUEDIT      = { 0x065F };
const COLOR code COL_MENU          = { 0xFFFF };
const COLOR code COL_MENUBG        = { 0x7800 };
const COLOR code COL_MENUEDITBG    = { 0x1280 };
const COLOR code COL_BLACK         = { 0x0000 };
const COLOR code COL_VFOPOWER      = { 0x7D1F };
const COLOR code COL_VFOCHNAME     = { 0xFFC5 };
const COLOR code COL_VFORXFREQ     = { 0xA7DF };
const COLOR code COL_VFOTXFREQ     = { 0x7FCF };
const COLOR code COL_VFOCORNER     = { 0xFDD4 };
const COLOR code COL_VFOCORNER2    = { 0xFEDB };
const COLOR code COL_VFOIDLE       = { 0xAA82 };
const COLOR code COL_VFOSCAN       = { 0x788E };
const COLOR code COL_VFORX         = { 0x2C42 };
const COLOR code COL_VFOTX         = { 0x0014 };
const COLOR code COL_VFOLABELS     = { 0x2E9F };
const COLOR code COL_ASLFLAG       = { 0x4A5F };
const COLOR code COL_BATTHIGH      = { 0x3FC7 };
const COLOR code COL_BATTLOW       = { 0x39DF };
const COLOR code COL_SCOPEBAR      = { 0xFFFF };
const COLOR code COL_SCOPEBARMID   = { 0x07FF };


//const u32 code  defaultFreq = 14400000l;
//const u32 code  deadFreq = 70000000l;


const char code TX_LABEL[] = "TX";
const char code RX_LABEL[] = "RX";
const char code STN_LABEL[] = "STN";
const char code DTMF_LABEL[] = "DTMF";
const char code SCAN_LABEL[] = "Scan ";
const char code ACIV_LABEL[] = "Actv ";

const char code FM[] = " FM";
const char code AM[] = " AM";
const char code USB[] = "USB";
const char code FMT[] = "FMT";
const char code NR[] = "N/R";
const char code optionAlways[] = "Always";
const char code optionSquelched[] = "Squelched";
const char code optionOff[] = "Off";
const char code optionOn[] = "On";
const char code optionNo[] = "No";
const char code optionYes[] = "Yes";
const char code optionWide[] = "Wide";
const char code optionNarrow[] = "Narrow";
const char code AUTO[] = "Auto";
const char code NA[] = "N/A";
const char code DUAL[] = "Dual";
const char code SINGLE[] = "Single";
const char code HYBRID[] = "Hybrid";
const char code ICON[] = "Icon";
const char code PERCENT[] = "Percent";
const char code VOLTS[] = "Volts";
const char code DIFFERENTIAL[] = "Differential";
const char code VOICE[] = "Voice";
const char code BOTH[] = "Both";
const char code AGC[] = "AGC";
const char code SOLID[] = "Solid";
const char code SEGMENT[] = "Segment";
const char code STEPPED[] = "Stepped";
const char code CANCEL[] = "Cancel";
const char code CRC[] = "CRC";
const char code OK[] = "OK ";
const char code BAD[] = "BAD";
const char code COSI[] = "I-COS";
const char code POWERON[] = "Power On";
const char code CLONE[] = "Clone";
const char code BOT[] = "BoT";
const char code EOT[] = "EoT";

const char code IF1[] = "8.46";
const char code IF2[] = "7.25";
const char code IF3[] = "6.35";
const char code IF4[] = "5.64";
const char code IF5[] = "5.08";
const char code IF6[] = "4.62";
const char code IF7[] = "4.23";


const char code SIGNATURE[] = " nicFW ";
const char code VERSION[] = "2.52.18";
const char code RELEASE_TYPE[] = "R";


u16 code  gainTable[] = {
    0x03BE,
    0x0000,
    0x0008,
    0x0010,
    0x0001,
    0x0009,
    0x0011,
    0x0002,
    0x000A,
    0x0012,
    0x0003,
    0x000B,
    0x0013,
    0x0004,
    0x000C,
    0x000D,
    0x001C,
    0x001D,
    0x001E,
    0x001F,
    0x003E,
    0x003F,
    0x005E,
    0x005F,
    0x007E,
    0x007F,
    0x009F,
    0x00BF,
    0x00DF,
    0x00FF,
    0x01DF,
    0x01FF,
    0x02BF,
    0x02DF,
    0x02FF,
    0x035E,
    0x035F,
    0x037E,
    0x037F,
    0x038F,
    0x03BF,
    0x03DF,
    0x03FF,
};


/*
COLOR code  COL_BLACK = { .RGB = { .r=0, .g=0, .g0=0, .b=0 } };
COLOR code  COL_RED = { .RGB = { .r=31, .g=0, .g0=0, .b=0 } };
COLOR code  COL_GREEN = { .RGB = { .r=0, .g=31, .g0=1, .b=0 } };
COLOR code  COL_BLUE = { .RGB = { .r=13, .g=13, .g0=0, .b=31 } };
COLOR code  COL_CYAN = { .RGB = { .r=0, .g=31, .g0=1, .b=31 } };
COLOR code  COL_MAGENTA = { .RGB = { .r=31, .g=0, .g0=0, .b=31 } };
COLOR code  COL_YELLOW = { .RGB = { .r=31, .g=31, .g0=1, .b=0 } };
COLOR code  COL_WHITE = { .RGB = { .r=31, .g=31, .g0=1, .b=31 } };
COLOR code  COL_LYELLOW = { .RGB = { .r=31, .g=31, .g0=1, .b=20 } };
COLOR code  COL_ORANGE = { .RGB = { .r=31, .g=20, .g0=1, .b=0 } };
COLOR code  COL_GREY = { .RGB = { .r=20, .g=20, .g0=1, .b=20 } }; // yes I'm British. I don't mind missing the u in color, but I draw the line at gray
COLOR code  COL_DGRAY = { .RGB = { .r=10, .g=10, .g0=0, .b=10 } }; // well whatever...
*/


