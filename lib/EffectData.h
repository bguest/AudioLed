#ifndef EFFECT_DATA_H
#define EFFECT_DATA_H

#define UINT8_MAX 0xFF
#define UINT16_MAX 0xFFFF

struct EffectData{
  uint16_t tempo; // Period between taps
  bool shouldStep;
  uint8_t volume;
  uint16_t rawVolume;
  uint8_t maxVolume;
  uint8_t freqAmp[7];
};
#endif
