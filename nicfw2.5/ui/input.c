void inputPrepareString(const u8 charCount, const u8 x, const u8 y, const u8 font, const char* source)
{
    inputStringSource = (u16)source;
    memCpySpc(source, TXTEDIT, charCount+1);
    inputPrepare(charCount, 0, x, y, font+4);
    inputStringParseKey(99);        
}

void inputPrepareDTMF(const u8 digitCount, const u8 x, const u8 y, const u8 font, const dtmfSequence* sequence)
{
    memBlank(sequence, 5);
    inputStringSource = (u16)sequence;
    dtmfSeqToString(sequence, '-', TXTEDIT);
    inputPrepare(digitCount, 0, x, y, font+10);    
    inputDtmfParseKey(99);
}

void inputPrepare(const u8 units, const u8 decimals, const u8 x, const u8 y, const u8 font)
{
    inputUnitsCnt = units;
    inputUnits = units;
    inputDecimalCount = decimals;
    inputDecimals = decimals;
    inputValue = 0;
    inputX = x;
    inputY = y;
    inputFont = font; 
    if(inputFont>9)
    {
        inputFont-=10;
        inputAsDTMF = 1;
    }
    else
        inputAsDTMF = 0;
    if(inputFont>4 && !inputAsDTMF)
    {
        inputFont-=4;
        inputAsString=1;
    }
    else
        inputAsString=0;
    inputMode |= INPUTMODE_INPUT;
    inputMag = Pow10(decimals);
    inputState = INPUT_IDLE;
}

void inputTick(void)
{
    //if(longPress!=KEY_NONE)
    //{
    //    inputLongPress(longPress);
    //    longPress = KEY_LONGACTIONED;
    //}
    if(inputAsDTMF)
    {
        inputDtmfParseKey(keypadPTT() ? 0x80 : keypadSinglePress());
    }
    else
    if(inputAsString)
        inputStringParseKey(keypadSinglePress());
    else
    if(longPress!=KEY_NONE)
    {
        inputLongPress(longPress);
        longPress = KEY_LONGACTIONED;
    }
    else
        inputParseKey(keypadSinglePress());
}

void inputLongPress(const u8 key)
{
    u8 ch;
    if(inputUnits==4 && inputDecimals==5 && inputUnitsCnt<4 && inputUnitsCnt>0)
    {
        inputValue/=100000l;
        ch = C32(inputValue)->bytes.byte0 + 1;
        if(ch>1 && ch<200)
        {
            switch(key)
            {
                case KEY_MENU:
                    channelMap[ch]=ACTIVE_VFO.rxFreq.value;
                    eepromWrite(ch<<5, (u8*)&ACTIVE_VFO, 32);
                    break;
                case KEY_EXIT:
                    voicePlay(VOICE_ID_DELETE_CHANNEL, 0);
                    channelMap[ch]=0l;
                    eepromWrite(ch<<5, nowt, 32);              
                    break;
            }
            radioToggleVfoMode(1, 0, ch);                                  
            inputParseKey(KEY_EXIT);
        }
    }
}

