#include <ArduinoHttpClient.h>
#include <SPI.h>
#include <WiFiNINA.h>

// Name of the server we want to connect to
const char kHostname[] = "flask-deploy-lesson.herokuapp.com";
// endpoint
const char kPath[] = "/";

// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30*1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;

WiFiClient c;
HttpClient http(c, kHostname);

String createClient(){
int err =0;
String response;

  
  err = http.get(kPath);
  if (err == 0)
  {
    Serial.println("startedRequest ok");

    err = http.responseStatusCode();
    if (err >= 0)
    {
      Serial.print("Got status code: ");
      Serial.println(err);

      response = http.responseBody();

    }
    else
    {    
      Serial.print("Getting response failed: ");
      Serial.println(err);
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }

  return response;
  http.stop();
}