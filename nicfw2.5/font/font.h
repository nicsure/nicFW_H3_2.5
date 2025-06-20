u8 code customSymbols[] =
{
    0x1e, 0x05, 0x05, 0x1e, 0xf8, 0xa8, 0xa8, 0x50, // 0 // A/B
    0x3c, 0x5a, 0x99, 0x99, 0x99, 0x99, 0x5a, 0x3c, // 1 // no entry sign 
    0x00, 0x0c, 0x02, 0x7f, 0xf0, 0xf0, 0xe0, 0x00,	// 2 // music note
    0x00, 0x81, 0xc3, 0xe7, 0x7e, 0x3c, 0x18, 0x00, // 3 // RIGHT direction arrow
    0x70, 0x38, 0x1c, 0x0e, 0x0e, 0x1c, 0x38, 0x70, // 4 // UP direction arrow
    0x0e, 0x1c, 0x38, 0x70, 0x70, 0x38, 0x1c, 0x0e, // 5 // DOWN direction arrow
    0x0c, 0x9e, 0xde, 0x7e, 0x3e, 0x1e, 0x1e, 0x0c, // 6 // speech bubble
    0x3e, 0x41, 0x3e, 0x08, 0x08, 0x78, 0x08, 0x78, // 7 // key symbol
    0x0e, 0x11, 0xa0, 0xc7, 0xe3, 0x05, 0x88, 0x70, // 8 // scan sign
	0x70, 0x78, 0x4C, 0x46, 0x4C, 0x78, 0x70, 0x00,	// 9 // outlined chevron 
    0x7f, 0x06, 0x18, 0x7f, 0x3e, 0x41, 0x41, 0x3e, // 10 // (NO)
    0x7e, 0x09, 0x09, 0x7e, 0x7e, 0x09, 0x09, 0x7e, // 11 // (AA)
    0x82, 0x44, 0x28, 0xfe, 0x92, 0xaa, 0x44, 0x00, // 12 // bluetooth icon
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 13 // blanker
    0x00, 0x7e, 0x7e, 0x00, 0x00, 0x7e, 0x7e, 0x00, // 14 // pause
    0xff, 0x81, 0x42, 0x3c, 0x00, 0xff, 0x09, 0x0f, // 15 // dp
    0x8e, 0x89, 0x89, 0x79, 0x00, 0xff, 0x09, 0x0f, // 16 // sp
};

