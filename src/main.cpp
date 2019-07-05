#include "wifiConnect.h"
#include "httpClient.h"

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

  httpClient();
  
  // And just stop, now that we've tried a download
  while(1);
}

