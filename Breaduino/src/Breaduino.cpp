// Do not remove the include below
#include "Breaduino.h"
#include "Button.h"
#include "Kneader.h"
#include "KneadProgram.h"



const int sserialRX =  5;	// SoftwareSerial RX
const int sserialTX =  6;	// SoftwareSerial TX
const int LCDResetPin = 7;	//ResetLCD

SoftwareSerial mySerial(sserialRX,sserialTX);

ProxySerial myPort(&mySerial); // hardware abstraction layer
Serial_LCD myLCD(&myPort); // LCD

CButton loaf_bt(8,LOW);
CButton start_bt(9,LOW);
CButton inc_bt(10,LOW);
CButton dec_bt(11,LOW);
CButton menu_bt(12,LOW);
CButton color_bt(13,LOW);
uint8_t aa;
Kneader kneader(2,HIGH);
/* create a kneader program
 * program length 2 minutes=60*2
 * frequancy between one kenading and the other 1 sec=1000ms
 * first_mix length in ms of the first mode kneading 10sec=10000ms
 * secondFreq_milli frequancy between one kenading of second type and the other 0
 * 	not used in continuos mode
 * 	second_mix length in ms of the second type kneading 0
 * 	 not used in continuos mode
 */
KneadProgram kp( 60*2,5*1000, 10*1000, 0, 0, continuos);

Module* hw[] = {
		&start_bt,
		&color_bt,
		&dec_bt,
		&inc_bt,
		&loaf_bt,
		&menu_bt,
		&kneader,
		0 };

void setup() {
  Serial.begin(19200);
  mySerial.begin(38400);
  Module::begin(hw);
  // === End of Serial port initialisation ===
  myLCD.begin(LCDResetPin);
}
bool start_pressed_short=false;
bool start_pressed_long=false;
bool change_lcd=true;
void loop() {

 Module::update(hw);
 if(start_bt.wasPressed(40)){
	 start_pressed_short=true;
	 if(!start_pressed_long){
		 dLabel(&myLCD, 0, 0, 128, 25, "start", 0xffff, myLCD.setColour(0x00, 0x7f, 0), 0, 0, 9);
	 }
	 if(start_bt.wasPressed(1000)){
		 start_pressed_long=true;
		 start_pressed_short=false;
		 dLabel(&myLCD, 0, 0, 128, 25, "start", 0xffff, myLCD.setColour(0x7f, 0x00, 0x00), 0, 0, 9);
		 dLabel(&myLCD, 0, 25, 128, 25, "stop", 0xffff, myLCD.setColour(0x00, 0x7f, 0), 0, 0, 9);

	 }
	 change_lcd=true;
 }else{
	 if(start_pressed_long){
		 kneader.stop();
	 }else{
	 }
	 if(start_pressed_short){
		 kneader.init(&kp);
	 }
	 if(change_lcd)
	 {
		 dLabel(&myLCD, 0, 0, 128, 25, "start", 0xffff, myLCD.setColour(0x7f, 0x00, 0x00), 0, 0, 9);
		 dLabel(&myLCD, 0, 25, 128, 25, "stop", 0xffff, myLCD.setColour(0x7f, 0x00, 0), 0, 0, 9);
		 change_lcd=false;

	 }
	 start_pressed_short=false;
	 start_pressed_long=false;
 }


}
#if 0
uint8_t i;
String temp="Temperature=";
void loop() {

 Module::update(hw);
//  String toLcd=temp+String(0, DEC);
 if(start_bt.wasPressed(40)){
	 if(start_bt.wasPressed(2000)){
		 dLabel(&myLCD, 0, 0, 128, 25, "start", 0xffff, myLCD.setColour(0x00, 0x00, 0x7f), 0, 0, 9);
	 }else{
		 dLabel(&myLCD, 0, 0, 128, 25, "start", 0xffff, myLCD.setColour(0x00, 0x7f, 0x00), 0, 0, 9);
	 }
 }else{
	 dLabel(&myLCD, 0, 0, 128, 25, "start", 0xffff, myLCD.setColour(0x7f, 0x00, 0x00), 0, 0, 9);
 }
 if(loaf_bt.wasPressed(40))
	 dLabel(&myLCD, 0, 25*1, 128, 25, "loaf", 0xffff, myLCD.setColour(0x00, 0x7f, 0x00), 0, 0, 9);
 else
	 dLabel(&myLCD, 0, 25*1, 128, 25, "loaf", 0xffff, myLCD.setColour(0x7f, 0x00, 0x00), 0, 0, 9);

 if(inc_bt.wasPressed(40))
	 dLabel(&myLCD, 0, 25*2, 128, 25, "inc", 0xffff, myLCD.setColour(0x00, 0x7f, 0x00), 0, 0, 9);
 else
	 dLabel(&myLCD, 0, 25*2, 128, 25, "inc", 0xffff, myLCD.setColour(0x7f, 0x00, 0x00), 0, 0, 9);

 if(dec_bt.wasPressed(40))
	 dLabel(&myLCD, 0, 25*3, 128, 25, "dec", 0xffff, myLCD.setColour(0x00, 0x7f, 0x00), 0, 0, 9);
 else
	 dLabel(&myLCD, 0, 25*3, 128, 25, "dec", 0xffff, myLCD.setColour(0x7f, 0x00, 0x00), 0, 0, 9);

 if(menu_bt.wasPressed(40))
	 dLabel(&myLCD, 0, 25*4, 64, 25, "menu", 0xffff, myLCD.setColour(0x00, 0x7f, 0x00), 0, 0, 9);
 else
	 dLabel(&myLCD, 0, 25*4, 64, 25, "menu", 0xffff, myLCD.setColour(0x7f, 0x00, 0x00), 0, 0, 9);

 if(color_bt.wasPressed(40))
 	 dLabel(&myLCD, 64, 25*4, 64, 25, "color", 0xffff, myLCD.setColour(0x00, 0x7f, 0x00), 0, 0, 9);
  else
 	 dLabel(&myLCD, 64, 25*4, 64, 25, "color", 0xffff, myLCD.setColour(0x7f, 0x00, 0x00), 0, 0, 9);
}

/* main loop :
 * its just a loop where every piece of hardware is updated
 * every hardware has a state which it has proper configuration
 * the main loop can be blocked at any time by the use of start/stop button
 * */
 */
#endif