void inputStringEditChar(const u8 key)
{
    char c = TXTEDIT[inputDecimals];
    switch(key)
    {
        case 0:
            switch(c)
            {
                default: c='0'; break;
                case '0': c=' '; break;
            }
            break;
        case 1:
            switch(c)
            {
                default: c='1'; break;
                case '1': c='-'; break;
                case '-': c='.'; break;
                case '.': c=','; break;
                case ',': c='@'; break;
            }
            break;
        case 2:
            switch(c)
            {
                default: c='2'; break;
                case '2': c='A'; break;
                case 'A': c='B'; break;
                case 'B': c='C'; break;
                case 'C': c='a'; break;
                case 'a': c='b'; break;
                case 'b': c='c'; break;
            }
            break;
        case 3:
            switch(c)
            {
                default: c='3'; break;
                case '3': c='D'; break;
                case 'D': c='E'; break;
                case 'E': c='F'; break;
                case 'F': c='d'; break;
                case 'd': c='e'; break;
                case 'e': c='f'; break;
            }
            break;
        case 4:
            switch(c)
            {
                default: c='4'; break;
                case '4': c='G'; break;
                case 'G': c='H'; break;
                case 'H': c='I'; break;
                case 'I': c='g'; break;
                case 'g': c='h'; break;
                case 'h': c='i'; break;
            }
            break;
        case 5:
            switch(c)
            {
                default: c='5'; break;
                case '5': c='J'; break;
                case 'J': c='K'; break;
                case 'K': c='L'; break;
                case 'L': c='j'; break;
                case 'j': c='k'; break;
                case 'k': c='l'; break;
            }
            break;
        case 6:
            switch(c)
            {
                default: c='6'; break;
                case '6': c='M'; break;
                case 'M': c='N'; break;
                case 'N': c='O'; break;
                case 'O': c='m'; break;
                case 'm': c='n'; break;
                case 'n': c='o'; break;
            }
            break;
        case 7:
            switch(c)
            {
                default: c='7'; break;
                case '7': c='P'; break;
                case 'P': c='Q'; break;
                case 'Q': c='R'; break;
                case 'R': c='S'; break;
                case 'S': c='p'; break;
                case 'p': c='q'; break;
                case 'q': c='r'; break;
                case 'r': c='s'; break;
            }
            break;
        case 8:
            switch(c)
            {
                default: c='8'; break;
                case '8': c='T'; break;
                case 'T': c='U'; break;
                case 'U': c='V'; break;
                case 'V': c='t'; break;
                case 't': c='u'; break;
                case 'u': c='v'; break;
            }
            break;
        case 9:
            switch(c)
            {
                default: c='9'; break;
                case '9': c='W'; break;
                case 'W': c='X'; break;
                case 'X': c='Y'; break;
                case 'Y': c='Z'; break;
                case 'Z': c='w'; break;
                case 'w': c='x'; break;
                case 'x': c='y'; break;
                case 'y': c='z'; break;
            }
            break;
    }
    TXTEDIT[inputDecimals] = c;
}

void inputCancelDTMF(void)
{
    inputState = INPUT_CANCELLED;
    inputMode &= ~INPUTMODE_INPUT;
    lcdCls();
    displayRefreshFull(); 
}

void inputDtmfParseKey(const u8 key)
{
    u8 c2a = 0;
    if(inputDecimals<inputUnits)
    {
        if(key<10)
            c2a = key+48;
        else
        if(key<14)
            c2a = key+55;
        else
        if(key==14)
            c2a = '*';
        else
        if(key==15)
            c2a = '#';
    }
    if(c2a)
        TXTEDIT[inputDecimals++] = c2a;
    else
    if(longPress == KEY_EXIT)
    {
        longPress = KEY_LONGACTIONED;
        inputCancelDTMF();
        return; 
    }
    else
    if(key==KEY_FLSH)
    {
        if(inputDecimals)
            TXTEDIT[--inputDecimals] = '-';
        else
        {
            inputCancelDTMF();
            return;            
        }
    }
    else
    if(key==0x80)
    {
        dtmfSeqFromString();
        inputCancelDTMF();
        //playDtmfOnPTT=inputStringSource;  
        playDtmfOnPTT=1;  
        return;    
    }
    fontChipDrawText(TXTEDIT, &CHIPFONT[inputFont], inputX, inputY, COL_INPUT, 0);
}    


