#include "AudioLed.h"

AudioLed::AudioLed(){
  
}

void AudioLed::init(){
#ifdef DEBUG
  Serial.println("RESET");
#endif
  for(uint8_t i=0; i<FREQ_COUNT; i++){
    data.freqAmp[i]=0;
    data.maxFreqAmp[i]=0;
  }
  sound.init();
  effects.init();
}

void AudioLed::run(){
  sound.run(data);
  effects.run(data);
}
