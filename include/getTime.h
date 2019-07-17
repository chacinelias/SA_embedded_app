#include <RTCZero.h>
#include <WiFiNINA.h>

//seven segment includes:
#include <Wire.h>
#include <Adafruit_LEDBackpack.h>

//seven segment matrix object
Adafruit_7segment matrix = Adafruit_7segment();

//clock object
RTCZero rtc;

int hour, minute, second, alarmHour, alarmMinute;
const int GMT = -4; //change this to adapt it to your time zone

void getEpoch(){
  unsigned long epoch = 0;
  int numberOfTries = 0, maxTries = 15;

  Serial.print("Getting current time");
  while(epoch == 0 && numberOfTries < maxTries){

    epoch = WiFi.getTime();
    delay(1000);
    Serial.print(".");
    numberOfTries++;
  }

  Serial.println();

  if (epoch == 0) {
    Serial.print("NTP unreachable!!");
    while (1);
  }
  else {
    Serial.print("Epoch received: ");
    Serial.println(epoch);
    rtc.setEpoch(epoch);

    Serial.println();
  }
}

void writeHours(int num){

  if(num > 12) num = num -12;

  if(num > 9){

    int n = num - 10;
    matrix.writeDigitNum(0, 1, 0);
    matrix.writeDigitNum(1, n, 0);
  }else{
    matrix.writeDigitNum(0, 0, 0);
    matrix.writeDigitNum(1, num, 0);
  }
}

void writeMinutes(int num){

  if(num > 9){

    int n1 = num % 10;
    int n2 = num / 10;
    matrix.writeDigitNum(3, n2, 0);
    matrix.writeDigitNum(4, n1, 0);
  }else{
    matrix.writeDigitNum(3, 0, 0);
    matrix.writeDigitNum(4, num, 0);
  }

  matrix.writeDisplay();
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}

void printTime(){

  // if(hour > 12) hour = hour - 12;

    print2digits(hour);
    Serial.print(":");
    print2digits(minute);
    Serial.print(":");
    print2digits(second);
    Serial.println();
  }

void printDate(){
  Serial.print(rtc.getDay());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.print(rtc.getYear());

  Serial.print(" ");
}