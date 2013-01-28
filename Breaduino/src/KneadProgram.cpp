/*
 * KneadProgram.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: zad
 */

#include "KneadProgram.h"



KneadProgram::KneadProgram(uint32_t length_seconds,uint32_t frequency_milly,uint32_t firstMix_milli,uint32_t secondFreq_milli,uint32_t secondMix_milli,knead_mode mode)
{
	ki.firstMix_milli=firstMix_milli;
	ki.frequency_milli=frequency_milly;

	ki.length_seconds=length_seconds;
	ki.secondMix_milli=secondMix_milli;
	ki.secondFreq_milli=secondFreq_milli;
	ki.mode=mode;
	type=kneading;
}

