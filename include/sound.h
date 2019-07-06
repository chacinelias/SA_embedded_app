#define PIEZO 1
#define LED 2

void soundAlarm() {
    pinMode(PIEZO, OUTPUT);
    pinMode(LED, OUTPUT);

    int count = 0;

  while(count < 10){
    digitalWrite(LED, HIGH);
    tone(PIEZO, 1000, 250);
    delay(250);
    digitalWrite(LED, LOW);
    delay(250); 
    count++;
  }
}