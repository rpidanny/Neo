#include "Neo.h"

#include <SPI.h>

unsigned char disp1[38][8]={
  {0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0
  {0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},//1
  {0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},//2
  {0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},//3
  {0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},//4
  {0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},//5
  {0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},//6
  {0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},//7
  {0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8
  {0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},//9
  {0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
  {0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},//B
  {0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},//C
  {0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},//D
  {0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E 
  {0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
  {0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
  {0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
  {0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
  {0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},//J
  {0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
  {0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
  {0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
  {0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
  {0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
  {0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
  {0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
  {0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
  {0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
  {0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},//T
  {0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
  {0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
  {0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},//W
  {0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},//X
  {0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
  {0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F}//Z
}; 

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
}

void Neo::displayTest() {
  transferToAll(MAX7219_REG_DISPLAYTEST, 0x01);
    delay(10);
  transferToAll(MAX7219_REG_DISPLAYTEST, 0x00);  
}

void Neo::setBrightness(uint8_t value) {
  transferToAll(MAX7219_REG_INTENSITY, value);
}

void Neo::initDisplay() {
  
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

void Neo::demo() {
  for (int i = 0; i < 38; i++)
  {
    for(int j = 0; j < _display_count; j++) {
      printChar(i);
    }
    delay(200);
  }
}

void Neo::test() {
  // transferToAll(0, 0x01);
  // delay(100);
  // transferToAll(1, 0x02);
  // delay(100);
  // transferToAll(2, 0x04);
  // delay(100);
  // transferToAll(3, 0x08);
  fillDisplay();
  delay(100);
  clearDisplay();
  delay(100);
  transferToDisp(0, 1, 0x01);
  delay(100);
  transferToDisp(1, 2, 0x02);
  delay(100);
  transferToDisp(2, 3, 0x04);
  delay(100);
  transferToDisp(3, 4, 0x08);
}

void Neo::printChar(uint8_t ch) {
  for (int i=1; i<9; i++) {
    transfer(i, disp1[ch][i-1]);
  }
}

void Neo::clearDisplay() {
  for (uint8_t j = 1; j < 9; j++) {
    transferToAll(j, 0x00);
  }
}

void Neo::fillDisplay() {
  for (uint8_t j = 1; j < 9; j++) {
    transferToAll(j, 0xff);
  }
}