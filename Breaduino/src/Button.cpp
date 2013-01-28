#include "Arduino.h"
#include "Button.h"

CButton::CButton(uint8_t buttonPin, uint8_t buttonMode)
{
	this->pin=buttonPin;
	mode = buttonMode;
}

void CButton::begin()
{
	Module::begin();
    pinMode(pin,INPUT);

	mode==PULLDOWN ? pulldown() : pullup();
    state = 0;
    timing[CHANGED] = timing[PREVIOUS] = timing[CURRENT] = 0;
    bitWrite(state,CURRENT,!mode);
}

/*
|| Set pin HIGH as default
*/
void CButton::pullup(void){
	mode=PULLUP;
	digitalWrite(pin,HIGH);
}

/*
|| Set pin LOW as default
*/
void CButton::pulldown(void){
	digitalWrite(pin,LOW);
}

void CButton::run()
{
	bitWrite(state,PREVIOUS,bitRead(state,CURRENT));
	timing[PREVIOUS] = timing[CURRENT];
	bitWrite(state,CURRENT,(digitalRead(pin) != mode));
	timing[CURRENT] = millis();
	if (bitRead(state,CURRENT) != bitRead(state,PREVIOUS)){
		bitWrite(state,CHANGED,true);
		timing[CHANGED] = timing[CURRENT];
	}else{
		bitWrite(state,CHANGED,false);
	}
	if (bitRead(state,CURRENT)){
	} else if (bitRead(state,CHANGED)) {
	}
	delay(20);

}
/*
|| Return the bitWrite(state,CURRENT, of the switch
*/
bool CButton::isPressed(void){
    if (bitRead(state,CURRENT)){
        return true;
    } else {
        return false;
    }
}

/*
|| Return true if state has been changed
*/
bool CButton::stateChanged(void){
    return bitRead(state,CHANGED);
}

/*
|| Return true if the button is pressed, and was not pressed before
*/
bool CButton::isReleased(void){
    return (!isPressed() && stateChanged());
}

bool CButton::wasPressed(unsigned long time)
{
    if (bitRead(state,CURRENT)){
        return (timing[CURRENT] - timing[CHANGED]) >= time;
    } else {
        return false;
    }
}
