const u8 memCmp2(const u8* loc1, const u8* loc2, u8 length)
{
    while(length--)
    {
        if(loc1[length] != loc2[length])
            return 0;
    }
    return 1;
}

void memCpySpc(const char* src, char* dest, u8 length)
{
    char c;
    dest[length--]=0;
    while(length!=0xff)
    {
        c = src[length];
        if(c<32 || c>126) c=32;
        dest[length] = c;
        length--;
    }
}

void memCpy2(const void* src, void* dest, u8 length)
{
    while(length--)
    {
        ((u8*)dest)[length]=((u8*)src)[length];
    }
}

void memBlank(const void* target, u8 length)
{
    memFill(target, length, 0);
}

void memFill(const void* target, u8 length, const u8 value)
{
    while(length--)
        ((u8*)target)[length] = value;
}

u8 strcontains(char* haystack, char* needle) {
    char* h;
    char* n;
    if (!*needle) return 0;
    while (*haystack) {
        h = haystack;
        n = needle;
        while (*h && *n && (*h == *n)) { h++; n++; }
        if (!*n) { return 1; }
        haystack++;
    }
    return 0;
}