#include "Particle.h"


#define DECAY_CONSTANT 1

void Particle::update(){

  //Age
  if(ttl > 0 && (IS_DIEING_MASK & typeMask) > 0){
    ttl--;
  }

  //apply velocity
  if((IS_FIXED_MASK & typeMask) > 0){
    vx = 0;
    vy = 0;
    return;
  }

  // Bouncy
  if((IS_BOUNCE_MASK & typeMask) > 0){

    uint16_t newX, newY;
    if (y == 0 || y >= PS_MAX_Y) {
        vy = -1 * vy;
    }
    if (x == 0 || x >= PS_MAX_X) {
        vx = -1 * vx;
    }
    if (vx == 0 && vy == 0) {
        ttl = 0;
    } else {
        x = min(max(x + vx, 0), PS_MAX_X);
        y = min(max(y + vy, 0), PS_MAX_Y);
    }

  }else{

    uint16_t newX, newY;
    newX = x + vx;
    newY = y + vy;
    if(newX < 0 || newX > PS_MAX_X || newY < 0 || newY > PS_MAX_Y) {
      ttl = 0;
    } else {
      x = (uint16_t)newX;
      y = (uint16_t)newY;
    }

  }



}



