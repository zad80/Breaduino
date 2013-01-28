/*
 * utility.c
 *
 *  Created on: Jan 26, 2013
 *      Author: zad
 */
#include "utility.h"

boolean isExpired(unsigned long start,unsigned long length){
	return millis()>(start+length);
}
boolean isExpired2(unsigned long now,unsigned long start,unsigned long length){
	return now>(start+length);
}
