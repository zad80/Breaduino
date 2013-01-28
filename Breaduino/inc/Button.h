#ifndef BUTTON_H
#define BUTTON_H

#include "Module.h"

#define PULLUP HIGH
#define PULLDOWN LOW

#define CURRENT 0
#define PREVIOUS 1
#define CHANGED 2

class CButton
: public Module
{
  public:
    CButton(uint8_t buttonPin, uint8_t buttonMode=PULLDOWN);
	
	virtual void begin();

    void pullup();
    void pulldown();
    bool isPressed();
    bool stateChanged();
	bool isReleased();
	bool wasPressed(unsigned long time);
	virtual void run();
protected:
  private: 
    uint8_t pin;
    uint8_t mode;
    uint8_t state;
	unsigned long timing[3];
};

#endif
