#include "CenterPulse.h"

#define SMOOTH_BASE 100

CenterPulse::CenterPulse(){
  smoothing = 1;
}

void CenterPulse::run(Sign &sign, EffectData &data){
  sign.off();
  Pixel* pixel = sign.pixel(3, 2);
  uint16_t value = map(data.volume, 0, data.maxVolume, 0, 0xFFFF);
  uint16_t h0 = pixel->hue[0];
  if(data.shouldStep){
    maxVal = maxVal/2;
  }
  if(value > maxVal){ maxVal = value;}
  pixel -> hue[0] = maxVal;
  //pixel->hue[0] = value;
  //pixel->hue[0] = smoothing*value/SMOOTH_BASE + (SMOOTH_BASE-smoothing)*h0/SMOOTH_BASE;
}

void CenterPulse::push(IrInput input){
  Effect::push(input);

  switch(input){
    case UP: if(smoothing < SMOOTH_BASE){ ++smoothing;} break;
    case DOWN: if(smoothing > 0){ --smoothing;} break;
  }
}
