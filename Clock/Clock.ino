int Eingang = 6;
int Ausgabe = 3;
int Zeit = 600;
#include <Display.h>
#include <Digit.h>
#include <Segment.h>

const byte digit_pins[4] {6, 9, 10, 0}; // From com1 - com4
const byte segment_pins[7] {7, 11, 2, 4, 5, 8, 1}; // From a - g (abc...g)
const byte dp_pin = 3;
char* timeOut = "00.00";

Display d(digit_pins, segment_pins, dp_pin);

void setup() {
  for (int i = 0; i <= 11; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(Eingang,INPUT);
  pinMode(Ausgabe,OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(Eingang), Strike, RISING);
}

void loop() {
  /*if (Zeit == 0) {
    Ausgabe = 6;
  } else {
  Zeit--;
  }
  printTime(Zeit/60,Zeit%60); //TODO void printTime(int m,int s);
  */
  d.print("13.37");
}

void printTime(int m, int s) {
  
}

void Strike()
{
  Zeit = Zeit - 200;
}
