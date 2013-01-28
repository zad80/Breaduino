///
/// @file 	Serial_LCD.h
/// @brief	Core library
/// @details 	Serial_LCD provides the core functions to display text and graphic, track touch, read and write on SD-card, play sound
/// @n
/// @n @a 	Member of Serial_LCD Library Suite
/// @n @a	for 4D Systems uLCD-uLED-uVGA Serial_LCD Library Suite
/// @n 		on Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
///
/// @a 		Developed with [embedXcode](http://embedXcode.weebly.com)
///
/// @author	Rei VILO, http://embeddedcomputing.weebly.com
/// @date 	Dec 11, 2012
/// @version	release 337
/// @n
/// @copyright 	© Rei VILO, 2010-2012
/// @copyright 	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/serial-lcd.html
/// @n		http://github.com/rei-vilo/Serial_LCD
///
/// @see 	4D Systems Goldelox and Picaso SGC Command Set
/// @n		http://www.4dsystems.com.au/
///
///
#define SERIAL_LCD_RELEASE 337
#ifndef Serial_LCD_h
#define Serial_LCD_h
#if defined(WIRING)
#include "Wiring.h"
#elif defined(MAPLE_IDE)
#include "WProgram.h"
#elif defined(MPIDE)
#include "WProgram.h"
#elif defined(ENERGIA)
#include "Energia.h"
#elif defined(ARDUINO) && (ARDUINO >= 100)
#include "Arduino.h"
#elif defined(ARDUINO) && (ARDUINO < 100)
#include "WProgram.h"
#else
#error Board not supported.
#endif
#include "proxySerial.h"
#if PROXYSERIAL_RELEASE < 312
#error required PROXYSERIAL_RELEASE 312
#endif
const uint8_t __uOLED__ = 0;
const uint8_t __uLCD__  = 1;
const uint8_t __uVGA__  = 2;
const uint8_t __Goldelox__ = 0;
const uint8_t __Picaso__   = 1;
const uint16_t blackColour   = 0b0000000000000000;
const uint16_t whiteColour   = 0b1111111111111111;
const uint16_t redColour     = 0b1111100000000000;
const uint16_t greenColour   = 0b0000011111100000;
const uint16_t blueColour    = 0b0000000000011111;
const uint16_t yellowColour  = 0b1111111111100000;
const uint16_t cyanColour    = 0b0000011111111111;
const uint16_t orangeColour  = 0b1111101111100000;
const uint16_t magentaColour = 0b1111100000001111;
const uint16_t violetColour  = 0b1111100000011111;
const uint16_t grayColour    = 0b0111101111101111;
class Serial_LCD {
public:
  Serial_LCD(ProxySerial * proxyPort);
  void begin(int8_t resetPin=-1);
  uint8_t setSpeed(uint32_t speed);
  String WhoAmI();
  uint8_t replaceBackGroundColour(uint16_t colour);
  uint8_t clear();
  uint8_t setBacklight(boolean flag);
  uint8_t setDisplay(boolean flag);
  uint8_t setContrast(uint8_t contrast);
  uint8_t setOrientation(uint8_t orientation);
  uint8_t getOrientation();
  uint8_t setResolutionVGA(uint8_t resolution);
  uint8_t setVolume(uint8_t percent);
  uint8_t protectFAT(boolean flag);
  uint8_t checkScreenType();
  uint8_t checkControllerType();
  uint8_t checkHardwareVersion();
  uint8_t checkSoftwareVersion();
  void off();
  uint8_t fontX();
  uint8_t fontY();
  uint16_t maxX();
  uint16_t maxY();
  uint8_t nacAck();
  uint8_t circle(uint16_t x1, uint16_t y1, uint16_t radius, uint16_t colour);
  uint8_t triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t colour);
  uint8_t setBackGroundColour(uint16_t colour=blackColour);
  uint8_t dLine(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t colour);
  uint8_t line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);
  uint8_t rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);
  uint8_t dRectangle(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t colour);
  uint8_t ellipse(uint16_t x, uint16_t y, uint16_t rx, uint16_t ry, uint16_t colour);
  uint8_t point(uint16_t x1, uint16_t y1, uint16_t colour);
  uint16_t readPixel(uint16_t x1, uint16_t y1);
  uint8_t copyPaste(uint16_t xs, uint16_t ys, uint16_t xt, uint16_t yt, uint16_t dx, uint16_t dy);
  uint8_t setPenSolid(boolean flag=true);
  uint8_t setFont(uint8_t size=0);
  uint8_t setFontSolid(boolean flag=true);
  uint8_t tText(uint8_t x, uint8_t y, String s, uint16_t colour=whiteColour);
  uint8_t gText(uint16_t x, uint16_t y, String s, uint16_t colour=whiteColour, uint8_t ix=1, uint8_t iy=1);
  uint8_t setTouch(boolean flag=true);
  uint8_t getTouchActivity();
  uint8_t getTouchXY(uint16_t &x, uint16_t &y);
  uint8_t dDetectTouchRegion(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy);
  uint8_t detectTouchRegion(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
  uint8_t saveScreenRAW(uint32_t sector);
  uint8_t dSaveScreenRAW(uint32_t sector, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy);
  uint8_t saveScreenRAW(uint32_t sector, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
  uint8_t readScreenRAW(uint32_t sector, uint16_t x1=0, uint16_t y1=0);
  uint32_t getSectors(uint16_t dx, uint16_t dy, uint16_t sizeSector=512);
  uint8_t initSD();
  boolean checkSD();
  boolean checkRAW();
  boolean checkFAT();
  uint8_t openTextFileDelimiter(String filename, char delimiter);
  boolean nextTextFileDelimiter(String * result);
  uint8_t readTextFileDelimiter(String filename, char delimiter, void (*cbReadFile)(String text));
  uint8_t readTextFile(String filename, uint8_t bytes, void (*cbReadFile)(String text));
  uint8_t writeStringFile(String filename, String text, uint8_t option=0x00);
  uint8_t appendStringFile(String filename, String text);
  uint8_t eraseFile(String filename);
  uint8_t findFile(String filename);
  uint8_t saveScreenFAT(String filename);
  uint8_t dSaveScreenFAT(String filename, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy);
  uint8_t saveScreenFAT(String filename, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
  uint8_t readScreenFAT(String filename, uint16_t x1=0, uint16_t y1=0);
  uint8_t readScreenGCI(String filename, uint16_t x1=0, uint16_t y1=0, uint16_t msb2=0, uint16_t lsb2=0);
  uint8_t playSoundSD(String filename, uint8_t option0=0);
  uint16_t setColour(uint8_t red, uint8_t green, uint8_t blue);
  void splitColour(uint16_t rgb, uint8_t &red, uint8_t &green, uint8_t &blue);
  uint16_t halfColour(uint16_t rgb);
  uint16_t reverseColour(uint16_t rgb);
private:
  ProxySerial * _port;
  int8_t _resetPin;
  uint8_t _checkedScreenType;
  uint8_t _checkedControllerType;
  uint8_t _checkedHardwareVersion;
  uint8_t _checkedSoftwareVersion;
  boolean _checkedSD;
  boolean _checkedRAW;
  boolean _checkedFAT;
  uint8_t _font, _fontX, _fontY;
  uint8_t _touch_buffer[4];
  uint8_t _orientation;
  uint16_t _maxX, _maxY;
  uint32_t _fileSize;
  uint8_t _delimeter;
  boolean _XY16;
  void _print16(uint16_t ui);
  void _printXY(uint16_t x, uint16_t y);
  void _swap(uint16_t &a, uint16_t &b);
};
#endif
