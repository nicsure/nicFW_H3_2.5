	#define VOICE_ID_0                             0x00U
	#define VOICE_ID_1                             0x01U
	#define VOICE_ID_2                             0x02U
	#define VOICE_ID_3                             0x03U
	#define VOICE_ID_4                             0x04U
	#define VOICE_ID_5                             0x05U
	#define VOICE_ID_6                             0x06U
	#define VOICE_ID_7                             0x07U
	#define VOICE_ID_8                             0x08U
	#define VOICE_ID_9                             0x09U
	#define VOICE_ID_10                            0x0AU
	#define VOICE_ID_100                           0x0BU
	#define VOICE_ID_WELCOME                       0x0CU
	#define VOICE_ID_LOCK                          0x0DU
	#define VOICE_ID_UNLOCK                        0x0EU
	#define VOICE_ID_SCANNING_BEGIN                0x0FU
	#define VOICE_ID_SCANNING_STOP                 0x10U
	#define VOICE_ID_SCRAMBLER_ON                  0x11U
	#define VOICE_ID_SCRAMBLER_OFF                 0x12U
	#define VOICE_ID_FUNCTION                      0x13U
	#define VOICE_ID_CTCSS                         0x14U
	#define VOICE_ID_DCS                           0x15U
	#define VOICE_ID_POWER                         0x16U
	#define VOICE_ID_SAVE_MODE                     0x17U
	#define VOICE_ID_MEMORY_CHANNEL                0x18U
	#define VOICE_ID_DELETE_CHANNEL                0x19U
	#define VOICE_ID_FREQUENCY_STEP                0x1AU
	#define VOICE_ID_SQUELCH                       0x1BU
	#define VOICE_ID_TRANSMIT_OVER_TIME            0x1CU
	#define VOICE_ID_BACKLIGHT_SELECTION           0x1DU
	#define VOICE_ID_VOX                           0x1EU
	#define VOICE_ID_TX_OFFSET_FREQUENCY_DIRECTION 0x1FU
	#define VOICE_ID_TX_OFFSET_FREQUENCY           0x20U
	#define VOICE_ID_TRANSMITING_MEMORY            0x21U
	#define VOICE_ID_RECEIVING_MEMORY              0x22U
	#define VOICE_ID_EMERGENCY_CALL                0x23U
	#define VOICE_ID_LOW_VOLTAGE                   0x24U
	#define VOICE_ID_CHANNEL_MODE                  0x25U
	#define VOICE_ID_FREQUENCY_MODE                0x26U
	#define VOICE_ID_VOICE_PROMPT                  0x27U
	#define VOICE_ID_BAND_SELECTION                0x28U
	#define VOICE_ID_DUAL_STANDBY                  0x29U
	#define VOICE_ID_CHANNEL_BANDWIDTH             0x2AU
	#define VOICE_ID_OPTIONAL_SIGNAL               0x2BU
	#define VOICE_ID_MUTE_MODE                     0x2CU
	#define VOICE_ID_BUSY_LOCKOUT                  0x2DU
	#define VOICE_ID_BEEP_PROMPT                   0x2EU
	#define VOICE_ID_ANI_CODE                      0x2FU
	#define VOICE_ID_INITIALISATION                0x30U
	#define VOICE_ID_CONFIRM                       0x31U
	#define VOICE_ID_CANCEL                        0x32U
	#define VOICE_ID_ON                            0x33U
	#define VOICE_ID_OFF                           0x34U
	#define VOICE_ID_2_TONE                        0x35U
	#define VOICE_ID_5_TONE                        0x36U
	#define VOICE_ID_DIGITAL_SIGNAL                0x37U
	#define VOICE_ID_REPEATER                      0x38U
	#define VOICE_ID_MENU                          0x39U
	#define VOICE_ID_11                            0x3AU
	#define VOICE_ID_12                            0x3BU
	#define VOICE_ID_13                            0x3CU
	#define VOICE_ID_14                            0x3DU
	#define VOICE_ID_15                            0x3EU
	#define VOICE_ID_16                            0x3FU
	#define VOICE_ID_17                            0x40U
	#define VOICE_ID_18                            0x41U
	#define VOICE_ID_19                            0x42U
	#define VOICE_ID_20                            0x43U
	#define VOICE_ID_30                            0x44U
	#define VOICE_ID_40                            0x45U
	#define VOICE_ID_50                            0x46U
	#define VOICE_ID_60                            0x47U
	#define VOICE_ID_70                            0x48U
	#define VOICE_ID_80                            0x49U
	#define VOICE_ID_90                            0x4AU
	#define VOICE_ID_END                           0x4BU
    #define VOICE_COMB_PWR_SAVE                    0x4CU
	#define VOICE_NONE							   0xffu

    unsigned char code voiceTableDelay10ms[76] = {
//     0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x50, 0x32, 0x2D, 0x2D, 0x2D, 0x37, 0x37, 0x37, 0x32, 0x32, 0x3C, 0x37, 0x46, 0x46, 0x4B, 0x82, // 0
	0x82, 0x6E, 0x82, 0x46, 0x96, 0x64, 0x46, 0x6E, 0x78, 0x6E, 0x87, 0x64, 0x96, 0x96, 0x46, 0x9B, // 1
	0x91, 0x82, 0x82, 0x73, 0x78, 0x64, 0x82, 0x6E, 0x78, 0x82, 0x87, 0x6E, 0x55, 0x78, 0x64, 0x69, // 2
	0x9B, 0x5A, 0x50, 0x3C, 0x32, 0x55, 0x64, 0x64, 0x50, 0x36, 0x46, 0x46, 0x4B, 0x4B, 0x50, 0x50, // 3
	0x55, 0x4B, 0x4B, 0x32, 0x32, 0x32, 0x32, 0x37, 0x41, 0x32, 0x3C, 0x37,                         // 4
};

void voiceInit(void);
void voiceSend(u8 byt);
void voicePlay(const u8 id, const u8 pause);