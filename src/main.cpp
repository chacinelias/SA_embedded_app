#include "wifiConnect.h"
#include "httpClient.h"
#include "getTime.h"
#include "sound.h"

#include <ArduinoJson.h>

//create memory pool for json response
StaticJsonDocument<200> doc;

const long callInterval = 5000;
unsigned long previousMillis;

void setup()
{
  Serial.begin(9600);

  //connect to wifi
  wifiConnect();

  //clock init
  rtc.begin();

  // //get time in epoch format
  getEpoch();

  // //backpack init
  matrix.begin(0x70);
  // ringtone_1();
}

void loop(){

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

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= callInterval){
    previousMillis = currentMillis;

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

  //CHECK IF IT'S TIME TO SOUND ALARM
  if(alarmHour == hour && minute >= alarmMinute){
    ringtone_1();
  }
}

