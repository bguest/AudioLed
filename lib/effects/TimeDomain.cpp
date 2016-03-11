#include "TimeDomain.h"

TimeDomain::TimeDomain(){
  lastStep = 0;
  currVolume = 0;
  for(uint8_t i=0; i< LED_WIDTH; i++){
    volume[i] = 0;
  }
  band = FREQ_COUNT;
}

const uint8_t PIXEL_HEIGHT = UINT8_MAX/LED_HEIGHT;

void TimeDomain::run(Sign &sign, EffectData &data){

  uint16_t maxVolume, freqVol;
  if(band == FREQ_COUNT){
    maxVolume = data.maxVolume;
    freqVol = data.volume;
  }else{
    maxVolume = data.maxFreqAmp[band];
    freqVol =  data.freqAmp[band];
  }
  if(freqVol > currVolume){ currVolume = freqVol; }

  unsigned long currMillis = millis();
  if(currMillis - lastStep < data.tempo/4){ return; }
  lastStep = currMillis;

  uint8_t vol = map(currVolume, 0, maxVolume, 0, UINT8_MAX);
  this->pushVolume(vol);
  currVolume = 0;

  sign.off();
  for(uint8_t i=0; i<LED_WIDTH; i++){
    uint8_t vol = volume[i]/2;
    if(vol < PIXEL_HEIGHT/2){ continue;}

    for(uint8_t j=0; j<LED_HEIGHT; j++){
      uint8_t pixelHeight = j*PIXEL_HEIGHT+PIXEL_HEIGHT/2;
      if( pixelHeight > ( UINT8_MAX_2 - vol ) &&
          pixelHeight < ( UINT8_MAX_2 + vol ) ){

        sign.pixel(i,j)->direction = Up;
      }

    }
  }

}

// +--+ 5: UINT8_MAX
// |  | 4: Volume/2 + UINT8_MAX/2
// +--+-3
// |  | 2
// +--+ 1
// |  | UINT8_MAX/2
// +--+
// |  |
// +--+-
// |  | UINT8_MAX/2 - Volume/2
// +--+ 0

void TimeDomain::push(IrInput input){
  Effect::push(input);
  switch(input){
    case LEFT: if(band > 0 ){ band--; } break;
    case RIGHT: if(band < FREQ_COUNT){ band++; } break;
  }
}

void TimeDomain::setConfig(uint8_t kConfig){
  switch(kConfig){
    case DIFFUSION_TIME_CONFIG:
      band = FREQ_COUNT;
  }
}

void TimeDomain::pushVolume(uint8_t vol){
  for(uint8_t i=LED_WIDTH-1; i > 0; i--){
    volume[i] = volume[i-1];
  }
  volume[0] = vol;
}

