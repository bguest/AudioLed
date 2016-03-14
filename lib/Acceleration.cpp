#include "Acceleration.h"

Acceleration::Acceleration(){
  ax = ay = 0;
  counter = 0;
}

void Acceleration::apply(Particle particals[], uint8_t particleCount){
  counter++;
  if(counter % 20 != 0){ return; }

  for(uint8_t i=0; i < particleCount; i++){
    particals[i].vx += ax;
    particals[i].vy += ay;
  }
}
