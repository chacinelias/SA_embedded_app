#include "wifiConnect.h"
#include "httpClient.h"
#include "getTime.h"
#include "sound.h"

#include <ArduinoJson.h>

//create memory pool for json response
StaticJsonDocument<200> doc;

Chrono callInterval;

const int localAlarmHour = 11;
const int localAlarmMinute = 9;

boolean alarm;
int buttonState;

void setup(){
  Serial.begin(9600);

  //connect to wifi
  wifiConnect();

  //clock init
  rtc.begin();

  // //get time in epoch format
  getEpoch();

  // //backpack init
  matrix.begin(0x70);

  alarm = false;

  buttonState = 0;

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop(){

  buttonState = digitalRead(buttonPin);

  hour = rtc.getHours();
  minute = rtc.getMinutes();
  second = rtc.getSeconds();

  //Adjust for timezone
  if(hour > 4){
    hour += GMT;
  }else{
    hour += 24 + GMT;
  }

  //WRITE TO LED
  writeHours(hour);
  writeMinutes(minute);
  matrix.drawColon(second % 2 == 0);
  matrix.writeColon();

  if(callInterval.hasPassed(15000) && !alarm){
    callInterval.restart();
    //Print to serial monitor
    Serial.println("----------------------");
    printDate();
    printTime();

    String str = createClient();
    deserializeJson(doc, str);

    alarmHour = doc["alarmHour"];
    alarmMinute = doc["alarmMinute"];
    sound = doc["sound"]; 
    volume = doc["volume"];

    Serial.print("alarmHour: ");
    Serial.println(alarmHour);
    Serial.print("alarmMinute: ");
    Serial.println(alarmMinute);
    Serial.print("sound: ");
    Serial.println(sound);
    Serial.print("volume: ");
    Serial.println(volume);
  }

  if (!alarm){
    while(buttonState){
      buttonState = digitalRead(buttonPin);

      writeHours(alarmHour);
      writeMinutes(alarmMinute);
      digitalWrite(ledPin, HIGH);
      matrix.drawColon(1);
      matrix.writeColon();
    }
    digitalWrite(ledPin, LOW);
  }

  //CHECK IF IT'S TIME TO SOUND ALARM
  if(((alarmHour == hour && minute == alarmMinute) || (localAlarmHour == hour && minute == localAlarmMinute)) && ringtone_1(buttonState)){
    alarm = true;
  }else{
    alarm = false;
  }
}

