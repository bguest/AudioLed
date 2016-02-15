#include "Spectrum0.h"

Spectrum0::Spectrum0(){

}

void Spectrum0::run(Sign &sign, EffectData &data){
  unsigned long currMillis = millis();

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

    for(uint8_t j = 1; j <= LED_HEIGHT; j++){
      Pixel* pixel = sign.pixel(i,j);

      if(j*dotSize < data.freqAmp[i]){
        pixel -> isOn = true;
      }
      else if(maxAmp[i] < j*dotSize && maxAmp[i] > (j-1)*dotSize ){
        pixel -> isOn = true;
      }

    } 

  }


}

