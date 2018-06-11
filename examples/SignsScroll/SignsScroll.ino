#include <Neo.h>
#include <Neo_signs.h>

#define SPEED 20

Neo disp(0, 7, 0, 4);

byte frame[8];
const uint8_t SIGNS_COUNT = sizeof(SIGN)/8;

void setup() {
  delay(100);
  disp.init();
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