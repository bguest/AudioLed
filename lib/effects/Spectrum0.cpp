#include "Spectrum0.h"

Spectrum0::Spectrum0(){
  for(uint8_t i=0; i<FREQ_COUNT; i++){
    maxAmp[i] = 0;
    lastMax[i] = 0;
  }
  isHighOn = false;
  rolloff = 192;
}

void Spectrum0::run(Sign &sign, EffectData &data){
  unsigned long currMillis = millis();

  data.shouldStep = true;
  data.rolloff = rolloff;

  sign.off();
  uint8_t min = min(FREQ_COUNT, LED_WIDTH);

  for(uint8_t i=0; i< min; i++){

    // Update MaxFreq
    if(data.freqAmp[i] > maxAmp[i]){
      maxAmp[i] = data.freqAmp[i];
      lastMax[i] = currMillis;
    }else if( currMillis - lastMax[i] > data.tempo / 2){
      maxAmp[i] = (maxAmp[i]*rolloff)/200;
    }

    uint8_t dotSize = data.maxFreqAmp[i]/LED_HEIGHT;

    for(uint8_t j = 0; j < LED_HEIGHT; j++){
      Pixel* pixel = sign.pixel(i,j);

      if((j+1)*dotSize < data.freqAmp[i]){
        pixel -> direction[0] = Up;
      }
      if(isHighOn && maxAmp[i] < (j+1)*dotSize && maxAmp[i] > j*dotSize ){
        pixel -> direction[0] = Down;
      }
    }
  }
}

void Spectrum0::setConfig(uint8_t kConfig){
  switch(kConfig){
    case FIRE0_CONFIG:
      rolloff = 180;
      isHighOn = true;
  }
}

void Spectrum0::push(IrInput input){
  Effect::push(input);
  switch(input){
    case UP: if(rolloff < 200){rolloff++;} break;
    case DOWN: if(rolloff > 0){rolloff--;} break;
    case RIGHT: isHighOn = !isHighOn; break;
  }
}
