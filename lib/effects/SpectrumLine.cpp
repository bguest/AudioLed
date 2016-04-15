#include "SpectrumLine.h"

SpectrumLine::SpectrumLine(){
  this->randomize();
  lineHeight = 2;
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

void SpectrumLine::setConfig(uint8_t kConfig){
  switch(kConfig){
    case BOTTOM_BUBBLES_CONFIG:
      lineHeight = 0;
      break;

    case CENTER_SPECTRUM_CONFIG:
      lineHeight = LED_Y_CENTER;
      break;
  }
}

void SpectrumLine::push(IrInput input){
  Effect::push(input);

  switch(input){
    case UP: if(lineHeight < LED_HEIGHT-1){ ++lineHeight;} break;
    case DOWN: if(lineHeight > 0){ --lineHeight;} break;
  }
}
