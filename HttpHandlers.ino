void handleOn(){
  if(server.hasArg("id")){
    int id = server.arg("id").toInt();
    deviceOn(id);
  } else {
    allOn();
  }

  sendJson("status", "done");
}

void handleOff(){
  if(server.hasArg("id")){
    int id = server.arg("id").toInt();
    deviceOff(id);
  } else {
    allOff();
  }

  sendJson("status", "done");
}


void handleToggle(){
  if(server.hasArg("id")){
    int id = server.arg("id").toInt();
    deviceToggle(id);
  } else {
    allToggle();
  }

  sendJson("status", "done");
}

void handleFlicker(){
  int count = 50;
  sendSwitch.setRepeatTransmit(flickerRetrySend);
  
  if(server.hasArg("count")){
    count = server.arg("count").toInt();
  }
  
  if(server.hasArg("id")){
    int id = server.arg("id").toInt();
    deviceFlicker(id, count);
  } else {
    allFlicker(count);
  }
  
  sendSwitch.setRepeatTransmit(defaultRetrySend);
  sendJson("status", "done");
}

void handleRoot() {
  server.send(200, "text/html", FPSTR(htmlRoot));
}

void handleNotFound(){
  toggleLed();
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  
  server.send(404, "text/plain", message);
}
