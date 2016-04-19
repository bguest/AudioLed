#include "Arduino.h"
#include "Sound.h"

#define STROBE 2
#define RESET 3
#define AUDIO_OUT A0
#define AUDIO_RAW A1
#define USE_RAW_VOLUME 1

const uint8_t ROLLOFF_DURRATION = 5;

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
    freqAmp[i] = 0;
  }
  lastCollect = 0;
}

void Sound::run(EffectData &data){

  uint16_t currAmp;
  uint16_t currVolume = 0;

  for(uint8_t i = 0; i<FREQ_COUNT; i++) {
    currAmp = ( analogRead(AUDIO_OUT) + analogRead(AUDIO_OUT) )/2;
#if USE_RAW_VOLUME == 1
    currVolume = ( analogRead(AUDIO_RAW) + analogRead(AUDIO_RAW) )/2;
    if(currVolume > volume){
      volume = currVolume;
    }
#else
    currVolume += currAmp;
#endif
    if (currAmp > freqAmp[i]){
      freqAmp[i] = currAmp;
    }
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }

#if USE_RAW_VOLUME == 0
  if(currVolume > volume){
    volume = currVolume;
  }
#endif

  // Update if > Sound collect time
  unsigned long currMillis = millis();

  if(currMillis - lastCollect > ROLLOFF_DURRATION){
    lastCollect = currMillis;

    for(uint8_t i = 0; i<FREQ_COUNT; i++) {
      if(freqAmp[i] > data.freqAmp[i]){
        data.freqAmp[i] = freqAmp[i];
      }else{
        data.freqAmp[i] = (data.freqAmp[i]*data.rolloff)/200;
      }

      if(freqAmp[i] > data.maxFreqAmp[i]){
        data.maxFreqAmp[i] = freqAmp[i];
      }
      freqAmp[i] = 0;
    }

    if(volume > data.volume){
      data.volume = volume;
    }else{
      data.volume = (data.volume*data.rolloff)/200;
    }

    if(volume > data.maxVolume){
      data.maxVolume = volume;
    }
    volume = 0;
  }

}


