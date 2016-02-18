#ifndef AUDIO_LED_H
#define AUDIO_LED_H

#define IR_PIN A3
#define PLAY_PAUSE_IR 0x31F0E936
#define MENUE_IR      0xD14F58B0
#define UP_IR         0x17E1F858
#define DOWN_IR       0x8EBB3CFC
#define LEFT_IR       0xC26B4710
#define RIGHT_IR      0xFA0E2992
#define CENTER_IR     0x133620BA

#include "Sound.h"
#include "Effects.h"
#include "Tempo.h"
#include "EffectData.h"
#include "IRremote.h"

class AudioLed{
  public:
    AudioLed();
    void init();
    void run();

  private:
    Effects effects;
    Sound sound;
    Tempo tempo;
    EffectData data;

    IRrecv *irrecv;
    decode_results irResults;
    void handleIrCode(uint32_t irCode);
};

#endif
