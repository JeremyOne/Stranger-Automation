#include <RCSwitch.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

RCSwitch receiveSwitch = RCSwitch();
RCSwitch sendSwitch = RCSwitch();
ESP8266WebServer server(80);

//Codes to turn on the devices
int onCodes[] = {4281651, 4281795, 4282115, 4283651, 4289795};

//Codes to turn OFF the devices
int offCodes[] = {4281660, 4281804, 4282124, 4283660, 4289804};

//current state of devices, default to off
bool deviceState[] = {0, 0, 0, 0, 0};

int ledState = LOW;       //current diag led state
int deviceCount = 4;      //number of deives (zero index)
int nextPulse = 0;        //next millis of action
int nextCodeIndex = 0;  
int defaultRetrySend = 3;
int flickerRetrySend = 2;
int codeBitLength = 24;   //bits length of 433 codes 
bool debugRadio = false;  //enable radio receive debug

//using constant PROGMEM to save memory with this long html string, minified with: http://www.willpeavy.com/minifier/ from Default.html
const char htmlRoot[] PROGMEM = "<!DOCTYPE html><html lang='en'> <head> <meta charset='utf-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Stranger Automation</title> <link rel='stylesheet' href='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'> <script src='https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js'></script> <script src='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script> <script>$(document).ready(function(){$('.command').click(function(){$.ajax({url: $(this).attr('href')}); return false;});}); </script> </head> <body> <nav class='navbar navbar-inverse'> <div class='container'> <div class='navbar-header'> <a class='navbar-brand' href='/'>Stranger Automation</a> </div></div></nav> <div class='container'> <div class='panel panel-default'> <div class='panel-heading'> <h3 class='panel-title'>Toggle</h3> </div><div class='panel-body'> <p> <a href='toggle' class='command wide btn btn-warning' role='button'>All</a>&nbsp; <a href='toggle?id=0' class='command btn btn-info' role='button'>0</a>&nbsp; <a href='toggle?id=1' class='command btn btn-info' role='button'>1</a>&nbsp; <a href='toggle?id=2' class='command btn btn-info' role='button'>2</a>&nbsp; <a href='toggle?id=3' class='command btn btn-info' role='button'>3</a>&nbsp; <a href='toggle?id=4' class='command btn btn-info' role='button'>4</a>&nbsp; </p></div></div><div class='panel panel-default'> <div class='panel-heading'> <h3 class='panel-title'>Flicker</h3> </div><div class='panel-body'> <p> <a href='flicker' class='command btn btn-danger' role='button'>All</a>&nbsp; <a href='flicker?id=0' class='command btn btn-info' role='button'>0</a>&nbsp; <a href='flicker?id=1' class='command btn btn-info' role='button'>1</a>&nbsp; <a href='flicker?id=2' class='command btn btn-info' role='button'>2</a>&nbsp; <a href='flicker?id=3' class='command btn btn-info' role='button'>3</a>&nbsp; <a href='flicker?id=4' class='command btn btn-info' role='button'>4</a>&nbsp; </p></div></div><div class='panel panel-default'> <div class='panel-heading'> <h3 class='panel-title'>Flicker Long</h3> </div><div class='panel-body'> <p> <a href='flicker?count=200' class='command btn btn-danger' role='button'>All</a>&nbsp; <a href='flicker?id=0&count=80' class='command btn btn-info' role='button'>0</a>&nbsp; <a href='flicker?id=1&count=80' class='command btn btn-info' role='button'>1</a>&nbsp; <a href='flicker?id=2&count=80' class='command btn btn-info' role='button'>2</a>&nbsp; <a href='flicker?id=3&count=80' class='command btn btn-info' role='button'>3</a>&nbsp; <a href='flicker?id=4&count=80' class='command btn btn-info' role='button'>4</a>&nbsp; </p></div></div><div class='panel panel-default'> <div class='panel-heading'> <h3 class='panel-title'>Turn On</h3> </div><div class='panel-body'> <p> <a href='on' class='command wide btn btn-primary' role='button'>All</a>&nbsp; <a href='on?id=0' class='command btn btn-info' role='button'>0</a>&nbsp; <a href='on?id=1' class='command btn btn-info' role='button'>1</a>&nbsp; <a href='on?id=2' class='command btn btn-info' role='button'>2</a>&nbsp; <a href='on?id=3' class='command btn btn-info' role='button'>3</a>&nbsp; <a href='on?id=4' class='command btn btn-info' role='button'>4</a>&nbsp; </p></div></div><div class='panel panel-default'> <div class='panel-heading'> <h3 class='panel-title'>Turn Off</h3> </div><div class='panel-body'> <p> <a href='off' class='command btn btn-primary' role='button'>All</a>&nbsp; <a href='off?id=0' class='command btn btn-info' role='button'>0</a>&nbsp; <a href='off?id=1' class='command btn btn-info' role='button'>1</a>&nbsp; <a href='off?id=2' class='command btn btn-info' role='button'>2</a>&nbsp; <a href='off?id=3' class='command btn btn-info' role='button'>3</a>&nbsp; <a href='off?id=4' class='command btn btn-info' role='button'>4</a>&nbsp; </p></div></div></div></body></html>";


