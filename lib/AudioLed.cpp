#include "AudioLed.h"

AudioLed::AudioLed(){
  irrecv = new IRrecv(IR_PIN);
}

void AudioLed::init(){
  irrecv -> enableIRIn();

  for(uint8_t i=0; i<FREQ_COUNT; i++){
    data.freqAmp[i]=0;
    data.maxFreqAmp[i]=0;
  }
  tempo.init();
  sound.init();
  effects.init();
}

void AudioLed::run(){

  if (irrecv -> decode(&irResults)) {
    this -> handleIrCode(irResults.value);
    irrecv -> resume(); // Receive the next value
  }
  data.tempo = tempo.tempo;
  sound.run(data);
  effects.run(data);
}

void AudioLed::handleIrCode(uint32_t irCode){

  switch(irCode){
    case PLAY_PAUSE_IR:
      break;
    case MENUE_IR:
      break;
    case UP_IR:
      effects.nextEffect(ColorLayer);
      break;
    case DOWN_IR:
      effects.prevEffect(ColorLayer);
      break;
    case LEFT_IR:
      effects.prevEffect(TextLayer);
      break;
    case RIGHT_IR:
      effects.nextEffect(TextLayer);
      break;
    case CENTER_IR:
      tempo.tap();
      break;
  }

}
