///
/// @file 	Gallery.h
/// @brief	Gallery of pictures
/// @details	4D Systems uLCD-uLED-uVGA Serial_LCD Library Suite
/// @n @a	for Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
///
/// @a 		Developed with [embedXcode](http://embedXcode.weebly.com)
///
/// @author	Rei VILO
/// @author	http://embeddedcomputing.weebly.com
/// @date	Nov 29, 2012
/// @version 	release 311
/// @n
/// @copyright	© Rei VILO, 2010-2012
/// @copyright	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/serial-lcd.html
/// @n		http://github.com/rei-vilo/Serial_LCD
///
/// @see	4D Systems Goldelox and Picaso SGC Command Set
/// @n		http://www.4dsystems.com.au/
///
#define GALLERY_RELEASE 311

#ifndef Gallery_h
#define Gallery_h

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
#define MAXPICTURE 64
#if SERIAL_LCD_RELEASE < 336
#error required SERIAL_LCD_RELEASE 336
#endif
class Gallery {
public:
    Gallery();
    ~Gallery();
    uint8_t begin(Serial_LCD * lcd, String name);
    uint8_t number();
    uint8_t index();
    uint8_t showNext();
    uint8_t showPrevious();
    uint8_t showImage(uint8_t index=0);
private:
    struct image_t {
        uint16_t msb, lsb, x, y;
    };
    Serial_LCD * _pscreen;
    String _name;
    uint8_t _index;
    image_t _gallery[MAXPICTURE];
    uint16_t _size;
};
#endif
