#include <Neo.h>
#include <Neo_signs.h>

#define SPEED 100

Neo disp(4, 7);

byte frame[8];
const uint8_t SIGNS_COUNT = sizeof(SIGN)/8;

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
    disp.renderDisplay(0, frame);
    delay(SPEED);
  }
}