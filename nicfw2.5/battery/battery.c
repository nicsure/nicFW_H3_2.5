void batteryRead(void)
{
    ROMBNK |= 2;
    battAdc.value = ((u16)ADC10) << 4;
    battAdc.bytes.lo |= ((ADC1>>4)&0xf);
    if(xmitActive)
        battXmit = battAdc.value;
    else
        battReceive = battAdc.value;
    battAdc.value = (battAdc.value > 2828) ? battAdc.value-2828 : 0;
}

void batteryShow(const u8 x, const u8 y)
{
    s32 battDiff, ir;
    COLOR col;
    u16 b;
    col.value = battAdc.value > 950 ? COL_BATTHIGH.value : battAdc.value < 316 ? COL_BATTLOW.value : COL_BATTICONBODY.value;
    switch(settings.battStyle)
    {
        default:
        case 1: // icon
            b = battAdc.value / 66;
            lcdFill(x+1, y,   23, 8, col); // batt body
            lcdFill(x+2, y+1, 21, 6, COL_BGROUND); // inner gap
            lcdFill(x+3, y+2,  b, 4, col); // batt level
            lcdFill(x  , y+2,  1, 4, col); // batt nipple
            return;
        case 2: // percentage
            b = battAdc.value * 6;
            b /= 76;
            SPRINT_NUMBER(TXT, b, 3, 255, 1, 0);
            TXT[3] = '%';
            break;
        case 3: // voltage
            b = battAdc.value / 48;
            b += 58;
            SPRINT_NUMBER(TXT, b/10, 1, 255, 0, 0);
            SPRINT_NUMBER(&TXT[2], b%10, 1, 255, 0, 0);
            TXT[1] = '.';
            TXT[3] = 'V';
            break;
    }
    TXT[4] = 0;
    fontDraw6x8(TXT, x, y, col);
    if(settings.txCurrent && xmitActive)
    {
        battDiff = (s32)battReceive - (s32)battXmit;
        ir = ((-60 * (s32)battReceive) + 275560) / 1000;
        if(ir<30) ir=30;
        if(ir>100) ir=100;
        // 488
        battDiff *= 10000;
        battDiff /= ir;
        battDiff /= 488;
        if(battDiff<0) battDiff=0;
        if(battDiff>99) battDiff=99;

        SPRINT_NUMBER(TXT, battDiff, 1, 1, 1, 1);
        TXT[3]='A';
        TXT[4]=0;
        if(!(settings.pttMode & 1) && !VFO_CHANGERXFREQNOTBG) //VFO_CHANGERXFREQNOTBG
            COL_BGROUND.value = COL_VFOTX.value;        
        fontDraw6x8(TXT, VFO_POWERX, displayVfoPos(settings.activeVfo)+DIS(VFO_POWERY), COL_VFOPOWER);
        COL_BGROUND.value = COL_FWBGROUND.value;
    }
}