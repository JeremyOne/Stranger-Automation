# Stranger-Automation
A small project for automating a series of 433mhz mains automation plugs in the style of Stranger Things christmas lights

See an example of the lights running here: [YouTube - Stranger Automation](https://www.youtube.com/watch?v=LgupRClw0yk)

## Required Equipment
1x esp8266 microcontroller, any version supported by [ESP8266-Arduino](https://github.com/esp8266/Arduino/), and any cables needed for flashing/programming, and 2 free pins.

1x 433mhz receiver - generic, any version that can work with 3.3v logic [Sparkfun](https://www.sparkfun.com/products/10532), similar can be found on Amazon and ebay

1x 433mhz transmitter - generic, any version that can work with 3.3v logic [Sparkfun](https://www.sparkfun.com/products/10534), similar can be found on [Amazon](https://www.amazon.com/s/?field-keywords=433+mhz+transmitter) or [ebay](https://www.ebay.com/sch/i.html?_nkw=433+mhz+transmitter)

Any number of 433mhz wireless remote control outlets, I used these: [Amazon - Etekcity](https://www.amazon.com/-/dp/B00DQELHBS)

## Receiver Setup
The 433hmz receiver has three connections:
Gnd - Connect to any Gnd on the ESP
Data - Connect to any digital pin, D8 works well
VCC - Connect to VIN on ESP

Note: All digital pins on the ESP are 3.3v, but if the receiver's VCC is connected to 5v it will run and out logic at 5v. Many report no problems with this, and in my case it was not and issue, but your millage may vary.

[Finished Circut](https://github.com/JeremyOne/Stranger-Automation/blob/master/Docs/circut-finished-top.jpg?raw=true | width=100)

In StrangerAutomation.ino, set:

```
bool DebugRadio = 1;
long unsigned int receivePin = D8; //Or another chosen pin, some pins may work better than others
```

Upload the sketch to your ESP and start the serial monitor.

Note: The WiFi manger script will attempt to connect your wifi each time you power on, you can use the web manger to connect now or later.

Your setup may or may not require an antennas to send and receive reliably. For me, a simple solid core wire cut to 17CM and soldered to the TX and RX units worked great.

Once the serial monitor is running you can attempt to read the codes out of the air, use the remote that came with your outlets and toggle the available buttons. As codes are received they will immediately output to the serial monitor, if no codes appear check your wiring.

## Code Discovery
Once your receiver is working, use the serial monitor to discover the on and off code for each outlet. Also note the bit and pulse lengths.

Adjust the following lines in StrangerAuotmation.ino:
```
int onCodes[] = {0000000, 2222222, 4444444, 6666666, 8888888};  //Codes to turn on the devices
int offCodes[] = {1111111, 3333333, 5555555, 7777777, 9999999}; //Codes to turn OFF the devices
int deviceCount = 4;                                            //Number of devices (zero index)
int pulseLength = 185;                                          //The length of each pulse
int codeBitLength = 24;                                         //Number of total bits to send when padding is needed
```

Note: The system is not limited to 5 devices, you can have any number that work on the same pulse and bit length.

## Transmiter Setup
The 433hmz transmitter also has three connections:
Gnd - Connect to any Gnd on the ESP
Data - Connect to any digital pin - I used D0
VCC - Connect to VIN on ESP (Not 3.3v)

Adjust the following lines in StrangerAuotmation.ino:
```
long unsigned int transmitPin = D8;
int defaultRetrySend = 3;
int flickerRetrySend = 2;
```

Re-upload the sketch to the ESP and use the web interface to send commands to your outlets. If DebugRadio is still enabled, you should see echos of the sent codes in the serial monitor.

If your transmissions are not working at all, double check your wiring and your specified pulse length. If transmissions are working unreliably try increasing the retry count, adjusting or replacing your antenna.

Both TX and RX use the rc-switch library by sui77, for more info see [rc-switch](https://github.com/sui77/rc-switch).

## WiFi Setup
This project uses the WiFiManger library from, tzapu. If no wifi config exists in flash, it will create a WiFi network that provides a web interface to select and enter your SSID and key phrase.

For more info see: [WiFiManager](https://github.com/tzapu/WiFiManager)

## Web Interface
The web interface is a mobile friendly bootstrap interface that makes AJAX/REST style requests to the host ESP web server.
[Interface Screenshot](https://github.com/JeremyOne/Stranger-Automation/blob/master/Docs/web-screenshot.jpg)

## REST API

### /toggle
Toggles all outlets on, then off.

#### Optional parameters:
id - control one device only

### /flicker
randomly choose outlets to switch on or off as quickly as possible

#### Optional parameters:
id - control one device only

number - number of times to flicker (default 50)

### /on
Turns all outlets ON

#### Optional parameters:
id - control one device only

### /off
Turns all outlets OFF

#### Optional parameters:
id - control one device only
