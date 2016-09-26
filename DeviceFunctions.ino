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


