
#include "FireEmitter.h"
#include "Sign.h"

byte FireEmitter::baseHue = 128; //blues
byte FireEmitter::maxTtl = 128;

FireEmitter::FireEmitter()
{
    counter = 0;
    cycleHue = false;
}


void FireEmitter::emit(Particle &particle)
{
    counter++;
    if (cycleHue) baseHue = (counter>>2)%240;

    if (counter % 2 == 0) {
        particle.x = random(PS_MAX_X >> 2, 3 * (PS_MAX_Y >> 2));
        switch (particle.x / 32) {
        case 0:
        case 7:
            particle.ttl = random(1, 7);
            break;
        case 1:
        case 6:
            particle.ttl = random(5, 14);
            break;
        case 2:
        case 5:
            particle.ttl = random(15, 21);
            break;
        case 3:
        case 4:
            particle.ttl = random(25, 28);
            break;
        }
        particle.hue = (baseHue+16) << 8;
    } else {
        particle.x = random(PS_MAX_X);
        switch (particle.x / 32) {
        case 0:
        case 7:
            particle.ttl = random(1, 20);
            break;
        case 1:
        case 6:
            particle.ttl = random(5, 40);
            break;
        case 2:
        case 5:
            particle.ttl = random(20, 70);
            break;
        case 3:
        case 4:
            particle.ttl = random(40, 100);
            break;
        }
        particle.hue = baseHue << 8;
    }

    particle.y = 1;
    particle.typeMask = IS_DIEING_MASK;

    particle.vx = 0;
    particle.vy = 2;
    particle.mass = 0;

}

