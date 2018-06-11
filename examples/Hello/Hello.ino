#include <Neo.h>
#include <Neo_font_minimal.h>

#define SPEED 20

Neo disp(0, 7, 0, 4);

byte frame[8];

char string1[] = "Hello World!!";
char string2[] = "i <3 Neo";

void setup() {
  delay(100);
  disp.init();
  disp.setBrightness(1);
  disp.clearDisplay();
}

void printChar(char c, uint8_t speed) {
  if (c < 32) return;
  c -= 32;
  memcpy_P(frame, CH + 8 * c, 8);
  
  // rotate frame 90 degrees
  byte temp[8];
  for (byte r = 0; r < 8; r++) {
    byte b = 0;
    for (byte i = 0; i < 8; i++)
      b |= bitRead(frame[i], r) << (7 - i);
    temp[r] = b;
  }

  disp.append(temp);

  for (uint8_t i = 0; i < 8; i++) {
    disp.shiftLeft();
    delay(speed);
  }
}

void printString(char* s, uint8_t speed) {
  while (*s != 0) {
    printChar(*s, speed);
    s++;
  }
}

void loop() {
  printString(string1, SPEED);
  printString(" ", SPEED);
  printString(string2, SPEED);
  printString(" ", SPEED);
}