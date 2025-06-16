
void fontChipSendByte(u8 byt)
{
    u8 m;
    for(m=128; m!=0; m>>=1)
    {
        FONT_SCK = 0;
        FONT_SI = (byt & m);
        FONT_SCK = 1;
    }
}

const u8 fontChipReadByte(void)
{
    u8 byt = 0;
    u8 m;
    for(m=128; m!=0; m>>=1)
    {
        FONT_SCK = 0;
        if(FONT_SO) byt|=m;
        FONT_SCK = 1;
    }
    return byt;
}

void fontChipRead(const u8 cmd, const U32* addr, const u8 len, u8* destination)
{
    u8 c;
    FONT_SCK = 1;
    FONT_CS = 0;
    FONT_SI = 0;
    fontChipSendByte(cmd);
    fontChipSendByte(addr->bytes.byte2);
    fontChipSendByte(addr->bytes.byte1);
    fontChipSendByte(addr->bytes.byte0);
    fontChipSendByte(0xAA); // dummy byte
    for(c=0; c!=len; c++)
    {
        u8 byt = fontChipReadByte();
        destination[c] = byt;
    }
    FONT_SCK = 0;
    FONT_CS = 1;
    FONT_SI = 0;
}


void fontFillRegion(const u8* bytearray, u16 offset, u8 length, const COLOR col)
{
    u8 bitmap, mask;
    bit on;
    while(length--)
    {
        bitmap=bytearray[offset++];
        for(mask=1; mask!=0; mask<<=1)
        {
            on = bitmap&mask;
            lcd2Byte(on?col.bytes.c2:COL_BGROUND.bytes.c2, on?col.bytes.c1:COL_BGROUND.bytes.c1);
        }            
    }     
}

const COLOR lowerColor(COLOR col)
{
    if(dimColor)
    {
        switch(DIM_INACTIVE_VFO)
        {
            default:
                col.RGB.r>>=1;
                col.RGB.b>>=1;
                col.RGB.gl>>=1;
                col.RGB.gh>>=1;                                     
                break;
            case 2:
                col.bytes.c1 |= 0x1c; // 0b00011100;
                col.bytes.c2 |= 0xe7; // 0b11100111;
                break;
            case 0:
                break;
        }
    }
    return col;
}

void fontCustomSymbol(const u8 sym, const u8 x, const u8 y, const COLOR col)
{
    COLOR col2;
    col2.value = lowerColor(col).value;
    remoteSymbol(sym, x, y, col2);
    lcdRegion(x,y,x+7,y+7);
    fontFillRegion(customSymbols, sym<<3, 8, col2); // may need undo
}

void fontDrawHuge(const u8* font, const u8 ascii, const u8 x, const u8 y, const COLOR col)
{
    lcdRegion(x,y,x+15,y+15);
    fontFillRegion(font, ((u16)ascii)<<5, 32, col);
}

void fontChipDrawText(const char* text, const chipFont* font, u8 x, const u8 y, const COLOR col, const bit ds)
{
    u8 i;
    u8 j, yo, b1, b2;
    u8 k, ascii;
    u8 l, boxw, boxh;
    u8 mask;
    U32 addr;
    bit on;
    COLOR col2;
    col2 = lowerColor(col);
    remoteText(text, font, x, y, col2, ds);
    addr.value = 0;
    boxw = ds?font->width<<1:font->width;
    boxh = ds?16:8;
    for(i=0; i!=21; i++)
    {
        ascii = text[i];
        if(ascii==0) break;
        ascii-=32;
        if(ds && ascii>15 && ascii<26)
        {
            fontDrawHuge(hugeFontNumbers, ascii-16, x, y, col2);
        }
        else
        if(ds && ascii>32 && ascii<59)
        {
            fontDrawHuge(hugeUpperLetters, ascii-33, x, y, col2);
        }
        else
        if(ds && ascii>64 && ascii<91)
        {
            fontDrawHuge(hugeLowerLetters, ascii-65, x, y, col2);
        }
        else
        {
            if(font->byteSize==16 && ascii>15 && ascii<26)
            {
                memCpy2(&largeFontNumbers[ (((u16)ascii)-16)<<4  ], fontBuffer, 16);
            }
            else
            {
                addr.value = font->base + (ascii*font->byteSize);            
                fontChipRead(0xb, &addr, font->byteSize, fontBuffer);
            }
            for(j = 0; j<font->byteSize; j+=8)
            {         
                yo = y+j;
                if(ds) yo+=j;
                lcdRegion(x,yo,x+boxw-1,yo+boxh-1);
                for(k=0; k!=font->width; k++)
                {
                    const u8 bitmap=fontBuffer[j+k];
                    for(l = 0; l!=(ds?2:1); l++)
                    {
                        for(mask=1; mask!=0; mask<<=1)
                        {
                            on = bitmap&mask;
                            b1=on ? col2.bytes.c1 : COL_BGROUND.bytes.c1;
                            b2=on ? col2.bytes.c2 : COL_BGROUND.bytes.c2; // may need undo
                            lcd2Byte(b2, b1);
                            if(ds) lcd2Byte(b2, b1);
                        }
                    }                
                }            
            }
        }
        x+=boxw;
    }
}

void fontDraw6x8 (char* text, const u8 x, const u8 y, const COLOR col)
{
    fontChipDrawText(text, &FONT6x8, x, y, col, 0);
}

void fontDraw8x8 (char* text, const u8 x, const u8 y, const COLOR col, const bit ds)
{
    fontChipDrawText(text, &FONT8x8, x, y, col, ds);
}

void fontDraw8x16 (char* text, const u8 x, const u8 y, const COLOR col)
{
    fontChipDrawText(text, &FONT8x16, x, y, col, 0);
}
