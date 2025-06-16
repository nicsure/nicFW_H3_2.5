
#define OPTION 1
//#define OPTION2 1
//#define OPTION3 2
//#define OPTION4 3
//#define OPTION5 4
//#define OPTION6 5
//#define OPTION7 6
#define VALUE16 20
#define VALUE8 21
#define VALUE8ZO 22
#define VALUECTS 23
#define VALUEDCS 24
#define VALUE16ZO 25
#define VALUE8S 26
#define VALUE8L 27

#define menuNumber (*(menuAdvanced?&menuNumberAdv:&menuNumberUser))

#define menusBank (menuAdvanced?menus_adv:menus)

//#define MENU_COUNT ((sizeof(menus)/3)-1)
#define MENU_COUNT (((menuAdvanced?sizeof(menus_adv):sizeof(menus))/3)-1)

#define MENU_TYPE (*((u8*)menu))
#define MENU_VAR (*(((MENU*)menu)->var))
#define MENU_VAR16 (*(((MENU16*)menu)->var))

#define NEWVALUE_KEEPOLD 0xffff
#define NEWVALUE_ADD1 0xfffe
#define NEWVALUE_SUB1 0xfffd
#define NEWVALUE_1ST 0xfffc


typedef struct
{
    u8 type;
    u8 min;
    u8 max;
    u8 voicePrompt;
    u8* var;    
    char* title;
} MENU;

typedef struct
{
    u8 type;
    u8 min;
    u8 max;
    u8 voicePrompt;
    u8* var;    
    char* title;
    char* opts[7];
} MENUOPTS;

typedef struct
{
    u8 type;
    u8 min;
    u8 max;
    u8 voicePrompt;
    u8* var;    
    char* title;
    char* opts[2];
} MENUOPTS2;

typedef struct
{
    u8 type;
    u8 min;
    u8 max;
    u8 voicePrompt;
    u8* var;    
    char* title;
    char* opts[3];
} MENUOPTS3;

typedef struct
{
    u8 type;
    u8 min;
    u8 max;
    u8 voicePrompt;
    u8* var;    
    char* title;
    char* opts[4];
} MENUOPTS4;


typedef struct
{
    u8 type;
    u16 min;
    u16 max;
    u8 decimals;
    u8 voicePrompt;
    u16* var;    
    char* title;
} MENU16;

/*
typedef struct 
{
    u8 type;
    u8 max;
    u8 min;
    u8 voicePrompt;
    u8* var;
    char* title;
} MENUVALUE8;

typedef struct 
{
    u8 type;
    u8 decimals;
    u16 max;
    u16 min;
    u8 voicePrompt;
    u16* var;
    char* title;
} MENUVALUE16;

typedef struct 
{
    u8 type;
    u8 voicePrompt;
    u8* var;
    char* title;
    char** option[2];
} MENUOPTION2;

typedef struct 
{
    u8 type;
    u8 voicePrompt;
    u8* var;
    char* title;
    char** option[3];
} MENUOPTION3;

typedef struct 
{
    u8 type;
    u8 voicePrompt;
    u8* var;
    char* title;
    char** option[4];
} MENUOPTION4;

typedef struct 
{
    u8 type;
    u8 voicePrompt;
    u8* var;
    char* title;
    char** option[5];
} MENUOPTION5;

typedef struct 
{
    u8 type;
    u8 voicePrompt;
    u8* var;
    char* title;
    char** option[6];
} MENUOPTION6;

typedef struct 
{
    u8 type;
    u8 voicePrompt;
    u8* var;
    char* title;
    char** option[7];
} MENUOPTION7;
*/

void menuDraw(const u16 newValue);
void menuTick(void);
void menuInit(void);
void menuDrawPin(void);

