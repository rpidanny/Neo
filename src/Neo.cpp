#include "Neo.h"

#include <SPI.h>


Neo::Neo(uint8_t din, uint8_t cs, uint8_t clk, uint8_t displayCount) {
  _din = din;
  _cs = cs;
  _clk = clk;
  _display_count = displayCount;

  // pinMode(_din, OUTPUT);
  pinMode(_cs, OUTPUT);
  // pinMode(_clk, OUTPUT);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();

  DP = 0;
  RP = 0;
  for (int i=0; i < 100; i++)
		buffer[i] = 0;
}

void Neo::displayTest() {
  transferToAll(MAX7219_REG_DISPLAYTEST, 0x01);
    delay(100);
  transferToAll(MAX7219_REG_DISPLAYTEST, 0x00);  
}

void Neo::setBrightness(uint8_t value) {
  if (value < 16)
    transferToAll(MAX7219_REG_INTENSITY, value);
  else
    transferToAll(MAX7219_REG_INTENSITY, 0x0f);
}

void Neo::init() {
  
  // Enable mode BCD
  transferToAll(MAX7219_REG_DECODEMODE, 0x00);
  
  // Use lowest intensity
  transferToAll(MAX7219_REG_INTENSITY, 0x00);
  
  // Only scanlimit: 8LED
  transferToAll(MAX7219_REG_SCANLIMIT, 0x07);
  
  // power-down mode:0, normal mode: 1
  transferToAll(MAX7219_REG_SHUTDOWN, 0x01);
}

void Neo::transfer(uint8_t address, uint8_t value) {
  // Ensure LOAD/CS is LOW
  digitalWrite(_cs, LOW);

  // Send the register address
  SPI.transfer(address);

  // Send the value
  SPI.transfer(value);

  // Tell chip to load in data
  digitalWrite(_cs, HIGH);
}

void Neo::transferToDisp(uint8_t disp, uint8_t address, uint8_t value) {
  digitalWrite(_cs, LOW);    
  for (uint8_t i =0; i < _display_count; i++) {
    if (disp == i) {
      SPI.transfer(address);
      SPI.transfer(value);
    } else {
      SPI.transfer(MAX7219_REG_NOOP);
      SPI.transfer(0x00);
    }
  }
  digitalWrite(_cs, HIGH); 
}

void Neo::transferToAll(uint8_t address, uint8_t value) {
  digitalWrite(_cs, LOW);    
  for (uint8_t i =0; i < _display_count; i++) {
    SPI.transfer(address);
    SPI.transfer(value);
  }
  digitalWrite(_cs, HIGH);    
}

void Neo::renderDisplay(uint8_t disp, unsigned char frame[8]) {
  for (uint8_t i = 1; i < 9; i++) {
    transferToDisp(disp, i, frame[i - 1]);
    // buffer[((_display_count - disp - 1) * 8) + i - 1] = frame[i - 1];
  }
}

void Neo::printChar(uint8_t disp, uint8_t ch) {
  for (int i=1; i<9; i++) {
    transferToDisp(disp, i, disp1[ch][i-1]);
  }
}

void Neo::clearDisplay() {
  for (uint8_t j = 1; j < 9; j++) {
    transferToAll(j, 0x00);
  }
  for (int i=0; i<80; i++)
		buffer[i] = 0;
}

void Neo::fillDisplay() {
  for (uint8_t j = 1; j < 9; j++) {
    transferToAll(j, 0xff);
  }
}

void Neo::shiftLeft() {
  for (uint8_t i = 0; i < 100; i++) {
    byte old = buffer[i];
    if ( i < 92)
      buffer[i] = (old << 1) | ( buffer[i + 8] >> 7);
    else
      buffer[i] = (old << 1) & 0xfe;
  }
  reload();
}

void Neo::reload() {
  for (uint8_t disp =0; disp < _display_count; disp++) {
    for (uint8_t r = 1; r < 9; r++) {
      // transferToDisp(disp, r, buffer[((_display_count - disp - 1) * 8) + r - 1]);
      transferToDisp(disp, r, buffer[(disp * 8) + r - 1]);
    }
  }
  if (RP == 7) {
    RP = 0;
    DP--;
  } else {
    RP++;
  }
}

void Neo::render(byte frame[8]) {
  for (uint8_t i = 0; i < 8; i++) {
    // buffer[((_display_count - DP - 1) * 8) + i] = frame[i];
    buffer[((_display_count - DP) * 8) + i] = frame[i];
  }
  DP++;
}