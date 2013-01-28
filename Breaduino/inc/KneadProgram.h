/*
 * KneadProgram.h
 *
 *  Created on: Jan 22, 2013
 *      Author: zad
 */

#ifndef KNEADPROGRAM_H_
#define KNEADPROGRAM_H_
#include "Breaduino.h"

class KneadProgram: public BreadProgram{
public:
	KneadProgram(){
		type = kneading;
	};
	KneadProgram(uint32_t length_seconds,uint32_t frequency_milly,uint32_t firstMix_milli,uint32_t secondFreq_milli,uint32_t secondMix_milli,knead_mode mode);
	knead_instruction ki;
private:


};


#endif /* KNEADPROGRAM_H_ */
