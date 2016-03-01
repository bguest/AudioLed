#include "AudioLed.h"

AudioLed::AudioLed(){
  pushLayer = LAYER_COUNT;
}

void AudioLed::init(){

  for(uint8_t i=0; i<FREQ_COUNT; i++){
    data.freqAmp[i]=0;
    data.maxFreqAmp[i]=0;
    //data.collectTime = 100;
    data.rolloff = 99;
  }

  tempo.init();
  sound.init();
  effects.init();
  remote.init();
}

void AudioLed::run(){
  remote.run();
  if(remote.code != NONE){
    this->handleRemote();
  }
  data.pushLayer = pushLayer;

  data.tempo = tempo.tempo;
  sound.run(data);
  effects.run(data);
}

void AudioLed::handleRemote(){
  IrInput input = remote.code;

  switch(input){
    case PLAY_PAUSE:
      pushLayer++;
      pushLayer = pushLayer % (LAYER_COUNT + 1);
      return;
    case MENUE:
      pushLayer = LAYER_COUNT;
      return;
  }

  if(pushLayer != LAYER_COUNT){
    effects.push(input, pushLayer);
    return;
  }

  switch(input){
    case UP:
      effects.nextEffect(COLOR_LAYER);
      break;
    case DOWN:
      effects.prevEffect(COLOR_LAYER);
      break;
    case LEFT:
      effects.prevEffect(TEXT_LAYER);
      break;
    case RIGHT:
      effects.nextEffect(TEXT_LAYER);
      break;
    case CENTER:
      tempo.tap();
      if(tempo.isDoubleTap){
        this->reset();
      }
      break;
  }
}

void AudioLed::reset(){
  effects.reset();
}
