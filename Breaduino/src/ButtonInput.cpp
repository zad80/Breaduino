/*
 * ButtonInput.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: zad
 */

#include "ButtonInput.h"

ButtonInput::ButtonInput(Module **button){
	buttons=button;
}

void ButtonInput::begin(){
	Module::begin();

}
