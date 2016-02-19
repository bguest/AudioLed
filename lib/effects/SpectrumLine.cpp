#include "SpectrumLine.h"

SpectrumLine::SpectrumLine(){
  this->randomize();
}

void SpectrumLine::randomize(){
  lineHeight = random(0, LED_HEIGHT-1);
}

void SpectrumLine::run(Sign &sign, EffectData &data){
  data.shouldStep = true;

  uint8_t min = min(FREQ_COUNT, LED_WIDTH);
  sign.off();

  for(uint8_t i=0; i< min; i++){
    Pixel* pixel = sign.pixel(i, lineHeight);
    if(data.freqAmp[i] > data.maxFreqAmp[i] / 3){
      pixel->isOn = true;
    }
    pixel->hue[0] = (uint32_t)data.freqAmp[i]/data.maxFreqAmp[i]*0xFFFF;
  }

}
