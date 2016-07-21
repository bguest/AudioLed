#include <Adafruit_WS2801.h>
#include <IRremote.h>        /*DON'T FORGET TO SET DECODE_NEC 1*/
#define USE_RAW_VOLUME 0
#undef DEBUG

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

