#ifndef NEO_H
#define NEO_H

#include <avr/pgmspace.h>

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <SPI.h>

#define MAX7219_REG_NOOP        0x00
// codes 1 to 8 are digit positions 1 to 8
#define MAX7219_REG_DECODEMODE  0x09
#define MAX7219_REG_INTENSITY   0x0A
#define MAX7219_REG_SCANLIMIT   0x0B
#define MAX7219_REG_SHUTDOWN    0x0C
#define MAX7219_REG_DISPLAYTEST 0x0F

class Neo {
  public:
    Neo(uint8_t din, uint8_t cs, uint8_t clk, uint8_t displayCount);
        
    void init();
    void setBrightness(uint8_t value);
    void displayTest();
    void append(byte frame[8]);
    void renderDisplay(uint8_t disp, byte frame[8]);
    void clearDisplay();
    void fillDisplay();
    void shiftLeft();
    void render();

  private:
    void transfer(uint8_t address, uint8_t value);
    void transferToAll(uint8_t address, uint8_t value);
    void transferToDisp(uint8_t disp, uint8_t address, uint8_t value);
  
    uint8_t _display_count;
    uint8_t _din;
    uint8_t _cs;
    uint8_t _clk;
    uint8_t DP;
    uint8_t RP;
    byte buffer[];
};

#endif