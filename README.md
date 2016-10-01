# Stranger-Automation
A small project for automating a series of 433mhz mains automation plugs in the style of Stranger Things christmas lights

## Required Equipment
1x esp8266 microcontroller, any varation supported by [ESP8266-Arduino](https://github.com/esp8266/Arduino/), and any cables needed for flashing/programming

1x 433mhz receiver - generic, any version that can work with 3.3v logic [Sparkfun](https://www.sparkfun.com/products/10532), similar can be found on Amazon and ebay

1x 433mhz transmitter - generic, any version that can work with 3.3v logiv [Sparkfun](https://www.sparkfun.com/products/10534), similar can be found on Amazon and ebay

Any number of 433mhz wireless remote control outlets, I used these: [Amazon - Etekcity](https://www.amazon.com/-/dp/B00DQELHBS)

## Code Discovery
To discover the on/off codes required to run your outlets, wire the 433mhz receiver to the ESP8266, and set DebugRadio = 1; in StrangerAutomation.ino
Add discoverd codes to onCodes and offCodes arrays in StrangerAuotmation.ino

## Transmit Setup
Soon

## Debugging
Soon

##WiFi Setup
Soon

##Web Interface
Soon
