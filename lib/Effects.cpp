#include "Effects.h"

#include "effects/Effect.cpp"
#include "effects/Diffusion.cpp"
#include "effects/RandomOn.cpp"
#ifdef USE_SINGLE_FADE
  #include "effects/SingleFade.cpp"
#endif
#include "effects/TwoColor.cpp"
#include "effects/Spectrum0.cpp"
#ifdef USE_WANDER
  #include "effects/Wander.cpp"
#endif
#include "effects/Wave0.cpp"
#ifdef USE_LINE_SPECTRUM
  #include "effects/SpectrumLine.cpp"
#endif
#include "effects/CenterPulse.cpp"
#include "effects/TimeDomain.cpp"
#include "effects/ParticleSystem.cpp"

Effects::Effects(){
  this->reset();
  lastRun = 0;
}

void Effects::init(){
  sign.init();
  strip = Adafruit_WS2801(LED_COUNT, DATA_PIN, CLK_PIN);
  strip.begin();
  strip.show();
}

void Effects::reset(){
  cConfig = 0;
  effect[0]  = &randomOn;
  cEffect[0] = RANDOM_ON;
  effect[1]  = &twoColor;
  cEffect[1] = TWO_COLOR;
}

void Effects::run(EffectData &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun > UPDATE_DURRATION){
    lastRun = currMillis;
    this->updateShouldStep(data);
    effect[0] -> run(sign, data);
    effect[1] -> run(sign, data);
    this -> updateStrip();
    this -> updateStrip(data);
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
    case NO_EFFECT: effect[layer] = &noEffect; break;
    case RANDOM_ON: effect[layer] = &randomOn; break;
#ifdef USE_SINGLE_FADE
    case SINGLE_FADE: effect[layer] = &singleFade; break;
#endif
    case TWO_COLOR: effect[layer] = &twoColor; break;
    case WAVE0: effect[layer] = &wave0; break;
    case DIFFUSION: effect[layer] = &diffusion; break;
    case SPECTRUM_0: effect[layer] = &spectrum0; break;
#ifdef USE_WANDER
    case WANDER: effect[layer] = &wander; break;
#endif
#ifdef USE_LINE_SPECTRUM
    case SPECTRUM_LINE: effect[layer] = &spectrumLine; break;
#endif
    case CENTER_PULSE: effect[layer] = &centerPulse; break;
    case TIME_DOMAIN: effect[layer] = &timeDomain; break;
    case PARTICLE_SYSTEM: effect[layer] = &particleSystem; break;
  }
#ifdef DEBUG
  this->printEffect(kEffect);
#endif
}

#ifdef DEBUG
void Effects::printEffect(uint8_t kEffect){
  switch(kEffect){
    case RANDOM_ON: Serial.println("Random ON"); break;
#ifdef USE_SINGLE_FADE
    case SINGLE_FADE: Serial.println("Single Fade"); break;
#endif
    case TWO_COLOR: Serial.println("Two Color"); break;
    case WAVE0: Serial.println("Wave0"); break;
    case DIFFUSION: Serial.println("Diffusion"); break;
    case SPECTRUM_0: Serial.println("Spectrum0"); break;
#ifdef USE_WANDER
    case WANDER: Serial.println("Wander"); break;
#endif
#ifdef USE_LINE_SPECTRUM
    case SPECTRUM_LINE: Serial.println("SpectrumLine");  break;
#endif
    case CENTER_PULSE: Serial.println("CenterPulse"); break;
    case TIME_DOMAIN: Serial.println("TimeDomain"); break;
    case PARTICLE_SYSTEM: Serial.println("ParticleSystem"); break;
  }
}
#endif

void Effects::setConfig(uint8_t kConfig){
  switch(kConfig){

    case FIRE0_CONFIG:
      this->setEffect(SPECTRUM_0, TEXT_LAYER);
      this->setEffect(TWO_COLOR, COLOR_LAYER);
      break;

    case PS_CENTER_FOUNTAIN:
    case PS_FIRE0_CONFIG:
      this->setEffect(NO_EFFECT, TEXT_LAYER);
      this->setEffect(PARTICLE_SYSTEM, COLOR_LAYER);
      break;

    case CENTER_WAVE_CONFIG:
      this->setEffect(CENTER_PULSE, TEXT_LAYER);
      this->setEffect(WAVE0, COLOR_LAYER);
      break;

    case BOTTOM_BUBBLES_CONFIG:
      this->setEffect(SPECTRUM_LINE, TEXT_LAYER);
      this->setEffect(WAVE0, COLOR_LAYER);
      break;

    case DIFFUSION_TIME_CONFIG:
      this->setEffect(TIME_DOMAIN, TEXT_LAYER);
      this->setEffect(DIFFUSION, COLOR_LAYER);
      break;

  }
  effect[TEXT_LAYER]->setConfig(kConfig);
  effect[COLOR_LAYER]->setConfig(kConfig);
}

void Effects::nextEffect(uint8_t layer){
  cEffect[layer] = (++cEffect[layer]) % EFFECT_COUNT;
  this -> setEffect(cEffect[layer], layer);
}

void Effects::prevEffect(uint8_t layer){
  if(cEffect[layer] == 0){
    cEffect[layer] = EFFECT_COUNT - 1;
  }else{
    cEffect[layer] = (--cEffect[layer]) % EFFECT_COUNT;
  }
  this -> setEffect(cEffect[layer], layer);
}

void Effects::nextConfig(){
  cConfig = (++cConfig) % CONFIG_COUNT;
  this -> setConfig(cConfig);
}

void Effects::prevConfig(){
  if(cConfig == 0){
    cConfig = CONFIG_COUNT - 1;
  }else{
    cConfig = (--cConfig ) % CONFIG_COUNT;
  }
  this -> setConfig(cConfig);
}

void Effects::updateStrip(){
  uint8_t offset = 0;
  for(uint8_t idx = offset; idx< LED_COUNT; idx++){
    Pixel* pixel = sign.pixel(idx);
    strip.setPixelColor(idx-offset, pixel->color());
  }
}

void Effects::updateStrip(EffectData &data){
  if( data.pushLayer != CONFIG_LAYER){
    if(data.pushLayer == TEXT_LAYER){
      strip.setPixelColor(0, 0xFFFFFF);
    }else if( data.pushLayer == COLOR_LAYER){
      strip.setPixelColor(13, 0xFFFFFF);
    }else if( data.pushLayer == ADJUST_LAYER){
      strip.setPixelColor(14, 0xFFFFFF);
    }
  }
}
