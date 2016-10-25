#!/usr/bin/env bash
cd ~/Documents/Arduino
ln -s $(pwd)/AudioLed/lib $(pwd)/libraries/AudioLed
cd ~/Documents/Arduino/libraries
git clone git@github.com:adafruit/Adafruit-WS2801-Library.git Adafruit_WS2801
git clone git@github.com:bguest/Arduino-IRremote.git
cd Arduino-IRremote
git checkout audioled
echo "Finished"
