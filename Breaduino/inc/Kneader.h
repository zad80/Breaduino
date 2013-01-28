/*
 * kneader.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: zad
 */

#ifndef KNEADER_H_
#define KNEADER_H_

#include "Module.h"
#include "KneadProgram.h"

class Kneader:public Module{
public:
	Kneader(uint8_t pin,uint8_t onLevel);
	void init(KneadProgram *program);
	void stop();
	void on(){
		if(!isEnabled()){
			mode=!mode;
			digitalWrite(knead_pin,onLevel);
		}
	}
	void off(){
		if(isEnabled()){
			mode=!mode;
			digitalWrite(knead_pin,!onLevel);
		}
	}

	bool isEnabled(){
		return mode;
	}
	void continuos_program();
	void dashed_program();
	void alternated_program();

	virtual void begin();
	virtual void run();
protected:
	uint8_t knead_pin;
	uint8_t onLevel;
	bool mode;
	KneadProgram *kp;
	unsigned long started;
	unsigned long started_pause;
	unsigned long started_kenading;
	mixing_step_status mixing_step;
};



#endif /* KNEADER_H_ */
