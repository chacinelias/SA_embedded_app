#include "wifiConnect.h"
#include "httpClient.h"
#include "sound.h"
#include <cstring>

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //connect to wifi
  wifiConnect();
}

void loop()
{
  String str = createClient();

  // int n = str.length();
  // char char_array[n];
  // strcpy(char_array, str.c_str());

  if(str == "\"test\"\n"){
    Serial.println("SUCCESS.");
    soundAlarm();
  }else{
    Serial.println("FAIL.");
  }

  while (1);
}

