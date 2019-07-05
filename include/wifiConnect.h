#include <Arduino.h>
#include <WiFiNINA.h>

char ssid[] = "Chacin";
char pass[] = "Newton58173";

void wifiConnect(){
    // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // unsuccessful, retry in 4 seconds
    Serial.print("failed ... ");
    delay(4000);
    Serial.print("retrying ... ");
  }

  Serial.println("connected");
}