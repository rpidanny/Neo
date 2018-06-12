#include <Neo.h>
#include <Neo_signs.h>

#define SPEED 20

// Ignore DIN, CLK if using internal SPI
Neo disp(4, 7); // Chips / LOAD(CS) / DIN / CLK

byte frame[8];

void setup() {
  delay(100);
  disp.begin();
  disp.setBrightness(0);
  disp.clearDisplay();
}

void loop() {
  for (int i = 0; i < 57 ; i++)
  {
    memcpy_P(frame, SIGN + 8 * i, 8);
    disp.append(frame);
    for (uint8_t i = 0; i < 8; i++) {
      disp.shiftLeft();
      delay(SPEED);
    }
  }
}