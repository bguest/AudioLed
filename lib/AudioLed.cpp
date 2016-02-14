#include "AudioLed.h"

AudioLed::AudioLed(){
  
}

void AudioLed::init(){
  sound.init();
  effects.init();
}

void AudioLed::run(){
  sound.run(data);
  effects.run(data);
}
