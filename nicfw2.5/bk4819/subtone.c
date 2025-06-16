


void stSetTone(u32 tone)
{
    U32 golay;
    //u8 stDev = 74;    
    bkTemp.bytes.lo = settings.stDev;
    //if(!C32(tone)->subTone.isDCS)
    if(!(tone&0x8000))
    {
        bkTemp.bytes.hi = 0x91;
        if(tone == 1050)
        {
            bkTemp.bytes.hi += 4;
            tone = 2625;
        }
        bkSetReg(0x51, bkTemp.value);
        tone *= (u32)1032444;
        tone /= (u32)500000;
        bkSetReg(0x07, tone);
    }
    else
    {
        bkTemp.bytes.hi = 0x81;                        
        bkSetReg(0x51, bkTemp.value);
        bkSetReg(0x07, 0x2775);
        //golay.value =  stGetGolay(C32(tone)->subTone.tone, C32(tone)->subTone.isInverted);
        golay.value =  stGetGolay(tone&0x3fff, tone&0x4000);
        
        bkSetReg(0x08, golay.words.lo & 0xfff);
        golay.value >>= 12;
        golay.bytes.byte1 &= 0xf;
        golay.bytes.byte1 |= 0x80;
        bkSetReg(0x08, golay.words.lo);
    }
}

const u16 nextDcs(const bit fwd, u16 word)
{
    u8 i = fwd?0:104;
    const u16 inval = word & 0x3fff;
    while(1)
    {
        if(fwd)
        {
            if(DCS[i] > inval)
                break;
            i++;
            if(i==105)
            {
                i=0;
                break;
            }
        }
        else
        {
            if(DCS[i] < inval)
                break;
            i--;
            if(i==0xff)
            {
                i=104;
                break;
            }
        }
    }    
    if(i)
    {
        word &= 0x4000;
        word |= 0x8000u;
        word |= DCS[i];
    }
    else
        word = 0;
    return word;
}

void sprint_dcs(const u16 word)
{
    u8 i;
    u16 masked;
    if(word&0x8000)
    {
        masked = word & 0x1ff;
        TXT[0]='D';
        for(i=3; i!=0; i--)
        {
            TXT[i]=(masked&7)+48;
            masked>>=3;
        }
        TXT[4]=word&0x4000 ? 'I':'N';
        TXT[5]=0;    
    }
    else
        memCpy2(optionOff, TXT, 4);
}

const u16 nextCtcss(const bit fwd, u16 word)
{
    u8 i = fwd?0:50;
    while(1)
    {
        if(fwd)
        {
            if(CTCSS[i] > word)
                break;
            i++;
            if(i==51)
            {
                i=0;
                break;
            }
        }
        else
        {
            if(CTCSS[i] < word)
                break;
            i--;
            if(i==0xff)
            {
                i=50;
                break;
            }
        }
    }
    word = CTCSS[i];
    return word;
}

const u32 stGetGolay(const u32 codeword, const bit rev)
{
    u8 i;
    u32 word;
    word = codeword + (u32)0x800;
    for(i=0; i<12; i++)
    {
        word<<=1;
        if(word & (u32)0x1000)
            word ^= (u32)0x8ea;
    }
    word &= (u32)0xffe;
    word <<= 11;
    word |= (codeword + (u32)0x800);
    if(rev)
        word ^= (u32)0x7fffffu;
    return word;
}

const u8 reverseGolay(void)
{
    u8 i;
    for(i=1; i!=105; i++)
    {
        if(dcsTemp == stGetGolay(DCS[i], 0))
            return i;
    }
    return 0;
}

const u8 decodeDcs(void)
{
    u8 i, dcsi;
    for(i=0; i<23; i++)
    {
        if( ((C32(dcsTemp)->bytes.byte1)&14) == 8)//  ((dcsTemp>>9) & (u32)7) == 4 )
        {
            dcsi = reverseGolay();
            if(dcsi) return dcsi;
        }
        if(dcsTemp & (u32)1)
            dcsTemp |= (u32)0x800000;
        dcsTemp >>= 1;
    }
    return 0;
}

u8 closestCtcss(const u16 raw)
{
    u8 i;
    s16 dif;
    for(i=0; i<50; i++)
    {
        dif = (s16)raw - RAW_CTCSS[i];
        if(dif>-20 && dif<20)
        {
            return i+1;
        }        
    }
    return 0;
}

const u8 stMonitor(void)
{    
    U16* reg68;
    U16* reg69;
    U16* reg6a;
    u16 ht;
    u8 ind;
    reg68 = bkGetReg(0x68);
    if(reg68->bytes.hi<0x80)
    {
        reg68->bytes.hi&=0x1f;
        ht = CTCSS[closestCtcss(reg68->value)];
        if(ht)
            heardTone = ht;
        return 1;
    }
    else
    {        
        reg69 = bkGetReg(0x69);
        if(reg69->bytes.hi<0x80)
        {
            //reg69->value=~reg69->value;
            reg69->bytes.hi &= 0xf;
            dcsTemp = reg69->value;
            dcsTemp<<=12;
            reg6a = bkGetReg(0x6a);
            //reg6a->value=~reg6a->value;
            reg6a->bytes.hi &= 0xf;
            dcsTemp |= reg6a->value;
            ind = decodeDcs();            
            if(ind) 
                heardTone = DCS[ind] | 0x8000;
            return 1;
        }   
    }    
    return 0;
}
