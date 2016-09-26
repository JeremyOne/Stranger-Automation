void setup() {
  Serial.begin(115200);
  Serial.println(".");
  
  pinMode(BUILTIN_LED, OUTPUT);
  
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  //wifiManager.setTimeout(30);
  wifiManager.autoConnect();

  WiFi.printDiag(Serial);

  if(debugRadio){
    receiveSwitch.enableReceive(D2);
  }
  
  sendSwitch.enableTransmit(D1);
  sendSwitch.setPulseLength(185);
  //sendSwitch.setProtocol(1); //causes errors?
  sendSwitch.setRepeatTransmit(defaultRetrySend);

  //setup handlers
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/flicker", handleFlicker);
  server.on("/toggle", handleToggle);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");  
}

void loop() {

  //debug radio loopback code, if radios are working correctly it will echo what is sent
  if(debugRadio && receiveSwitch.available()) {
  //  Serial.print("Received: ");
  //  Serial.print(receiveSwitch.getReceivedValue());
  //  Serial.print(", bits: ");
  //  Serial.print(receiveSwitch.getReceivedBitlength());
  //  Serial.print(", delay: ");
  //  Serial.println(receiveSwitch.getReceivedDelay());
  //  receiveSwitch.resetAvailable();
  }

  server.handleClient();
}
