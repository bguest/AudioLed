#include "Spectrum0.h"

Spectrum0::Spectrum0(){
  for(uint8_t i=0; i<FREQ_COUNT; i++){
    maxAmp[i] = 0;
    lastMax[i] = 0;
  }
  isHighOn = false;
}

void Spectrum0::run(Sign &sign, EffectData &data){
  unsigned long currMillis = millis();

  data.shouldStep = true;

  sign.off();
  uint8_t min = min(FREQ_COUNT, LED_WIDTH);

  for(uint8_t i=0; i< min; i++){

    // Update MaxFreq
    if(currMillis - lastMax[i] > RESET_TIME){
      maxAmp[i] = 0;
      lastMax[i] = currMillis;
    }

    if(data.freqAmp[i] > maxAmp[i]){
      maxAmp[i] = data.freqAmp[i];
      lastMax[i] = currMillis;
    }

    uint8_t dotSize = data.maxFreqAmp[i]/LED_HEIGHT;

    for(uint8_t j = 0; j < LED_HEIGHT; j++){
      Pixel* pixel = sign.pixel(i,j);

      if((j+1)*dotSize < data.freqAmp[i]){
        pixel -> direction = Up;
      }
      if(isHighOn && maxAmp[i] < (j+1)*dotSize && maxAmp[i] > j*dotSize ){
        pixel -> direction = Up;
      }
    } 
  }

}

