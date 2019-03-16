#include <Arduino.h>
/*
// And https://github.com/MiguelPynto/ShiftDisplay
*/
const int latchPIN = 6;
const int clockPIN = 7;
const int dataPIN = 8;

#include <ShiftDisplay.h>
const int indexes[] = {4,5,6,0,1,2,3,7};
const int sizes[] = {6, 0};
ShiftDisplay display(latchPIN, clockPIN, dataPIN, COMMON_ANODE, sizes, true, indexes);

const int delay_ = 200;
long test = 999999;
const int tacho = 0;

void setup() {
  for(long test = 999999; test >= 0; test -= 111111) {
    display.set(test, DEFAULT_DECIMAL_PLACES_INTEGER, true);
    display.show(delay_);
  }

	display.set("START");
  display.show(1000);
}

void loop() {
  display.set((long)millis());
	display.update();
}
