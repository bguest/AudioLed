#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(){
  particleCount = MAX_PARTICLE_COUNT;
  emitter = &fireEmitter;
  counter = 0;
}

void ParticleSystem::reset(){
  particleCount = MAX_PARTICLE_COUNT;
  for(uint8_t i=0; i<MAX_PARTICLE_COUNT; i++){
    particles[i].ttl = 0;
  }
}

void ParticleSystem::setConfig(uint8_t kConfig){
  switch(kConfig){
    case PS_CENTER_FOUNTAIN:
      emitter = &fountainEmitter;
      particleCount = MAX_PARTICLE_COUNT;
      acceleration.ax = 0;
      acceleration.ay = 0;
      physics = &acceleration;
      break;

    case PS_FIRE0_CONFIG:
      fireEmitter.cycleHue = true;
      emitter = &fireEmitter;
      acceleration.ay = 1;
      physics = &acceleration;
      break;
  }
}

void ParticleSystem::run(Sign &sign, EffectData &data){
  counter++;
  if(counter % 2 != 0){ return;}

  this->update();
  physics->apply(particles, particleCount);
  this->render(sign);

}

void ParticleSystem::update(){
  for(int i = 0; i<particleCount; i++) {
    particles[i].update();
    if (particles[i].ttl == 0 ) {
      emitter->emit(particles[i]);
    }
  }
}

void ParticleSystem::render(Sign &sign){

    uint8_t row, col;
    uint16_t dx, dy;
    unsigned long tempVal;
    sign.off();
    sign.black();

    const uint8_t stepDown = 2;

    //go over particles and update matrix cells on the way
    for(int i = 0; i<particleCount; i++) {
      if (particles[i].ttl == 0) {
        continue;
      }

      dx = PS_P_RADIUS - (particles[i].x % PS_P_RADIUS);
      dy = PS_P_RADIUS - (particles[i].y % PS_P_RADIUS);

      //bottom left
      col = particles[i].x / PS_P_RADIUS;
      row = particles[i].y / PS_P_RADIUS;

      tempVal = ((unsigned long)dx*dy*particles[i].ttl)>>stepDown;
      addColor(sign, row, col, particles[i].hue, tempVal);

      //bottom right;
      col++;
      if (col < LED_WIDTH) {
        tempVal = ((unsigned long)(PS_P_RADIUS-dx)*dy*particles[i].ttl)>>stepDown;
        addColor(sign, row, col, particles[i].hue, tempVal);
      }

      //top right
      row++;
      if (col < LED_WIDTH && row < LED_HEIGHT) {
        tempVal = ((unsigned long)(PS_P_RADIUS-dx)*(PS_P_RADIUS-dy)*particles[i].ttl)>>stepDown; 
        addColor(sign, row, col, particles[i].hue, tempVal);
      }

      //top left
      col--;
      if (row < LED_HEIGHT) {
        tempVal = ((unsigned long)dx*(PS_P_RADIUS-dy)*particles[i].ttl)>>stepDown;
        addColor(sign, row, col, particles[i].hue, tempVal);
      }
    }

}

void ParticleSystem::addColor(Sign &sign, uint8_t row, uint8_t col, uint16_t hue, uint32_t value){
  Pixel* pixel = sign.pixel(col, row);
  pixel->push();
  pixel->hue[0] = hue;
  pixel->addValue(value);
}

