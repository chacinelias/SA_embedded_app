#include <Chrono.h>

int sound;
int volume;

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  5;
const int piezoPin = 0;
int flag = true;

Chrono toneInterval;

boolean ringtone_1(int state){

  if(toneInterval.hasPassed(400) && flag){
    toneInterval.restart();

    tone(piezoPin, 1000, 200);

    digitalWrite(ledPin, HIGH);

    if (state == HIGH) {
      digitalWrite(ledPin, LOW);
      pinMode(piezoPin, INPUT);
      flag = false;
    }
  }

  return flag;
}
