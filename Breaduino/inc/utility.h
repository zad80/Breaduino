/*
 * utility.h
 *
 *  Created on: Jan 26, 2013
 *      Author: zad
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include "Arduino.h"
#ifdef __cplusplus
extern "C" {
#endif
boolean isExpired(unsigned long start,unsigned long length);

boolean isExpired2(unsigned long now,unsigned long start,unsigned long length);

#ifdef __cplusplus
}
#endif

#endif /* UTILITY_H_ */
