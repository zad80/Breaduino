/*
 * Breaduino.h
 *
 *  Created on: Jan 22, 2013
 *      Author: zad
 */

#ifndef BREADUINO_H_
#define BREADUINO_H_
#include "Arduino.h"

//add your includes for the project testLCD here
#include "SoftwareSerial.h"
#include "proxySerial.h"
#include "Serial_LCD.h"
#include "GUI.h"

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

typedef enum _bread_machine_state{
	wait_command=0,
	running=1,
	stopped=2
}bread_machine_state;

typedef enum _program_type{
	kneading=0,
	baking=1,
	rising=2,
	max_program_type=3
}program_type;
typedef enum _knead_mode{
	/*
	 * kneading can happen at different modes:
	 * Continuous: the kneading continue without stopping
	 * dashed: "firstMix" determines how long the knead continue before
	 * have a stop for a "frequency" seconds before restart
	 * alternated: it's possible to program an alternating a sequence like the following
	 * "firstMix"-> pause for "frequency" -> secondMix-> pause for secondFreq and then again
	 * till length is passed
	 */
	continuos=0,
	dashed=1,
	alternated=3
}knead_mode;

typedef struct _knead_instruction{
	uint32_t frequency_milli;
	uint32_t length_seconds;
	uint32_t firstMix_milli;
	uint32_t secondMix_milli;
	uint32_t secondFreq_milli;
	knead_mode mode;
	knead_mode status;
}knead_instruction;
typedef enum _mixing_step_status{
	waiting2Mix=0,
	firstMix=1,
	secondMix=2,
	firstPause=3,
	secondPause=4,
}mixing_step_status;
class BreadProgram
{
public:
/*
virtual senza corpo, pure virtual il figlio deve per forza implementarla
virtual definita puo' essere ridefinita , in questo modo il metodo specializzato della classe figlio puo' essere richiamato
anche se si ha un puntatore generico di tipo padre che punta alla classe specializzata
*/

protected:
	program_type type;
};



#endif /* BREADUINO_H_ */
