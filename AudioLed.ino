//#include <Bounce2.h>
#include <Adafruit_WS2801.h>
#include <IRremote.h>
#define USE_RAW_VOLUME 1
//#define DEBUG

#include <AudioLed.h>
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

