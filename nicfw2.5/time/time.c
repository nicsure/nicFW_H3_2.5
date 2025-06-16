void delayL5(void)
{
    u8 i;
    for(i = 5; i != 0; i--) { }
}

//void delayRfi(void)
//{
//    u8 i;
//    for(i = 15; i != 0; i--) { }
//}

void delay100us(void)
{
    u16 j = 65;
    do
    {
        j--;
        feedTheDog();
    }
    while(j != 0);  
}

void delay(u16 ms)
{
    do
    {
        u8 u = 10;
        do
        {
            delay100us();
            u--;
        }
        while(u != 0);
        ms--;
    }
    while(ms != 0);
}
