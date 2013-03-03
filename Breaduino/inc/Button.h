#ifndef BUTTON_H
#define BUTTON_H

#include "Module.h"

#define PULLUP HIGH
#define PULLDOWN LOW

#define CURRENT 0
#define PREVIOUS 1
#define CHANGED 2
#define START_OF_SEQ 3
class CButton
: public Module
{
  public:
    CButton(uint8_t buttonPin, uint8_t buttonMode=PULLDOWN);
    CButton(uint8_t buttonPin, uint8_t buttonMode,int shortMilli,int longMilli,int expireSequenceMilli,int timeOut4SequenceMilli);
	virtual void begin();

    void pullup();
    void pulldown();
    bool isPressed();
    bool isInShort();
    bool isInLong();
    bool stateChanged();
	bool isReleased();
	bool wasPressed(unsigned long time);
	bool sequenceOnGoing();
	bool getSequence(uint8_t *shortCount,uint8_t *longCount);
	bool isSequenceReady(){return stopCountingSequence;};
	virtual void run();
protected:
  private: 
    uint8_t pin;
    uint8_t mode;
    uint8_t state;
    /* milliseconds needed to hold the button for a short pressure*/
    int shortPushMilli;
    /* Number of short Pressure of the sequence*/
    uint8_t shortPressureCount;
    /* Number of long Pressure of the sequence*/
    uint8_t longPressureCount;
    /* milliseconds needed to hold the button for a long pressure*/
    int longPushMilli;
    /* timing is an array which contains the start of different events begin */
	unsigned long timing[4];
	/* number of millisecond used to age a button pressures sequence*/
	int expireSequenceMilli;
	/* after timeOut4SequenceMilli milli if no pressure is detected , the sequence is considered closed */
	int timeOut4SequenceMilli;
	/* if during a sequence the button is pressed for resetSequenceMilli the sequence is invalidated*/
	int resetSequenceMilli;
	/* Flag used to indicate if a long pressure has been detected */
	bool longCounted;
	/* Flag used to indicate if a short pressure has been detected */
	bool shortCounted;
	/* Flag used to indicate to stop counting pressure for a sequence */
	bool stopCountingSequence;


};

#endif
