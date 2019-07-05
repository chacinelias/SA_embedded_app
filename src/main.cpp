#include "wifiConnect.h"
#include "httpClient.h"
#include <cstring>

const int LED = 1;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  pinMode(LED, OUTPUT);

  //connect to wifi
  wifiConnect();
}

void loop()
{
  String str = createClient();

  int n = str.length(); 
  
  // declaring character array 
  char char_array[n]; 

  // copying the contents of the 
  // string to char array 
  strcpy(char_array, str.c_str());
  
  for (int i = 0; i < n; i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(char_array[i]);
  }  

  if(str == "\"test\"\n"){
    digitalWrite(LED, HIGH);
    Serial.println("SUCCESS.");
  }else{
    Serial.println("not 1");
  }

  Serial.println();
  Serial.println(str);

  // And just stop, now that we've tried a download
  while(1);
}

