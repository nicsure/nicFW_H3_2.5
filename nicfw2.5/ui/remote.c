void remoteSendColor(const COLOR col)
{
    uartSendByte(col.bytes.c1);
    uartSendByte(col.bytes.c2);
}

void remoteSendSBarYPos(void)
{
    uartSendByte(105);
    uartSendByte(displayGetSMETER_YPOS());    
}

void remoteText(const char* text, const chipFont* font, const u8 x, const u8 y, const COLOR col, const bit overSize)
{
    if(remoteActive)
    {
        u8 cnt=0;
        uartSendByte(100); // packet id
        uartSendByte(font->number | (overSize?0x80:0));
        uartSendByte(x);
        uartSendByte(y);
        remoteSendColor(col);
        remoteSendColor(COL_BGROUND);
        do
        {
            uartSendByte(text[cnt]);
        }
        while(text[cnt++]); // ensures null gets sent to signal end of packet
        uartSendNull();
        feedTheDog();
    }
}

void remoteFill(const u8 x, const u8 y, const u8 w, const u8 h, const COLOR col)
{
    if(remoteActive && !remoteSuspendFill)
    {
        uartSendByte(101); // packet id
        uartSendByte(x);
        uartSendByte(y);
        uartSendByte(w);
        uartSendByte(h);
        remoteSendColor(col);
        uartSendNull();
        feedTheDog();
    }
}

void remoteSymbol(const u8 sym, const u8 x, const u8 y, const COLOR col)
{
    if(remoteActive)
    {
        uartSendByte(102); // packet id
        uartSendByte(sym);
        uartSendByte(x);
        uartSendByte(y);
        remoteSendColor(col);
        remoteSendColor(COL_BGROUND);
        uartSendNull();
        feedTheDog();
    }
}


void remoteSendLedStatus(void)
{
    if(remoteActive)
    {
        u8 b = 112;
        if(RXA_LED) b|=RXALED;
        if(TXA_LED) b|=TXALED;
        if(RXB_LED) b|=RXBLED;
        if(TXB_LED) b|=TXBLED;
        if(lastLedStatus!=b)
        {
            uartSendByte(b);
            lastLedStatus=b;
        }
        uartSendNull();
        feedTheDog();
    }
}
