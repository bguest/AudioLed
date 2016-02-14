#include <Bounce2.h>
#include <AudioLed.h>
#include <Adafruit_WS2801.h>
#include <IRremote.h>

/*#define DEBUG*/

AudioLed audioLed;

void setup(){

  #ifdef DEBUG
  Serial.begin(9600);
  #endif

  audioLed.init();
}

void loop(){
  audioLed.run();
}

