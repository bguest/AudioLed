#include "Effects.h"
#include "effects/Effect.cpp"
#include "effects/Diffusion.cpp"
#include "effects/RandomOn.cpp"
#include "effects/SingleFade.cpp"
#include "effects/TwoColor.cpp"
#include "effects/Spectrum0.cpp"
#include "effects/Wander.cpp"
#include "effects/Wave0.cpp"
#ifdef USE_LINE_SPECTRUM
  #include "effects/SpectrumLine.cpp"
#endif

Effects::Effects(){
  effect[0]  = &randomOn;
  cEffect[0] = RANDOM_ON;
  effect[1]  = &twoColor;
  cEffect[1] = TWO_COLOR;
  lastRun = 0;
}

void Effects::init(){
  sign.init();
  strip = Adafruit_WS2801(LED_COUNT, DATA_PIN, CLK_PIN);
  strip.begin();
  strip.show();
}

void Effects::run(EffectData &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun > UPDATE_DURRATION){
    lastRun = currMillis;
    this->updateShouldStep(data);
    effect[0] -> run(sign, data);
    effect[1] -> run(sign, data);
    this -> updateStrip();
    strip.show();
  }
}

void Effects::push(IrInput input, uint8_t layer){
  effect[layer]->push(input);
}


void Effects::updateShouldStep(EffectData &data){
  unsigned long currMillis = millis();
  if(currMillis - lastStep > data.tempo){
    data.shouldStep = true;
    lastStep = currMillis;
  }else{
    data.shouldStep = false;
  }
}

void Effects::setEffect(uint8_t kEffect, uint8_t layer){
  cEffect[layer] = kEffect;
  switch(kEffect){
    case RANDOM_ON: effect[layer] = &randomOn; break;
    case SINGLE_FADE: effect[layer] = &singleFade; break;
    case TWO_COLOR: effect[layer] = &twoColor; break;
    case WAVE0: effect[layer] = &wave0; break;
    case DIFFUSION: effect[layer] = &diffusion; break;
    case SPECTRUM_0: effect[layer] = &spectrum0; break;
    case WANDER: effect[layer] = &wander; break;
#ifdef USE_LINE_SPECTRUM
    case SPECTRUM_LINE: effect[layer] = &spectrumLine; break;
#endif
  }
}

void Effects::nextEffect(uint8_t layer){
  cEffect[layer]++;
  cEffect[layer] = cEffect[layer] % EFFECT_COUNT;
  this -> setEffect(cEffect[layer], layer);
}

void Effects::prevEffect(uint8_t layer){
  if(cEffect[layer] == 0){
    cEffect[layer] = EFFECT_COUNT - 1;
  }else{
    cEffect[layer]--;
    cEffect[layer] = cEffect[layer] % EFFECT_COUNT;
  }
  this -> setEffect(cEffect[layer], layer);
}

void Effects::updateStrip(){
  uint8_t offset = 0;
  for(uint8_t idx = offset; idx< LED_COUNT; idx++){
    Pixel* pixel = sign.pixel(idx);
    strip.setPixelColor(idx-offset, pixel->color());
  }

}