u8 code hugeFontNumbers[] = 
{
    // char '0'
    0xF8, 0x0F, 0xFC, 0x1F, 0xFE, 0x3F, 0x0F, 0x78, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 
    0x07, 0x70, 0x0F, 0x78, 0xFE, 0x3F, 0xFC, 0x1F, 0xF8, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char '1'
    0x00, 0x00, 0x00, 0x70, 0x0C, 0x70, 0x0E, 0x70, 0x0F, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 
    0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char '2'
    0x1C, 0x70, 0x1E, 0x78, 0x1F, 0x7C, 0x0F, 0x7E, 0x07, 0x7F, 0x87, 0x77, 0xC7, 0x73, 0xE7, 0x71, 
    0xF7, 0x70, 0x7F, 0x70, 0x3F, 0x70, 0x1E, 0x70, 0x0C, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char '3'
    0x1C, 0x1C, 0x1E, 0x3C, 0x1F, 0x7C, 0x0F, 0x78, 0x07, 0x70, 0xC7, 0x71, 0xC7, 0x71, 0xC7, 0x71, 
    0xC7, 0x71, 0xE7, 0x73, 0xFF, 0x7F, 0x3E, 0x3E, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char '4'
    0xF0, 0x03, 0xF8, 0x03, 0xFC, 0x03, 0xBE, 0x03, 0x9F, 0x73, 0x8F, 0x73, 0x87, 0x73, 0xFF, 0x7F, 
    0xFF, 0x7F, 0xFF, 0x7F, 0x80, 0x73, 0xC0, 0x77, 0xC0, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char '5'
    0xFF, 0x1C, 0xFF, 0x3C, 0xFF, 0x7C, 0xE7, 0x78, 0xE7, 0x70, 0xE7, 0x70, 0xE7, 0x70, 0xE7, 0x70, 
    0xE7, 0x70, 0xE7, 0x79, 0xE7, 0x7F, 0xC7, 0x3F, 0x87, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char '6'
    0xF0, 0x1F, 0xFC, 0x3F, 0xFE, 0x7F, 0xCF, 0x7B, 0xC7, 0x71, 0xC7, 0x71, 0xC7, 0x71, 0xC7, 0x71, 
    0xC7, 0x71, 0xC7, 0x7B, 0xC7, 0x7F, 0x83, 0x3F, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char '7'
    0x1F, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x07, 0x00, 0x07, 0x00, 0x87, 0x7F, 0xC7, 0x7F, 0xE7, 0x7F, 
    0xF7, 0x01, 0xFF, 0x00, 0x7F, 0x00, 0x3F, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char '8'
    0x1C, 0x1E, 0x3E, 0x3F, 0xFF, 0x7F, 0xEF, 0x79, 0xC7, 0x70, 0xC7, 0x70, 0xC7, 0x70, 0xC7, 0x70, 
    0xC7, 0x70, 0xEF, 0x79, 0xFF, 0x7F, 0x3E, 0x3F, 0x1C, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char '9'
    0x7C, 0x00, 0xFE, 0x60, 0xFF, 0x71, 0xEF, 0x71, 0xC7, 0x71, 0xC7, 0x71, 0xC7, 0x71, 0xC7, 0x79, 
    0xC7, 0x3D, 0xEF, 0x1F, 0xFF, 0x0F, 0xFE, 0x07, 0xFC, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

u8 code hugeUpperLetters[] =
{
    // char 'A'
    0xF0, 0x7F, 0xF8, 0x7F, 0xFC, 0x7F, 0x9E, 0x03, 0x8F, 0x03, 0x87, 0x03, 0x87, 0x03, 0x87, 0x03, 
    0x8F, 0x03, 0x9F, 0x03, 0xFE, 0x7F, 0xFC, 0x7F, 0xF8, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'B'
    0x03, 0x70, 0x03, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xC7, 0x70, 0xC7, 0x70, 0xC7, 0x70, 
    0xC7, 0x70, 0xC7, 0x70, 0xEF, 0x79, 0xFF, 0x7F, 0x3E, 0x3F, 0x1C, 0x1E, 0x00, 0x00, 0x00, 0x00, 
    // char 'C'
    0xF0, 0x07, 0xF8, 0x0F, 0xFC, 0x1F, 0x1E, 0x3C, 0x0F, 0x78, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 
    0x07, 0x70, 0x07, 0x70, 0x0F, 0x78, 0x1F, 0x7C, 0x1E, 0x3C, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 
    // char 'D'
    0x07, 0x70, 0x07, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 
    0x0F, 0x78, 0x1F, 0x7C, 0x3E, 0x3E, 0xFC, 0x1F, 0xF8, 0x0F, 0xE0, 0x03, 0x00, 0x00, 0x00, 0x00, 
    // char 'E'
    0x07, 0x70, 0x07, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xC7, 0x70, 0xC7, 0x70, 0xC7, 0x70, 
    0xE7, 0x71, 0xE7, 0x71, 0x07, 0x70, 0x07, 0x70, 0x0F, 0x78, 0x0F, 0x78, 0x00, 0x00, 0x00, 0x00, 
    // char 'F'
    0x07, 0x70, 0x07, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xC7, 0x70, 0xC7, 0x70, 0xC7, 0x70, 
    0xE7, 0x01, 0xE7, 0x01, 0x07, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'G'
    0xF0, 0x07, 0xF8, 0x0F, 0xFC, 0x1F, 0x1E, 0x3C, 0x0F, 0x78, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 
    0x07, 0x70, 0x87, 0x71, 0x87, 0x71, 0x8F, 0x7F, 0x8E, 0x7F, 0x0C, 0x7F, 0x00, 0x00, 0x00, 0x00, 
    // char 'H'
    0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xE0, 0x00, 0xE0, 0x00, 0xE0, 0x00, 0xE0, 0x00, 0xE0, 0x00, 
    0xE0, 0x00, 0xE0, 0x00, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'I'
    0x00, 0x00, 0x00, 0x00, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 
    0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'J'
    0x00, 0x0E, 0x00, 0x1E, 0x00, 0x3E, 0x00, 0x78, 0x00, 0x70, 0x00, 0x70, 0x07, 0x70, 0x07, 0x78, 
    0xFF, 0x7F, 0xFF, 0x3F, 0xFF, 0x1F, 0xFF, 0x0F, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'K'
    0x07, 0x70, 0x07, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xC0, 0x01, 0xE0, 0x03, 
    0xF0, 0x07, 0x78, 0x0F, 0x3C, 0x1E, 0x1F, 0x7C, 0x0F, 0x78, 0x07, 0x70, 0x00, 0x00, 0x00, 0x00, 
    // char 'L'
    0x07, 0x70, 0x07, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 
    0x00, 0x70, 0x00, 0x70, 0x00, 0x7C, 0x00, 0x7C, 0x00, 0x7C, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 
    // char 'M'
    0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x3C, 0x00, 0x78, 0x00, 0xF0, 0x00, 0xE0, 0x01, 0xE0, 0x01, 
    0xF0, 0x00, 0x78, 0x00, 0x3C, 0x00, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 
    // char 'N'
    0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x1E, 0x00, 0x3C, 0x00, 0x78, 0x00, 0xF0, 0x00, 0xE0, 0x01, 
    0xC0, 0x03, 0x80, 0x07, 0x00, 0x0F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 
    // char 'O'
    0xF0, 0x07, 0xF8, 0x0F, 0xFC, 0x1F, 0x1E, 0x3C, 0x0F, 0x78, 0x07, 0x70, 0x07, 0x70, 0x07, 0x70, 
    0x07, 0x70, 0x0F, 0x78, 0x1E, 0x3C, 0xFC, 0x1F, 0xF8, 0x0F, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 
    // char 'P'
    0x03, 0x70, 0x03, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xC7, 0x71, 0xC7, 0x71, 0xC7, 0x71, 
    0xC7, 0x01, 0xC7, 0x01, 0xEF, 0x01, 0xFF, 0x00, 0x7E, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'Q'
    0xFC, 0x0F, 0xFE, 0x1F, 0xFF, 0x3F, 0x0F, 0x78, 0x07, 0x70, 0x87, 0x71, 0x87, 0x73, 0x87, 0x77, 
    0x0F, 0x7F, 0xFF, 0x3F, 0xFE, 0x3F, 0xFC, 0x7F, 0x00, 0x78, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 
    // char 'R'
    0x07, 0x70, 0x07, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xC7, 0x70, 0xC7, 0x70, 0xC7, 0x01, 
    0xC7, 0x03, 0xC7, 0x07, 0xEF, 0x0F, 0xFF, 0x7E, 0x7E, 0x7C, 0x3C, 0x78, 0x00, 0x00, 0x00, 0x00, 
    // char 'S'
    0x3C, 0x18, 0x7E, 0x38, 0xFF, 0x78, 0xE7, 0x71, 0xC7, 0x71, 0xC7, 0x71, 0xC7, 0x71, 0xC7, 0x73, 
    0xC7, 0x7F, 0x8F, 0x7F, 0x0E, 0x3F, 0x0C, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'T'
    0x1F, 0x00, 0x1F, 0x00, 0x0F, 0x70, 0x07, 0x70, 0x07, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 
    0x07, 0x70, 0x07, 0x70, 0x0F, 0x70, 0x1F, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'U'
    0xFF, 0x1F, 0xFF, 0x3F, 0xFF, 0x7F, 0x00, 0x78, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 
    0x00, 0x70, 0x00, 0x78, 0xFF, 0x7F, 0xFF, 0x3F, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'V'
    0xFF, 0x01, 0xFF, 0x03, 0xFF, 0x07, 0x00, 0x0F, 0x00, 0x1E, 0x00, 0x3C, 0x00, 0x78, 0x00, 0x3C, 
    0x00, 0x1E, 0x00, 0x0F, 0xFF, 0x07, 0xFF, 0x03, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'W'
    0xFF, 0x3F, 0xFF, 0x3F, 0xFF, 0x3F, 0x00, 0x1E, 0x00, 0x0F, 0x80, 0x07, 0xC0, 0x03, 0xC0, 0x03, 
    0x80, 0x07, 0x00, 0x0F, 0x00, 0x1E, 0xFF, 0x3F, 0xFF, 0x3F, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 
    // char 'X'
    0x07, 0x70, 0x0F, 0x78, 0x1F, 0x7C, 0x3E, 0x3E, 0x7C, 0x1F, 0xF8, 0x0F, 0xF0, 0x07, 0xF0, 0x07, 
    0xF8, 0x0F, 0x7C, 0x1F, 0x3E, 0x3E, 0x1F, 0x7C, 0x0F, 0x78, 0x07, 0x70, 0x00, 0x00, 0x00, 0x00, 
    // char 'Y'
    0x0F, 0x00, 0x1F, 0x00, 0x3F, 0x00, 0x7C, 0x70, 0xF8, 0x70, 0xF0, 0x7F, 0xE0, 0x7F, 0xF0, 0x7F, 
    0xF8, 0x70, 0x7C, 0x70, 0x3F, 0x00, 0x1F, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'Z'
    0x0F, 0x70, 0x0F, 0x78, 0x0F, 0x7C, 0x03, 0x7E, 0x03, 0x7F, 0x83, 0x77, 0xC3, 0x73, 0xE3, 0x71, 
    0xF3, 0x70, 0x7B, 0x70, 0x3F, 0x7C, 0x1F, 0x7C, 0x0F, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

u8 code hugeLowerLetters[] =
{
    // char 'a'
    0x00, 0x1C, 0x00, 0x3E, 0x30, 0x7F, 0x30, 0x77, 0x30, 0x63, 0x30, 0x63, 0x30, 0x63, 0x70, 0x63, 
    0xF0, 0x77, 0xE0, 0x7F, 0xC0, 0x7F, 0x00, 0x70, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'b'
    0x07, 0x70, 0x07, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x3F, 0xE0, 0x39, 0xE0, 0x70, 0xE0, 0x70, 
    0xE0, 0x70, 0xE0, 0x79, 0xE0, 0x7F, 0xC0, 0x7F, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'c'
    0xC0, 0x0F, 0xE0, 0x1F, 0xF0, 0x3F, 0xF0, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 
    0x70, 0x70, 0xF0, 0x78, 0xE0, 0x38, 0xC0, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'd'
    0x00, 0x1F, 0x80, 0x3F, 0xC0, 0x7F, 0xE0, 0x79, 0xE0, 0x70, 0xE0, 0x70, 0xE0, 0x70, 0xE0, 0x79, 
    0xE0, 0x3F, 0xFF, 0x1F, 0xFF, 0x7F, 0xFF, 0x7F, 0x00, 0x70, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 
    // char 'e'
    0xC0, 0x1F, 0xE0, 0x3F, 0xF0, 0x7F, 0x70, 0x73, 0x30, 0x73, 0x30, 0x73, 0x30, 0x73, 0x30, 0x73, 
    0x30, 0x73, 0xF0, 0x73, 0xE0, 0x73, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'f'
    0xC0, 0x70, 0xC0, 0x70, 0xFC, 0x7F, 0xFE, 0x7F, 0xFF, 0x7F, 0xCF, 0x70, 0xC7, 0x70, 0xC7, 0x70, 
    0x07, 0x00, 0x0F, 0x00, 0x1E, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'g'
    0xC0, 0xC3, 0xE0, 0xC7, 0xF0, 0xCF, 0x70, 0xCE, 0x30, 0xCC, 0x30, 0xCC, 0x30, 0xCC, 0x30, 0xCC, 
    0x70, 0xCE, 0xF0, 0xFF, 0xF0, 0x7F, 0xF0, 0x3F, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'h'
    0x03, 0x70, 0x03, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xC0, 0x73, 0xE0, 0x71, 0xF0, 0x00, 
    0x70, 0x00, 0x70, 0x00, 0xF0, 0x00, 0xE0, 0x7F, 0xC0, 0x7F, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 
    // char 'i'
    0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x30, 0x70, 0x30, 0x70, 0xF3, 0x7F, 0xF3, 0x7F, 0xF3, 0x7F, 
    0x00, 0x70, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'j'
    0x00, 0x3C, 0x00, 0x7C, 0x00, 0xFC, 0x00, 0xE0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 
    0x00, 0xE0, 0xF3, 0xFF, 0xF3, 0x7F, 0xF3, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'k'
    0x07, 0x70, 0x07, 0x70, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x00, 0x03, 0x80, 0x07, 0xC0, 0x0F, 
    0xE0, 0x1F, 0xF0, 0x3C, 0x78, 0x78, 0x38, 0x70, 0x38, 0x70, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 
    // char 'l'
    0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0xFF, 0x1F, 0xFF, 0x3F, 0xFF, 0x7F, 0x07, 0x70, 0x00, 0x70, 
    0x00, 0x78, 0x00, 0x3C, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'm'
    0xC0, 0x7F, 0xE0, 0x7F, 0xF0, 0x7F, 0xF0, 0x01, 0xE0, 0x03, 0xC0, 0x07, 0x80, 0x07, 0x80, 0x07, 
    0xC0, 0x03, 0xE0, 0x01, 0xF0, 0x00, 0xF0, 0x7F, 0xE0, 0x7F, 0xC0, 0x7F, 0x00, 0x00, 0x00, 0x00, 
    // char 'n'
    0xF0, 0x7F, 0xF0, 0x7F, 0xF0, 0x7F, 0xE0, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 
    0xF0, 0x00, 0xF0, 0x7F, 0xE0, 0x7F, 0xC0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'o'
    0xC0, 0x1F, 0xE0, 0x3F, 0xF0, 0x7F, 0xF0, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 
    0xF0, 0x78, 0xF0, 0x7F, 0xE0, 0x3F, 0xC0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'p'
    0x38, 0xE0, 0x38, 0xE0, 0xF8, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0x38, 0xE6, 0x18, 0xE6, 0x18, 0xE6, 
    0x18, 0x06, 0x38, 0x07, 0xF8, 0x07, 0xF0, 0x03, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'q'
    0xC0, 0x01, 0xE0, 0x03, 0xF0, 0x07, 0x78, 0x07, 0x38, 0x06, 0x38, 0x06, 0x38, 0xE6, 0x38, 0xE6, 
    0x70, 0xE7, 0xF0, 0xFF, 0xF8, 0xFF, 0xF8, 0xFF, 0x38, 0xE0, 0x38, 0xE0, 0x00, 0x00, 0x00, 0x00, 
    // char 'r'
    0x70, 0x70, 0x70, 0x70, 0xF0, 0x7F, 0xF0, 0x7F, 0xC0, 0x7F, 0xE0, 0x73, 0xF0, 0x70, 0x70, 0x70, 
    0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0xF0, 0x01, 0xE0, 0x01, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 
    // char 's'
    0xC0, 0x00, 0xE0, 0x71, 0xF0, 0x73, 0xF8, 0x73, 0x38, 0x73, 0x38, 0x73, 0x38, 0x73, 0x38, 0x73, 
    0x38, 0x7F, 0x38, 0x7F, 0x38, 0x3E, 0x38, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 't'
    0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x78, 0x00, 0x7C, 0x00, 0xFE, 0x3F, 0xFF, 0x7F, 0xFF, 0x7F, 
    0x70, 0x70, 0x70, 0x78, 0x70, 0x7C, 0x70, 0x3C, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'u'
    0xF0, 0x0F, 0xF0, 0x1F, 0xF0, 0x7F, 0x00, 0x78, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 
    0x00, 0x78, 0xF0, 0x3F, 0xF0, 0x3F, 0xF0, 0x7F, 0x00, 0x78, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 
    // char 'v'
    0xF0, 0x03, 0xF0, 0x07, 0xF0, 0x0F, 0x00, 0x1E, 0x00, 0x3C, 0x00, 0x78, 0x00, 0x78, 0x00, 0x3C, 
    0x00, 0x1E, 0xF0, 0x0F, 0xF0, 0x07, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'w'
    0xF0, 0x0F, 0xF0, 0x1F, 0xF0, 0x3F, 0x00, 0x7C, 0x00, 0x7C, 0x00, 0x1E, 0xC0, 0x0F, 0xC0, 0x0F, 
    0x00, 0x1E, 0x00, 0x3C, 0x00, 0x7C, 0xF0, 0x7F, 0xF0, 0x1F, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x00, 
    // char 'x'
    0x38, 0x70, 0x78, 0x78, 0xF8, 0x78, 0xF0, 0x3D, 0xE0, 0x1F, 0xC0, 0x0F, 0x80, 0x07, 0x80, 0x07, 
    0xC0, 0x0F, 0xE0, 0x1F, 0xF0, 0x3D, 0xF8, 0x78, 0x78, 0x78, 0x38, 0x70, 0x00, 0x00, 0x00, 0x00, 
    // char 'y'
    0xF8, 0x03, 0xF8, 0xE7, 0xF8, 0xE7, 0x00, 0xE7, 0x00, 0xE6, 0x00, 0xE6, 0x00, 0xE6, 0x00, 0xE6, 
    0x00, 0xE7, 0xF8, 0xFF, 0xF8, 0x7F, 0xF8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // char 'z'
    0x78, 0x70, 0x78, 0x78, 0x78, 0x7C, 0x38, 0x7E, 0x38, 0x7F, 0xB8, 0x77, 0xF8, 0x73, 0xF8, 0x71, 
    0xF8, 0x70, 0x78, 0x78, 0x38, 0x78, 0x18, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

u8 code largeFontNumbers[] = 
{
    // char '0'
    0xFC, 0xFE, 0x07, 0x03, 0x07, 0xFE, 0xFC, 0x00, 0x07, 0x0F, 0x1C, 0x18, 0x1C, 0x0F, 0x07, 0x00, 
    // char '1'
    0x00, 0x06, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x1F, 0x1F, 0x18, 0x18, 0x00, 
    // char '2'
    0x86, 0xC7, 0xE3, 0x63, 0x73, 0x3F, 0x1E, 0x00, 0x1F, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 
    // char '3'
    0x03, 0x63, 0x63, 0x63, 0xF7, 0xFE, 0x9C, 0x00, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x0F, 0x07, 0x00, 
    // char '4'
    0xF0, 0xF8, 0x9C, 0x8E, 0xFF, 0xFF, 0x80, 0x00, 0x01, 0x01, 0x01, 0x01, 0x1F, 0x1F, 0x01, 0x00, 
    // char '5'
    0x3F, 0x3F, 0x33, 0x33, 0x73, 0xE3, 0xC3, 0x00, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x0F, 0x07, 0x00, 
    // char '6'
    0xFC, 0xFE, 0x67, 0x63, 0xE3, 0xC3, 0x80, 0x00, 0x07, 0x0F, 0x1C, 0x18, 0x1C, 0x0F, 0x07, 0x00, 
    // char '7'
    0x03, 0x03, 0x83, 0xC3, 0xE3, 0x7F, 0x3F, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 
    // char '8'
    0xBC, 0xFE, 0xE7, 0x43, 0xE7, 0xFE, 0xBC, 0x00, 0x07, 0x0F, 0x1C, 0x18, 0x1C, 0x0F, 0x07, 0x00, 
    // char '9'
    0x3C, 0x7E, 0xE7, 0xC3, 0xC7, 0xFE, 0xFC, 0x00, 0x00, 0x18, 0x18, 0x18, 0x1C, 0x0F, 0x07, 0x00, 
};

void fontChipRead(const u8, const U32*, const u8, u8*);
//void fontDrawSymbol(const u8, const u8, const u8, const COLOR);
void fontCustomSymbol(const u8, const u8, const u8, const COLOR);
void fontChipDrawText(const char* text, const chipFont* font, u8 x, const u8 y, const COLOR col, const bit ds);
void fontDraw6x8 (char* text, const u8 x, const u8 y, const COLOR col);
void fontDraw8x8 (char* text, const u8 x, const u8 y, const COLOR col, const bit ds);
void fontDraw8x16 (char* text, const u8 x, const u8 y, const COLOR col);
const COLOR lowerColor(COLOR col);
