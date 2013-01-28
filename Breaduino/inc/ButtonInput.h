#ifndef __BUTTON_INPUT
#define __BUTTON_INPUT
#include "Module.h"

class ButtonInput: public Module{
private:

	uint8_t state;
	Module** buttons;
protected:
public:
	ButtonInput(Module** button);
	virtual void begin();
	virtual void run();

};


#endif
