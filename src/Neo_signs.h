#if (defined(__AVR__))
  #include <avr/pgmspace.h>
  #include <WProgram.h>
#else
  #include <pgmspace.h>
#endif

PROGMEM const byte SIGN[] = {
  B00000000,
  B00000000,
  B00001000,
  B00001000,
  B00111110,
  B00001000,
  B00001000,
  B00000000
,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B00000000,
  B00000000,
  B00000000
,
  B00000000,
  B00000000,
  B00110110,
  B00011100,
  B01111111,
  B00011100,
  B00110110,
  B00000000
,
  B00000000,
  B00000000,
  B00000110,
  B00001100,
  B00011000,
  B00110000,
  B01100000,
  B00000000
,
  B00000000,
  B01100000,
  B01100110,
  B00001100,
  B00011000,
  B00110000,
  B01100110,
  B00000110
,
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B00000000,
  B00111100,
  B00000000,
  B00000000
,
  B00000000,
  B00000000,
  B00000000,
  B00111010,
  B01101100,
  B00000000,
  B00000000,
  B00000000
,
  B00000000,
  B00001000,
  B00010100,
  B00100010,
  B01000001,
  B00000000,
  B00000000,
  B00000000
,
  B00000000,
  B00000110,
  B00001100,
  B00011000,
  B00110000,
  B00011000,
  B00001100,
  B00000110
,
  B00000000,
  B01100000,
  B00110000,
  B00011000,
  B00001100,
  B00011000,
  B00110000,
  B01100000
,
  B00000000,
  B00000110,
  B00001100,
  B00011000,
  B00011000,
  B00011000,
  B00001100,
  B00000110
,
  B00000000,
  B01100000,
  B00110000,
  B00011000,
  B00011000,
  B00011000,
  B00110000,
  B01100000
,
  B00000000,
  B00011110,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011110
,
  B00000000,
  B01111000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B01111000
,
  B00000000,
  B00001110,
  B00011000,
  B00011000,
  B00110000,
  B00011000,
  B00011000,
  B00001110
,
  B00000000,
  B01110000,
  B00011000,
  B00011000,
  B00001100,
  B00011000,
  B00011000,
  B01110000
,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01100000,
  B01100000
,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00011000,
  B00011000,
  B00000000
,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00011000,
  B00011000,
  B00110000
,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00110000,
  B00110000,
  B00110000,
  B01100000
,
  B00000000,
  B00011000,
  B00111100,
  B00111100,
  B00011000,
  B00011000,
  B00000000,
  B00011000
,
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00011100,
  B00011000,
  B00000000,
  B00011000
,
  B00000000,
  B00111000,
  B01000100,
  B01011100,
  B01011000,
  B01000010,
  B00111100,
  B00000000
,
  B00000000,
  B00111100,
  B01100110,
  B00111100,
  B00101000,
  B01100101,
  B01100110,
  B00111111
,
  B00000000,
  B00001000,
  B00011110,
  B00100000,
  B00011100,
  B00000010,
  B00111100,
  B00001000
,
  B00000000,
  B00110110,
  B00110110,
  B01111111,
  B00110110,
  B01111111,
  B00110110,
  B00110110
,
  B00000000,
  B00001000,
  B00011100,
  B00111110,
  B01111111,
  B00011100,
  B00011100,
  B00011100
,
  B00000000,
  B00011100,
  B00011100,
  B00011100,
  B01111111,
  B00111110,
  B00011100,
  B00001000
,
  B00000000,
  B00001000,
  B00001100,
  B01111110,
  B01111111,
  B01111110,
  B00001100,
  B00001000
,
  B00000000,
  B00001000,
  B00011000,
  B00111111,
  B01111111,
  B00111111,
  B00011000,
  B00001000
,
  B00000000,
  B00001000,
  B00011100,
  B00011100,
  B00111110,
  B00111110,
  B01111111,
  B01111111
,
  B00000000,
  B01111111,
  B01111111,
  B00111110,
  B00111110,
  B00011100,
  B00011100,
  B00001000
,
  B00000000,
  B01100000,
  B01111000,
  B01111110,
  B01111111,
  B01111110,
  B01111000,
  B01100000
,
  B00000000,
  B00000011,
  B00001111,
  B00111111,
  B01111111,
  B00111111,
  B00001111,
  B00000011
,
  B00000000,
  B00111110,
  B01000001,
  B01010101,
  B01000001,
  B01010101,
  B01001001,
  B00111110
,
  B00000000,
  B00111110,
  B01111111,
  B01101011,
  B01111111,
  B01101011,
  B01110111,
  B00111110
,
  B00000000,
  B00100010,
  B01110111,
  B01111111,
  B01111111,
  B00111110,
  B00011100,
  B00001000
,
  B00000000,
  B00001000,
  B00011100,
  B00111110,
  B01111111,
  B00111110,
  B00011100,
  B00001000
,
  B00000000,
  B00001000,
  B00011100,
  B00101010,
  B01111111,
  B00101010,
  B00001000,
  B00011100
,
  B00000000,
  B00001000,
  B00011100,
  B00111110,
  B01111111,
  B00111110,
  B00001000,
  B00011100
,
  B00000000,
  B00000000,
  B00011100,
  B00111110,
  B00111110,
  B00111110,
  B00011100,
  B00000000
,
  B11111111,
  B11111111,
  B11100011,
  B11000001,
  B11000001,
  B11000001,
  B11100011,
  B11111111
,
  B00000000,
  B00000000,
  B00011100,
  B00100010,
  B00100010,
  B00100010,
  B00011100,
  B00000000
,
  B11111111,
  B11111111,
  B11100011,
  B11011101,
  B11011101,
  B11011101,
  B11100011,
  B11111111
,
  B00000000,
  B00001111,
  B00000011,
  B00000101,
  B00111001,
  B01001000,
  B01001000,
  B00110000
,
  B00000000,
  B00001000,
  B00111110,
  B00001000,
  B00011100,
  B00100010,
  B00100010,
  B00011100
,
  B00000000,
  B00011000,
  B00010100,
  B00010000,
  B00010000,
  B00110000,
  B01110000,
  B01100000
,
  B00000000,
  B00001111,
  B00011001,
  B00010001,
  B00010011,
  B00110111,
  B01110110,
  B01100000
,
  B00000000,
  B00001000,
  B00101010,
  B00011100,
  B01110111,
  B00011100,
  B00101010,
  B00001000
,
  B00000000,
  B00001000,
  B00011100,
  B00101010,
  B00001000,
  B00101010,
  B00011100,
  B00001000
,
  B00000000,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B00000000,
  B01100110,
  B01100110
,
  B00000000,
  B00000000,
  B00010100,
  B00100010,
  B01111111,
  B00100010,
  B00010100,
  B00000000
,
  B00000000,
  B00110110,
  B00110110,
  B00010100,
  B00000000,
  B00000000,
  B00000000,
  B00000000
,
  B00000000,
  B00000000,
  B01100000,
  B00110000,
  B00011000,
  B00001100,
  B00000110,
  B00000000
,
  B00000000,
  B00001100,
  B00001100,
  B00000110,
  B00000000,
  B00000000,
  B00000000,
  B00000000
,
  B00000000,
  B00011000,
  B00011000,
  B00011000,
  B00110000,
  B00000000,
  B00000000,
  B00000000
,
  B00000000,
  B00001000,
  B00011100,
  B00110110,
  B01100011,
  B01000001,
  B01000001,
  B01111111
};  //  end of MAX7219_Dot_Matrix_font