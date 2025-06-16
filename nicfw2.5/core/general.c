const u8 isValidFreq(const u32* freq)
{
    return *freq>=FREQ_MIN && *freq<=FREQ_MAX;
}

const u32 Pow10(u8 exp)
{
    u32 mag = 1;
    while(exp--)
        mag*=10;
    return mag;
}

const u8 countDigits(u32 val)
{
    u8 cnt = 0;
    do
    {
        val/=10;
        cnt++;
    } while(val);
    return cnt;
}

const u16 decToOct(u16 dec)
{
    u16 oct = 0;
    u16 bitshift = 0;
    while(dec)
    {
        u8 mod = dec % 10;
        if(mod > 7) return 0;
        dec /= 10;
        oct += mod << bitshift;
        bitshift += 3;
    }
    return oct;
}

const char groupLetter(const u8 groupNumber)
{
    return !groupNumber?32:groupNumber+64;
}

const u8 isFreqVhf(const u32* freq, const u8 rx)
{
    // vfox->rxIsVhf = (vfo->rxFreq.value/10000) < settings.rxSplit;
    return (*freq/10000) < (rx ? settings.rxSplit : settings.txSplit);
}

void sprint_power(const u8 dutyCycle, const bit isVhf)
{
    if(dutyCycle)
    {
        const u8 watts = calibPwmToPower(dutyCycle, isVhf);
        TXT[1]='.';
        TXT[3]='W';
        TXT[4]=0;
        SPRINT_NUMBER(TXT, watts/10, 1, 255, 0, 0);
        SPRINT_NUMBER(&TXT[2], watts%10, 1, 255, 0, 0);
    }
    else
    {
        memCpy2(NT, TXT, 5);
    }
}

void sprint_number(char* buffer, const bit padSpaces, const bit nullTerminate)
{
    u8 i, cnt, dig;
    // the global xdata vars sp_Units, sp_Decimals and sp_Value need to be set before calling
    //
    // decimals being 0 would create a decimal point at the end of the string with no following
    // digits, this is desired behavior during user input, the user may press '.' and this needs to
    // show on the display before the user keys in the decimal part of the input.
    // To print a number with no decimal point at all, set decimals to 255 (technically -1)
    //
    // cnt is the total length of the string, if decimals is 255 (-1) this prevents the '.' and also
    // ensures cnt takes the missing '.' into account by subtracting 1
    cnt = sp_Units + sp_Decimals + 1; 
    if(nullTerminate) buffer[cnt] = 0; // sometimes we need to insert the number into a larger string
    while(cnt--) // work backwards
    {
        if(!sp_Decimals) buffer[cnt--] = '.'; // decimals being 0 means we need to interject a '.' here
        sp_Decimals--;
        dig = sp_Value % 10; // grab the next least significant base 10 digit
        buffer[cnt] = dig + 48; // adjust it to ASCII and place in buffer
        sp_Value/=10; // move to next least significant digit
    }
    if(padSpaces) // left padding is spaces instead of the 0's which will have been set previously.
    {
        sp_Units--; // we want to leave at least 1 unit digit
        for(i=0; i!=sp_Units; i++) // loop all but the last of the unit digits, most significant first
        {
            if(buffer[i]=='0') // if it's a '0'
                buffer[i]=' '; // replace it with a space
            else
                break; // if we encounter a non 0 digit, there's no further need to continue
        }
    }
}

const u8 clampFreq(u32* freq)
{
    if( ((U32*)freq)->bytes.byte3==0xFF) { *freq=defaultFreq; } else
    if(*freq<FREQ_MIN) { *freq=FREQ_MIN; return 1; } else
    if(*freq>FREQ_MAX) { *freq=FREQ_MAX; return 1; }
    return 0;
}


const u8 subCounter(u8* counter, const u8 by)
{
    if(*counter)
    {
        if(*counter > by)
            *counter -= by;
        else
        {
            *counter = 0;
            return 1;
        }
    }
    return 0;
}

const u8 crc32(void)
{
    u32 fwcrc;
    U16 temp16;
    u8 temp8;
    fwcrc = 0;
    temp16.value=0;
    fwcrc--;
    for (; temp16.bytes.hi != 0xf8U; temp16.value++)
    {
        feedTheDog();
        fwcrc ^= ((u8 code *)temp16.value)[0];
        for (temp8 = 0; temp8 != 8; temp8++) 
        {
            if (fwcrc & 1)
                fwcrc = (fwcrc >> 1) ^ CRC32POLYNOMIAL;
            else
                fwcrc >>= 1;
        }
    }
    return fwcrc==0;
}