#include "CenterPulse.h"

#define SMOOTH_BASE 100

CenterPulse::CenterPulse(){
  locationX = 3;
  locationY = 2;
  //smoothing = 1;
}

void CenterPulse::run(Sign &sign, EffectData &data){
  sign.off();
  Pixel* pixel = sign.pixel(locationX, locationY);
  uint16_t value = map(data.volume, 0, data.maxVolume, 0, 0xFFFF);
  //uint16_t h0 = pixel->hue[0];
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
    case RIGHT: if(locationX < LED_WIDTH - 1){ ++locationX; } break;
    case LEFT: if(locationX > 0){ --locationX; } break;
    case UP: if(locationY < LED_HEIGHT - 1){ ++locationY; } break;
    case DOWN: if(locationY > 0){ --locationY; } break;
    //case UP: if(smoothing < SMOOTH_BASE){ ++smoothing;} break;
    //case DOWN: if(smoothing > 0){ --smoothing;} break;
  }
}
