#include "Neo.h"

#include <SPI.h>

/**
 * @brief Instantiates a new Neo class.
 * @param displayCount Number of 8x8 Matrix Display to use.
 * @param cs The CS / LOAD pin number.
 * @param din The DIN pin number if SPI not used, else not required.
 * @param clk The CLK pin number if SPI not used, else not required.
 */
Neo::Neo(uint8_t displayCount, uint8_t cs, uint8_t din, uint8_t clk) {
  _din = din;
  _cs = cs;
  _clk = clk;
  _display_count = displayCount;
  _SPI = (_din | _clk) == 0; 
}

/**
 * @brief Turns on every pixel for 100ms
 */
void Neo::displayTest() {
  transferToAll(MAX7219_REG_DISPLAYTEST, 0x01);
  delay(100);
  transferToAll(MAX7219_REG_DISPLAYTEST, 0x00);  
}

/**
 * @brief Sets the display brightness.
 * @param value Brightness intensity from 0 - 15
 */
void Neo::setBrightness(uint8_t value) {
  if (value < 16)
    transferToAll(MAX7219_REG_INTENSITY, value);
  else
    transferToAll(MAX7219_REG_INTENSITY, 0x0f);
}

/**
 * @brief Setups the Pins, SPI and Display
 */
void Neo::begin() {
  pinMode(_din, OUTPUT);
  pinMode(_cs, OUTPUT);
  pinMode(_clk, OUTPUT);
  
  if ( _SPI ) {
    SPI.setBitOrder(MSBFIRST);
    SPI.begin();
  }

  DP = 0;
  RP = 0;

  // initialize buffer to 0x00
  for (uint8_t i = 0; i < 8 * (_display_count + 1); i++)
		buffer[i] = 0;
  
  // Enable mode BCD
  transferToAll(MAX7219_REG_DECODEMODE, 0x00);
  
  // Use lowest intensity
  transferToAll(MAX7219_REG_INTENSITY, 0x00);
  
  // Only scanlimit: 8LED
  transferToAll(MAX7219_REG_SCANLIMIT, 0x07);
  
  // power-down mode:0, normal mode: 1
  transferToAll(MAX7219_REG_SHUTDOWN, 0x01);
}

void Neo::spiTransfer(uint8_t address, uint8_t value) {
  if ( _SPI ) {
    // Send the register address
    SPI.transfer(address);
    
    // Send the value
    SPI.transfer(value);
  } else {
    // Send the register address
    shiftOut(_din, _clk, MSBFIRST, address);
    
    // Send the value
    shiftOut(_din, _clk, MSBFIRST, value);
  }
}

void Neo::transfer(uint8_t address, uint8_t value) {
  // Ensure LOAD/CS is LOW
  digitalWrite(_cs, LOW);
  spiTransfer(address, value);
  // Tell chip to load in data
  digitalWrite(_cs, HIGH);
}

void Neo::transferToDisp(uint8_t disp, uint8_t address, uint8_t value) {
  digitalWrite(_cs, LOW);    
  for (uint8_t i =0; i < _display_count; i++) {
    if (disp == i) {
      spiTransfer(address, value);
    } else {
      spiTransfer(MAX7219_REG_NOOP, 0x00);
    }
  }
  digitalWrite(_cs, HIGH); 
}

void Neo::transferToAll(uint8_t address, uint8_t value) {
  digitalWrite(_cs, LOW);    
  for (uint8_t i =0; i < _display_count; i++) {
    spiTransfer(address, value);
  }
  digitalWrite(_cs, HIGH);    
}

void Neo::clearDisplay() {
  for (uint8_t j = 1; j < 9; j++) {
    transferToAll(j, 0x00);
  }
  for (uint8_t i = 0; i < 8 * (_display_count + 1); i++)
		buffer[i] = 0;
}

void Neo::fillDisplay() {
  for (uint8_t j = 1; j < 9; j++) {
    transferToAll(j, 0xff);
  }
}

/**
 * @brief Append a character frame to the internal display buffer.
 * @param frame byte array of length 8.
 */ 
void Neo::append(byte frame[8]) {
  for (uint8_t i = 0; i < 8; i++) {
    // buffer[((_display_count - DP - 1) * 8) + i] = frame[i];
    buffer[((_display_count - DP) * 8) + i] = frame[i];
  }
  DP++;
}

/**
 * @brief Renders a character frame to a particular display position.
 * @param disp The position of the display to render the frame.
 * @param frame byte array of length 8.
 */
void Neo::renderDisplay(uint8_t disp, byte frame[8]) {
  for (uint8_t i = 1; i < 9; i++) {
    transferToDisp(disp, i, frame[i - 1]);
    // buffer[((_display_count - disp - 1) * 8) + i - 1] = frame[i - 1];
  }
}

/**
 * @brief Shifts the entire display buffer left by 1bit and re-renders the display.
 */
void Neo::shiftLeft() {
  for (uint8_t i = 0; i < 8 * (_display_count + 1); i++) {
    byte old = buffer[i];
    if ( i < (8 * (_display_count + 1) - 8) )
      buffer[i] = (old << 1) | ( buffer[i + 8] >> 7);
    else
      buffer[i] = (old << 1) & 0xfe;
  }
  render();
}

/**
 * @brief Renders the content of the display buffer to the display.
 */
void Neo::render() {
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