const u8 planIsValid(void)
{
    return planMagic.value == PLANMAGIC_;
}

const u8 planMatch(const u32* freq)
{
    u8 i;
    if(planIsValid())
    {
        for(i=0; i!=20; i++)
        {
            const planInfo* info = &(plans[i]);
            if(*freq>=info->startFreq && *freq<info->endFreq)
            {
                return i;
            }
        }
    }
    else
    {
        planInfo* info = &(plans[19]);
        info->bits.txAllowed=1;
        info->bits.modulation=1;
        info->bits.bandwidth=0;
        info->bits.wrap=0;
        info->maxPower=160;
    }
    return 19;
}

void planFindFMT(void)
{
    u8 i;
    for(i=0; i!=20; i++)
    {
        const planInfo* info = &(plans[i]);
        if(info->bits.bandwidth==5)
        {
            fmtPlan = i;
            return;
        }
    }        
    fmtPlan=0xff;
}

const u8 planModulation(const planInfo* plan, const u8 desiredModulation)
{
    // modulations in plan : 0=Ignore, 1=FM, 2=AM, 3=USB, 4=FM Enforce, 5=AM Enforce, 6=USB Enforce, 7=band is excluded
    // modulations for main system 0=Automatic, 1=FM, 2=AM, 3=USB, 4=disallow use    
    const u8 planMod = plan->bits.modulation; // get the modulation set for the band
    if(planMod&4) // if bit 4 is set, this is an enforcement
    {
        return (planMod&3)+1; // clear bit 4 and return the enforced modulation, add one as the range will be 0-2 and it needs to be 1-3
    }
    if(desiredModulation) // if a particular modulation is requested (i.e. not automatic)
        return desiredModulation; // just return the requested modulation
    // otherwise the requested modulation is set to automatic
    // so long as the plan is not set to "ignore" return the plan's set modulation, otherwise default to FM
    return planMod?planMod:1;
}

const u8 planBandwidth(const planInfo* plan, const u8 desiredBandwidth)
{
    u8 planBw = plan->bits.bandwidth;
    if(planBw==5)
        planBw=0;
    if(planBw>2)
    {
        return planBw-3;        
    }
    if(planBw) planBw--;
    return desiredBandwidth>1?planBw:desiredBandwidth;
}

const u8 planPower(const planInfo* plan, const u8 desiredPower)
{
    u8 max;
    if(!(plan->bits.txAllowed))
        return 0;
    max = plan->maxPower;
    return desiredPower<max || !max ? desiredPower : max;
}

const u8 planBeforeStart(const channelInfo* vfo, const planInfo* plan)
{
    return vfo->rxFreq.value<plan->startFreq;
}

const u8 planPastEnd(const channelInfo* vfo, const planInfo* plan)
{
    return vfo->rxFreq.value>=plan->endFreq;
}

void subWA(void)
{
    wrapAdjustment -= settings.step;;
}

void calcWrapAdjustment(const channelInfo* vfo, const planInfo* plan)
{
    if(planBeforeStart(vfo, plan))
    {
        wrapAdjustment = plan->endFreq;
        subWA();
    }
    else
    if(planPastEnd(vfo, plan))
    {
        wrapAdjustment = plan->startFreq;
    }
    else
    {
        wrapAdjustment = 0;
        return;
    }
    wrapAdjustment -= vfo->rxFreq.value;
}

void addWA(channelInfo* vfo)
{
    vfo->rxFreq.value+=wrapAdjustment;
    vfo->txFreq.value+=wrapAdjustment;
}

void planWrapVfo(const u8 vfoPosition)
{    
    const channelXtra* vfox = &VFOX[vfoPosition];
    const planInfo* plan = &plans[vfox->rxplan];    
    if(plan->bits.wrap)
    {
        channelInfo* vfo = &VFO[vfoPosition];
        calcWrapAdjustment(vfo, plan);
        addWA(vfo);
    }
}

void planApply(const u8 vfoPosition)
{
    u8 maxCalibPwr;
    channelInfo* vfo = &VFO[vfoPosition];
    channelXtra* vfox = &VFOX[vfoPosition];
    vfox->rxplan=planMatch(&(vfo->rxFreq.value));
    vfox->txplan=planMatch(&(vfo->txFreq.value));
    vfox->modulation=planModulation(&plans[vfox->rxplan], vfo->bits.modulation);
    vfox->rxBandwidth=planBandwidth(&plans[vfox->rxplan], vfo->bits.bandwidth);
    vfox->txBandwidth=planBandwidth(&plans[vfox->txplan], vfo->bits.bandwidth);    
    maxCalibPwr = vfox->txIsVhf ? tuning.vhfPeakSetting : tuning.uhfPeakSetting;
    vfox->txPower=planPower(&plans[vfox->txplan], vfo->txPower > maxCalibPwr ? maxCalibPwr : vfo->txPower);
}