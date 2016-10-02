# Stranger-Automation
A small project for automating a series of 433mhz mains automation plugs in the style of Stranger Things christmas lights

## Required Equipment
1x esp8266 microcontroller, any varation supported by [ESP8266-Arduino](https://github.com/esp8266/Arduino/), and any cables needed for flashing/programming

1x 433mhz receiver - generic, any version that can work with 3.3v logic [Sparkfun](https://www.sparkfun.com/products/10532), similar can be found on Amazon and ebay

1x 433mhz transmitter - generic, any version that can work with 3.3v logic [Sparkfun](https://www.sparkfun.com/products/10534), similar can be found on Amazon and ebay

Any number of 433mhz wireless remote control outlets, I used these: [Amazon - Etekcity](https://www.amazon.com/-/dp/B00DQELHBS)

## Receive Setup
The 433hmz transmitter has three simple connections:
Gnd - Connect to any Gnd on the ESP
Data - Connect to any digital pin - I used D8
VCC - Cnnect to VIN on ESP

In StrangerAutomation.ino, set:

```
bool DebugRadio = 1;
long unsiged int receivePin = D8; //Or another chosen pin, some pins may work better than others
```

Upload the sketch to your ESP and start the serial monitor. 

Note: The wiFi manger script will attempt to connect your wifi each time you power on, you can use the web manger to connect now or later.

Once the seral monitor is running you can attempt to read the codes out of the air, use the remote that came with your outlets and toggle the aviable buttons. As codes are received they will immediately output to the seral monitor, if no codes appear check your wiring.

## Code Discovery
Once your receiver is working discover each on and off code for your outlets, the bit length and pulse length. 


Adjust the following in StrangerAuotmation.ino as needed:
```
int onCodes[] = {0000000, 2222222, 4444444, 6666666, 8888888};  //Codes to turn on the devices
int offCodes[] = {1111111, 3333333, 5555555, 7777777, 9999999}; //Codes to turn OFF the devices
int deviceCount = 4;                                            //number of devices (zero index)
int pulseLength = 185;
int codeBitLength = 24;
```


## Transmit Setup
Soon

## Debugging
Soon

##WiFi Setup
Soon

##Web Interface
Soon
