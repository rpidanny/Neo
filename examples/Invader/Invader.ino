#include <Neo.h>

#include <avr/pgmspace.h>

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define SPEED 100

PROGMEM const byte INVADER[] = {
  B00011000,  B00111100,  B01111110,  B11011011,  B11111111,  B00100100,  B01011010,  B10100101,
  B00011000,  B00111100,  B01111110,  B11011011,  B11111111,  B00100100,  B01011010,  B01000010
};

Neo disp(0, 7, 0, 4);

byte frame[8];

void setup() {
  delay(100);
  disp.begin();
  disp.setBrightness(0);
  disp.clearDisplay();
}

void demoInvader() {
  for (int i = 0; i < 2 ; i++)
  {
    memcpy_P(frame, INVADER + 8 * i, 8);
    disp.renderDisplay(0, frame);
    delay(SPEED);
  }
}

void loop() {
  demoInvader();
}