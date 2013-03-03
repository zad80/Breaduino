#include "Arduino.h"
#include "Button.h"

/* ############## Change log
 *
 * 3/03/2013
 * Button class is now completed:
 * It sores number of short and long pressures in a sequence.
 * In case a sequence is started pressures are counted till "timeOut4SequenceMilli" of no
 * pressure.
 * When a sequence is available it lasts for "expireSequenceMilli" long.
 * When a sequence is available successive pressure aren't counted
 * If a sequence is on going keeping the button pressed for "resetSequenceMilli"
 * resets counters and clear the sequence
 */
CButton::CButton(uint8_t buttonPin, uint8_t buttonMode)
{
	this->pin=buttonPin;
	mode = buttonMode;
	shortPushMilli=60;
	longPushMilli=1000;
	expireSequenceMilli=5000;
    timeOut4SequenceMilli=3000;
    resetSequenceMilli=3000;

}
CButton::CButton(uint8_t buttonPin, uint8_t buttonMode,int shortPushMilli,int longPushMilli,int expireSequenceMilli,int timeOut4SequenceMilli)
{
	this->pin=buttonPin;
	mode = buttonMode;
	this->longPushMilli=longPushMilli;
	this->shortPushMilli=shortPushMilli;
	this->expireSequenceMilli=expireSequenceMilli;
	this->timeOut4SequenceMilli=timeOut4SequenceMilli;
	this->resetSequenceMilli=timeOut4SequenceMilli;
}


void CButton::begin()
{
	Module::begin();
    pinMode(pin,INPUT);

	mode==PULLDOWN ? pulldown() : pullup();
    state = 0;
    timing[CHANGED] = timing[PREVIOUS] = timing[CURRENT] = 0;
    bitWrite(state,CURRENT,!mode);
    stopCountingSequence=shortCounted=longCounted=false;
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

	/* check if we need to reset a sequence that has been recorded
	 * and is aged.
	 * */
	if(stopCountingSequence==false){
		if(stateChanged()){
			/* check if was a transition from
			 * pressed to release
			 */

			if(!bitRead(state,PREVIOUS)){
				/* new Pressure start
				 * reset the timeout for the sequence
				 */
				timing[START_OF_SEQ] = millis();
				shortCounted=longCounted=false;
			}

		}else{
			/* status doesn't change*/
			if(isPressed()){
				if( shortCounted==false && isExpired(timing[START_OF_SEQ],shortPushMilli) ){
					/* count it only once*/
					shortPressureCount++;
					shortCounted=true;
					timing[START_OF_SEQ] = millis();
				}
				if( longCounted==false && isExpired(timing[START_OF_SEQ],longPushMilli) ){
					/* count it only once*/
					longPressureCount++;
					shortPressureCount--;
					longCounted=true;
					timing[START_OF_SEQ] = millis();
				}
				if(longCounted && isExpired(timing[START_OF_SEQ],resetSequenceMilli)){
					shortPressureCount=longPressureCount=0;
					stopCountingSequence=false;
				}

			}
		}
	}

		if(!isPressed() && (longCounted || shortCounted)){
			if(isExpired(timing[START_OF_SEQ],timeOut4SequenceMilli) && stopCountingSequence==false ){
				stopCountingSequence=true;
			}
			if(stopCountingSequence && isExpired(timing[START_OF_SEQ],expireSequenceMilli)){
				shortPressureCount=longPressureCount=0;
				stopCountingSequence=false;
			}
		}
	delay(20);

}
bool CButton::getSequence(uint8_t *shortCount,uint8_t *longCount){
	if(shortCount==NULL || longCount==NULL || stopCountingSequence==false){
		return false;
	}
	*shortCount=shortPressureCount;
	*longCount=longPressureCount;

	return true;
}
bool CButton::sequenceOnGoing(){
	return (shortPressureCount | longPressureCount);
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

bool CButton::isInLong()
{
   return wasPressed(longPushMilli);
}
bool CButton::isInShort()
{
   return wasPressed(shortPushMilli);
}
/*
 * ||Return true if the CURRENT state is pressed and the button has been
 * pressed for a number of milliseconds equal or major then time.
 */
bool CButton::wasPressed(unsigned long time)
{
    if (bitRead(state,CURRENT)){
        return (timing[CURRENT] - timing[CHANGED]) >= time;
    } else {
        return false;
    }
}
