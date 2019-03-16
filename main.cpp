#include <Arduino.h>
/*
// https://robotdyn.com/pub/media/0G-00004891==Mod-LED-Display-6D-74HC595/DOCS/Schematic==0G-00004891==Mod-LED-Display-6D-74HC595.pdf
// Thanks to https://forum.arduino.cc/index.php?topic=518797.0
*/
const int latchPIN = 6;
const int clockPIN = 7;
const int dataPIN = 8;

// ST_CP = SCK
// SH_CP = RCK
// SDI   = DIO
// Common anode
#define DS dataPIN
#define STCP clockPIN
#define SHCP latchPIN

boolean numbersDef[10][8] =
{
  {1,1,1,1,1,1,0}, //zero
  {0,1,1,0,0,0,0}, //one
  {1,1,0,1,1,0,1}, //two
  {1,1,1,1,0,0,1}, //three
  {0,1,1,0,0,1,1}, //four
  {1,0,1,1,0,1,1}, //five
  {1,0,1,1,1,1,1}, //six
  {1,1,1,0,0,0,0}, //seven
  {1,1,1,1,1,1,1}, //eight
  {1,1,1,1,0,1,1}  //nine
};

boolean digitsTable[8][8] =
{
  {0,0,0,0,1,0,0,0}, // first digit
  {0,0,0,0,0,1,0,0}, // second
  {0,0,0,0,0,0,1,0}, // third
  {1,0,0,0,0,0,0,0}, // forth
  {0,1,0,0,0,0,0,0}, // fifth
  {0,0,1,0,0,0,0,0}  // sixth  
};

void setup() {
  pinMode(DS, OUTPUT);
  pinMode(STCP, OUTPUT);
  pinMode(SHCP, OUTPUT);
  digitalWrite(DS, LOW);
  digitalWrite(STCP, LOW);
  digitalWrite(SHCP, LOW);
}

boolean display_buffer[16];

void prepareDisplayBuffer(int number, int digit_order, boolean showDot)
{
  for(int index=7; index>=0; index--)
  {
    display_buffer[index] = digitsTable[digit_order-1][index];
  }
  for(int index=14; index>=8; index--)
  {
    display_buffer[index] = !numbersDef[number-1][index]; //because logic is sanity, right?
  }
  if(showDot == true)
    display_buffer[15] = 0;
  else
    display_buffer[15] = 1;
}

void writeDigit(int number, int order, bool showDot = false)
{
  prepareDisplayBuffer(number, order, showDot);
  digitalWrite(SHCP, LOW);
  for(int i=15; i>=0; i--)
  {
      digitalWrite(STCP, LOW);
      digitalWrite(DS, display_buffer[i]); //output LOW - enable segments, HIGH - disable segments
      digitalWrite(STCP, HIGH);
   }
  digitalWrite(SHCP, HIGH);
}


void loop() {
  const uint32_t test = millis();
  char buf[7] = {0,};
  snprintf(buf, 7, "%6ld", test);

  for(int i = 0; i < 6; i++) {
    int num = (buf[i] - '0') & 0xFF;

    writeDigit(num, i + 1);
  }
}
