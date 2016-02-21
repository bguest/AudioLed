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
    pixel->hue[0] = map(data.freqAmp[i],0,data.maxFreqAmp[i],0,0xFFFF);
  }

}
