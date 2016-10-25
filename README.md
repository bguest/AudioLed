# AudioLed
Board to drive a string of WS2801 chips using audio and a MSGEQ7

# Setup

## Attaching FTDI
The FTDI Cable plugs in under the 12v Power Connector. The FTDI Grounds are close to the center of
the board, the DTR is closer to the edge of the board.

If the power connector is in the upper right of the board facing up the FTDI pins will be

GND, GND, VCC, RXI, RXO, DTR

## Setting up Arduino and Compiling the Code (MAC)

1. Clone this repo to `~/Documents/Arduino` with `cd ~/Documents/Arduino && git clone git@github.com:bguest/AudioLed.git`
2. Change directory to AudioLED with `cd AudioLed`
3. Mod setup script `chmod +x setup.sh`
4. Run Setup `.\setup.sh` this will clone correct versions of `Adafruit_WS2801` and `Arduino-IRremote`
5. Download Arduino v1.6.6 (May not compile with later versions of Arduino)
6. Launch Arduino v1.6.6
7. Open AudioLED
8. Set board to `Arduino Pro or Pro Mini`
9. Set processor to `ATmega328 (5V, 16MHz)`
10. Verify and Upload Code
