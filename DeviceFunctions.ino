RCSwitch receiveSwitch = RCSwitch();
RCSwitch sendSwitch = RCSwitch();
ESP8266WebServer server(80);
//Html used for root control page, stored using constant PROGMEM to save memory, minified with: http://www.willpeavy.com/minifier/ from Default.html in this repo
const char htmlRoot[] PROGMEM = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1'><title>Stranger Automation</title><link rel='stylesheet' href='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js'></script><script src='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script><script>$(document).ready(function(){$('.command').click(function(){$.ajax({url: $(this).attr('href')}); return false;});}); </script></head><body><nav class='navbar navbar-inverse'><div class='container'><div class='navbar-header'><a class='navbar-brand' href='/'>Stranger Automation</a></div></div></nav><div class='container'><div class='panel panel-default'><div class='panel-heading'><h3 class='panel-title'>Toggle</h3></div><div class='panel-body'><p><a href='toggle' class='command wide btn btn-warning' role='button'>All</a>&nbsp; <a href='toggle?id=0' class='command btn btn-info' role='button'>0</a>&nbsp; <a href='toggle?id=1' class='command btn btn-info' role='button'>1</a>&nbsp; <a href='toggle?id=2' class='command btn btn-info' role='button'>2</a>&nbsp; <a href='toggle?id=3' class='command btn btn-info' role='button'>3</a>&nbsp; <a href='toggle?id=4' class='command btn btn-info' role='button'>4</a>&nbsp; </p></div></div><div class='panel panel-default'><div class='panel-heading'><h3 class='panel-title'>Flicker</h3></div><div class='panel-body'><p><a href='flicker' class='command btn btn-danger' role='button'>All</a>&nbsp; <a href='flicker?id=0' class='command btn btn-info' role='button'>0</a>&nbsp; <a href='flicker?id=1' class='command btn btn-info' role='button'>1</a>&nbsp; <a href='flicker?id=2' class='command btn btn-info' role='button'>2</a>&nbsp; <a href='flicker?id=3' class='command btn btn-info' role='button'>3</a>&nbsp; <a href='flicker?id=4' class='command btn btn-info' role='button'>4</a>&nbsp; </p></div></div><div class='panel panel-default'><div class='panel-heading'><h3 class='panel-title'>Flicker Long</h3></div><div class='panel-body'><p><a href='flicker?count=200' class='command btn btn-danger' role='button'>All</a>&nbsp; <a href='flicker?id=0&count=80' class='command btn btn-info' role='button'>0</a>&nbsp; <a href='flicker?id=1&count=80' class='command btn btn-info' role='button'>1</a>&nbsp; <a href='flicker?id=2&count=80' class='command btn btn-info' role='button'>2</a>&nbsp; <a href='flicker?id=3&count=80' class='command btn btn-info' role='button'>3</a>&nbsp; <a href='flicker?id=4&count=80' class='command btn btn-info' role='button'>4</a>&nbsp; </p></div></div><div class='panel panel-default'><div class='panel-heading'><h3 class='panel-title'>Turn On</h3></div><div class='panel-body'><p><a href='on' class='command wide btn btn-primary' role='button'>All</a>&nbsp; <a href='on?id=0' class='command btn btn-info' role='button'>0</a>&nbsp; <a href='on?id=1' class='command btn btn-info' role='button'>1</a>&nbsp; <a href='on?id=2' class='command btn btn-info' role='button'>2</a>&nbsp; <a href='on?id=3' class='command btn btn-info' role='button'>3</a>&nbsp; <a href='on?id=4' class='command btn btn-info' role='button'>4</a>&nbsp; </p></div></div><div class='panel panel-default'><div class='panel-heading'><h3 class='panel-title'>Turn Off</h3></div><div class='panel-body'><p><a href='off' class='command btn btn-primary' role='button'>All</a>&nbsp; <a href='off?id=0' class='command btn btn-info' role='button'>0</a>&nbsp; <a href='off?id=1' class='command btn btn-info' role='button'>1</a>&nbsp; <a href='off?id=2' class='command btn btn-info' role='button'>2</a>&nbsp; <a href='off?id=3' class='command btn btn-info' role='button'>3</a>&nbsp; <a href='off?id=4' class='command btn btn-info' role='button'>4</a>&nbsp; </p></div></div></div></body></html>";
bool deviceState[] = {0, 0, 0, 0, 0}; //current state of devices, default to off
int ledState = LOW; //current state of the debug led

void toggleLed(){
  if (ledState == LOW){
    ledState = HIGH;
  } else {
    ledState = LOW;
  }

  digitalWrite(BUILTIN_LED, ledState);
}

void sendJson(String Title, String Message){
  toggleLed();

  String s = "[{key:'" + Title;
  s += "', value:'";
  s += Message;
  s += "'}]";

  server.send(200, "text/json", s);
}

void deviceOn(int deviceIndex){
    sendSwitch.send(onCodes[deviceIndex], codeBitLength);
    deviceState[deviceIndex] = 1;
}

void deviceOff(int deviceIndex){
    sendSwitch.send(offCodes[deviceIndex], codeBitLength);
    deviceState[deviceIndex] = 0;
}

void deviceToggle(int deviceIndex){
  if(deviceState[deviceIndex] == 0){
    deviceOn(deviceIndex);
  } else {
    deviceOff(deviceIndex);
  }
}

void deviceFlicker(int device, int count){
    for(int i = 0; i <= count; i++){
      deviceToggle(device);
      delay(random(1, 100));
    }
}

void allOn(){
  for(int i = 0; i <= 4; i++){
    sendSwitch.send(onCodes[i], codeBitLength);
    deviceState[i] = 1;
  }
}

void allOff(){
  for(int i = 0; i <= deviceCount; i++){
    sendSwitch.send(offCodes[i], codeBitLength);
    deviceState[i] = 0;
  }
}

void allToggle(){
    allOn();
    delay(10);
    allOff();
    delay(10);
}

void allFlicker(int count){
    for(int i = 0; i <= count; i++){
      deviceToggle(random(0,deviceCount));
      delay(1);
    }
}
