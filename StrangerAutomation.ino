#include <RCSwitch.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


//adjust these settings as needed ---
int onCodes[] = {4281651, 4281795, 4282115, 4283651, 4289795};  //Codes to turn on the devices
int offCodes[] = {4281660, 4281804, 4282124, 4283660, 4289804}; //Codes to turn OFF the devices
int deviceCount = 4;                                            //total number of devices minus one (zero index)

long unsigned int receivePin = D0;                              //data pin connected to receiver
long unsigned int transmitPin = D8;                             //data pin connected to transmitter
int pulseLength = 185;                                          //length of each pulse
int codeBitLength = 24;                                         //bits length of 433 codes

int defaultRetrySend = 3;                                       //number of times to resend commands
int flickerRetrySend = 2;                                       //number of times to resend in random flicker mode

bool debugRadio = false;                                        //enable to echo received codes to serial
