/*
 * Kneader.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: zad
 */
#include "Kneader.h"

Kneader::Kneader(uint8_t pin,uint8_t onLevel){

		knead_pin=pin;
		this->onLevel=onLevel;
		pinMode(pin,OUTPUT);
		stop();

	};

void Kneader::stop(){
	active=false;
	off();
	kp=NULL;
	mixing_step=waiting2Mix;
}
void Kneader::run(){
	if(!active)
		return ;
	/* first check if is the first time we run*/
	if(started==0){
		/* in that case mark when the program is started*/
		started=millis();
	}
	/* check if the program is ended */
	if(kp==NULL || isExpired(kp->ki.length_seconds*1000,started) ){
		delay(2000);
		return;
	}
	switch(kp->ki.mode){

	case continuos:
		continuos_program();
		break;
	case dashed:
		dashed_program();
		break;
	case alternated:
		alternated_program();
		break;
	default:
		/* unsupported bake */
		break;
	}
}
void Kneader::continuos_program(){
	switch(mixing_step){
	case waiting2Mix:
		started_kenading=millis();
		mixing_step=firstMix;
		on();
		break;
	case firstMix:
	case secondMix:
		if(isExpired(started_kenading,kp->ki.firstMix_milli)){
			started_pause=millis();
			mixing_step=firstPause;
			off();
		}
		break;
	case firstPause:
	case secondPause:
		if(isExpired(started_pause,kp->ki.frequency_milli) ){
			started_kenading=millis();
			mixing_step=firstMix;
			on();
		}
		break;
	}
}
void Kneader::alternated_program(){
	switch(mixing_step){
	case waiting2Mix:

		break;
	case firstMix:

		break;
	case firstPause:

		break;
	}
}void Kneader::dashed_program(){
	switch(mixing_step){
	case waiting2Mix:
		break;
	case firstMix:
		break;
	case firstPause:
		break;
	}
}
void Kneader::init(KneadProgram *program){
		kp=program;
		mode=false;
		active=true;
		started=0;
		mixing_step=waiting2Mix;
		Module::init();
}
void Kneader::begin(){
	Module::begin();

}



