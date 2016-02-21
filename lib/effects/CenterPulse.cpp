#include "CenterPulse.h"

CenterPulse::CenterPulse(){
  smoothing = 0xFF >> 1
}

void CenterPulse::run(Sign &sign, EffectData &data){
  sign.off();
  Pixel* pixel = sign.pixel(4, 3);
  uint16_t value = map(data.volume, 0, data.maxVolume, 0, 0xFFFF);
  uint16_t h0 = pixel->hue[0];
  pixel->hue[0] = (smoothing*value + (UINT8_MAX-smoothing)*h0 )/UINT8_MAX;
}

void CenterPulse::push(IrInput input){
  Effect::push(input);

  switch(input){
    case UP: if(smoothing < 0xFF){ ++smoothing;}
    case DOWN: if(smoothing > 0){ --smoothing;}
  }
}
