#include "Arduino.h"
#include "Sound.h"

#define STROBE 2
#define RESET 3
#define AUDIO_OUT A0

void Sound::init(){
  //
  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(AUDIO_OUT, INPUT);
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);

  for(uint8_t i=0; i<7; i++){
    maxFreqAmp[i] = 0;
  }
}

void Sound::run(EffectData &data){

  data.volume = 0;
  for(uint8_t i = 0; i<FREQ_COUNT; i++) {
    data.freqAmp[i] = (analogRead(AUDIO_OUT) + analogRead(AUDIO_OUT))/2;
    data.volume += data.freqAmp[i];
    if (data.freqAmp[i] > data.maxFreqAmp[i]){
      data.maxFreqAmp[i] = data.freqAmp[i];
    }
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
  if(data.volume > data.maxVolume){
    data.maxVolume = data.volume;
  }
}


