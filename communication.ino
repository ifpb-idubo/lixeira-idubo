void connectWifi(){
  WiFiClient client;
  readFile(SPIFFS, "/nomerede.txt");
  readFile(SPIFFS, "/senharede.txt");

  const char* savedSSID = ssid.c_str();
  const char* savedPassword = password.c_str();
  
  Serial.print("Conectando a rede: ");
  Serial.println(savedSSID);
  Serial.print("De senha: ");
  Serial.println(savedPassword);

  WiFi.mode(WIFI_STA);
  WiFi.begin(savedSSID, savedPassword);

  int cont = 0;
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("|");
    delay(200);
    cont++;
    if(cont==150){
      wipeData();
      for(int j=0;j<10;j++){
        digitalWrite(33,HIGH);
        delay(100);
        digitalWrite(33,LOW);
        delay(100);
      }
      ESP.restart();
    }
  }
  Serial.println();
  Serial.println("Conectado com sucesso.");
}

void announce(int value){
  DynamicJsonDocument doc(32);
  String payload = "";

  doc["sensor"] = value;
  serializeJson(doc, payload);
  
  String response = http.post("/sensor", payload);
  Serial.println(response);

  delay(1000);
}

void refreshSettings() {
  std::string bleSSID = server.getSSID();
  std::string blePassword = server.getPassword();

  if (bleSSID.length() == 0 || blePassword.length() == 0) {
    return;
  }

  Serial.print("SSID value: ");
  Serial.println(bleSSID.c_str());
  Serial.print("Passowrd value: ");
  Serial.println(blePassword.c_str());

  writeFile(SPIFFS, "/nomerede.txt", bleSSID.c_str());
  writeFile(SPIFFS, "/senharede.txt", blePassword.c_str());
  verifyFile(SPIFFS, "/", 0);
  connectWifi();
  digitalWrite(33, LOW);
  digitalWrite(32, HIGH);
  delay(1000);
  esp_deep_sleep_start();
}
