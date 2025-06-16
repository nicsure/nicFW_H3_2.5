void channelLoadMap(void)
{
    u8 i;
    u16 addr;
    for(i=0; i<200; i++)
    {
        addr = i<<5;
        eepromRead(addr, (u8*)&(channelMap[i]), 4);
        eepromRead(addr+13, (u8*)&(groupMap[i]), 2);
    }    
}

const u8 channelValidateGroup(u8 candidate, const u8 dir)
{
    u8 j, i;
    const U16* map;
    map = (U16*)&groupMap;
    for(j=0; j!=17; j++)
    {
        if(candidate>15) candidate=1;
        if(candidate<1) candidate=15;
        for(i = 2; i!=200; i++)
        {
            if( isValidFreq(&channelMap[i]) && channelCheckGroup(i, candidate) )
                return candidate;
        }
        candidate+=dir;
    }
    return 0;
}

//void channelUpdateMap(const u8 index, const u32 freq)
//{
//    channelMap[index] = freq;
//}

//void channelUpdateGroupMap(const u8 index, const u16 groupw)
//{
//    groupMap[index] = groupw;
//}

const u8 channelCheckGroup(const u8 channel, const u8 group)
{
    const U16* groupw = (U16*)&(groupMap[channel]);
    return groupw->nibbles.n0 == group || 
           groupw->nibbles.n1 == group ||
           groupw->nibbles.n2 == group ||
           groupw->nibbles.n3 == group;
}

const u8 channelValidateOrNext(u8 current, const u8 direction, const u8 group, const bit next)
{
    // vfo a is channel 0, vfo b is channel 1. Pre programmed channels start from 2.
    // we don't want to check the VFOs only the pre programmed channels 2-200
    u8 i;
    bit currentValid;
    currentValid = !next && current>1 && isValidFreq(&channelMap[current]);
    if(currentValid)
    {
        if(group==0 || channelCheckGroup(current, group))
            return current;
    }
    for(i=0; i<200; i++)
    {
        current+=direction;
        if(current<2 || current==0xff) current=199; else if(current>199) current=2;
        if(isValidFreq(&channelMap[current]) && (group==0 || channelCheckGroup(current, group)))
            return current;
    }
    if(clampFreq(&(channelMap[2])))
    {
        channelMap[2]=defaultFreq;
        memCpy2(&defaultFreq, TXT, 4);
        memCpy2(&defaultFreq, &TXT[4], 4);
        memBlank(&TXT[8], 24);
        eepromWrite(64, TXT, 32);
    }
    return 2;
}

void channelRead(const u8 channelNum, channelInfo* vfo)
{
    eepromRead(channelNum<<5, (u8*)vfo, 32);
}

void channelLoad(const u8 channelNum, const u8 vfoPosition)
{
    channelInfo* vfo;
    channelXtra* vfox;

    vfo = &VFO[vfoPosition];
    channelRead(channelNum, vfo);
    memCpySpc(vfo->name, vfo->name, 11);
    vfox = &VFOX[vfoPosition];
    vfox->number = channelNum;
    validateVfo(vfoPosition);
    displayVfoRefresh(vfoPosition, !loopMode);
}

void channelSprintName(const u8 channelNum)
{
    eepromRead((channelNum<<5)+20, TXT, 12);
    memCpySpc(TXT, TXT, LARGE_CH_NAME ? 8:12);
}

void channelSave(const u8 vfoPosition)
{
    channelInfo* vfo = &VFO[vfoPosition];
    channelXtra* vfox = &VFOX[vfoPosition];
    const u16 addr = (vfox->number)<<5;
    eepromWrite(addr, (u8*)vfo, 32);
}

void channelSaveActive(void)
{
    channelSave(settings.activeVfo);
}

void channelActiveToMenu(void)
{
    bandwidthMenuVal = ACTIVE_VFO.bits.bandwidth;
    modulationMenuVal = ACTIVE_VFO.bits.modulation;
    busyLockMenuVal = ACTIVE_VFO.bits.busyLock;
    pttIDMenuVal = ACTIVE_VFO.bits.pttID;
    txPowerMenuVal = ACTIVE_VFO.txPower;
    txMaxPowerMenuVal = planPower(&plans[ACTIVE_VFOX.txplan], 255); //  ACTIVE_VFOX.txPower;
    rxSubToneMenuVal = ACTIVE_VFO.rxSubTone.value;
    txSubToneMenuVal = ACTIVE_VFO.txSubTone.value;    
}

void channelActiveFromMenu(void)
{
    ACTIVE_VFO.bits.bandwidth = bandwidthMenuVal;
    ACTIVE_VFO.bits.modulation = modulationMenuVal;
    ACTIVE_VFO.bits.busyLock = busyLockMenuVal;
    ACTIVE_VFO.bits.pttID = pttIDMenuVal;
    ACTIVE_VFO.txPower = txPowerMenuVal;
    ACTIVE_VFO.rxSubTone.value = rxSubToneMenuVal;
    ACTIVE_VFO.txSubTone.value = txSubToneMenuVal;
}

void channelGroupLabel(const u8 group)
{
    if(group)
    {
        eepromRead(0x1c90 + (u16)((group-1)*6), TXTEDIT, 6);
        memCpySpc(TXTEDIT, TXT, 5);
        
        TXT[6]=0;

        //for(u8 i=0; i!=5; i++)
        //{
        //    if(TXT[i] == 0 || TXT[i] == 255)
        //        TXT[i] = 32;
        //}
        if(TXT[0]==32)
        {
            memCpy2(GRPn, TXT, 6);
            TXT[4]=groupLetter(group);
        }
    }
    else
        memCpy2(&SPACE5, TXT, 6);
}