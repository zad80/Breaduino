///
/// @file	Energy.h
/// @brief	Power saving based on idle time
/// @details	Energy switches backlight off when inactivity period is reach to save energy
/// @n
/// @n @a	Member of Serial_LCD Library Suite
/// @n @a	for 4D Systems uLCD-uLED-uVGA screens
/// @n @a	on Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
///
/// @a		Developed with [embedXcode](http://embedXcode.weebly.com)
/// @n
/// @author	Rei VILO
/// @author	http://embeddedcomputing.weebly.com
/// @date 	Sep 01, 2012
/// @version	release 307
/// @n
/// @copyright	© Rei VILO, 2010-2012
/// @copyright	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/serial-lcd.html
/// @n		http://github.com/rei-vilo/Serial_LCD
///
/// @see	4D Systems Goldelox and Picaso SGC Command Set
/// @n		http://www.4dsystems.com.au/
///
#define ENERGY_RELEASE 307
#ifndef Energy_h
#define Energy_h
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
#include "Serial_LCD.h"
#if SERIAL_LCD_RELEASE < 334
#error required SERIAL_LCD_RELEASE 334
#endif
class Energy {
public:
  Energy();
  void begin(Serial_LCD * lcd, uint32_t seconds=3);
  void check(boolean flag);
private:
  Serial_LCD * _pscreen;
  uint32_t _ms;
  uint32_t _chrono;
  boolean _state;
};
#endif
