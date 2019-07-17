#include <I2S.h>

int frequency; //in Hz
int sampleRate; //in Hz
int amplitude;
bool octave;
int halfWavelength; // half wavelength of square wave

int sound;
int volume;


void ringtone_1(){

  frequency = 1000;
  sampleRate = 8000;
  octave = true;
  short sample; // current sample value
  int count = 0;

  // start I2S at the sample rate with 16-bits per sample
  if (!I2S.begin(I2S_PHILIPS_MODE, sampleRate, 16)) {
    Serial.println("Failed to initialize I2S!");
    while (1); // do nothing
  }

  Serial.println("ALARM!!!");

  while(1){
    if(count > 1000){
        sample = 0;
    }else{
      sample = 2000;
      if(octave){
        octave = false;
        frequency *= 2;
      }else{
        octave = true;
        frequency /= 2;
      }
    }

    halfWavelength = (sampleRate / frequency);

    if (count % halfWavelength == 0) {
      // invert the sample every half wavelength count multiple to generate square wave
      sample = -1 * sample;
    }

    // write the same sample twice, once for left and once for the right channel
    I2S.write(sample);
    I2S.write(sample);

    // increment the counter for the next sample
    count++;

    if(count >= 2001){ count = 0;}
  }
}
