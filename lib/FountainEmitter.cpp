
#include "FountainEmitter.h"

byte FountainEmitter::minLife = 50;
byte FountainEmitter::maxLife = 100;

FountainEmitter::FountainEmitter(){
    vx = 0;
    vy = 0;
    var = 5;
    _hVar = (var>>1);
    currHue = 0;

    source.typeMask = IS_BOUNCE_MASK;
    source.vx = 1;
    source.vy = 1;
    source.ttl = 10;
    source.x = PS_P_RADIUS*0;
    source.y = PS_P_RADIUS*2;
}


void FountainEmitter::emit(Particle &particle)
{
    source.update();

    particle.x = source.x;
    particle.y = source.y;
    particle.vx = vx + random(var)-_hVar;
    particle.vy = vy + random(var)-_hVar;

    //particle->ttl = random(20,100);
    particle.ttl = random(minLife, maxLife);
    currHue += random(0,300);
    particle.hue = currHue; 
    particle.typeMask = IS_DIEING_MASK;
}