void inputStringParseKey(const u8 key)
{
    u8 i;
    if(key<10)
        inputStringEditChar(key);
    else
    {
        switch(key)
        {
            case KEY_UP:
                inputDecimals++;
                break;
            case KEY_DOWN:
                inputDecimals--;
                break;
            case KEY_MENU:
                memCpy2(TXTEDIT, (char xdata *)inputStringSource, inputUnits+1);
            case KEY_EXIT:
                inputState = INPUT_CANCELLED;
                inputMode &= ~INPUTMODE_INPUT;    
                return;
            case KEY_STAR:
                if(inputDecimals)
                {
                    for(i=inputDecimals-1; i!=inputUnits; i++)
                        TXTEDIT[i] = TXTEDIT[i+1];
                    TXTEDIT[inputUnits+1] = ' ';
                    inputDecimals--;
                }
                break;
            case KEY_HASH:
                if(inputDecimals<inputUnits-1)
                {
                    for(i=inputUnits-2; i>=inputDecimals && i!=0xff; i--)
                        TXTEDIT[i+1] = TXTEDIT[i];
                    TXTEDIT[inputDecimals] = ' ';
                }
                break;
            case 99:
                break;
            default:
                return;
        }
    }
    if(inputDecimals==inputUnits) inputDecimals=0;
    if(inputDecimals==0xff) inputDecimals=inputUnits-1;    
    fontChipDrawText(TXTEDIT, &CHIPFONT[inputFont], inputX, inputY, COL_INPUT, 0);
    singleChar[0] = TXTEDIT[inputDecimals];
    COL_BGROUND.value = COL_INPUT.value;
    fontChipDrawText(singleChar, &CHIPFONT[inputFont], inputX+(inputDecimals<<3), inputY, COL_FWBGROUND, 0);
    COL_BGROUND.value = COL_FWBGROUND.value;
}

void inputParseKey(const u8 key)
{
    bit cancel = 0;
    if(key<10)
    {
        if(octalInput && (key==8 || key==9)) return;
        if(inputUnitsCnt)
        {
            inputValue*=10;
            inputValue+=(key*inputMag);
            inputUnitsCnt--;
        }
        else
        {
            if(inputDecimalCount)
            {
                inputMag/=10;
                inputValue+=(key*inputMag);
                inputDecimalCount--;
            }
        }
    }
    else
    {
        switch(key)
        {
            case KEY_FLSH:
                if(offsetInput)
                {
                    offsetInput=1;
                    inputValue = ACTIVE_VFO.rxFreq.value;
                    goto INPUTAPPLY;
                }
                return;
            case KEY_DOWN:
            case KEY_UP:
                if(offsetInput)
                {
                    offsetInput = key==KEY_UP ? 3:2;
                    TXT[1]=0;
                    TXT[0]= key==KEY_UP ? '+':'-';
                    fontDraw8x8(TXT, inputX-8, inputY, COL_VFOTXFREQ, 0);
                }
                return;
            case KEY_EXIT:
                cancel = 1;
            case KEY_HASH:
            case KEY_MENU:
                INPUTAPPLY:
                inputUnitsCnt=0;
                inputDecimalCount=0;
                break;            
            case KEY_STAR:
                if(inputDecimals)
                {
                    inputUnitsCnt=0;
                    break;
                }
            case 0x99:
                break;
            default:
                return;
        }
    }
    if(!inputUnitsCnt && !inputDecimalCount)
    {
        if(octalInput && inputValue)
            inputValue = decToOct(inputValue)|0x8000;
        inputState = cancel?INPUT_CANCELLED:INPUT_APPLIED;
        inputMode &= ~INPUTMODE_INPUT;        
    }
    //else
    {
        if(inputFont==4)
            displayFreq(&inputValue, inputX, inputY, COL_INPUT, inputDecimals - inputDecimalCount, !inputUnitsCnt);
        else
        {
            SPRINT_NUMBER(TXT, inputValue, inputUnits, inputDecimals?inputDecimals:255, 1, 1);
            if(inputAsGroup)
            {
                TXT[0]=C32(inputValue)->bytes.byte0+64;
                TXT[1]=0;
            }
            if(inputDecimals)
            {
                if(inputUnitsCnt)
                    TXT[inputUnits]=0;
                else
                    TXT[inputUnits + (inputDecimals - inputDecimalCount) + 1]=0;
            }
            fontChipDrawText(TXT, &CHIPFONT[inputFont], inputX, inputY, COL_INPUT, 0);
        }
    }
}



