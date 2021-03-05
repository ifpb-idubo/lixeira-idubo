#include "ServerBLE.h"
#include <SimpleDHT.h>

SimpleDHT11 dht(21);
ServerBLE server;

void setup() {
  Serial.begin(115200);
  server.start();
}

void loop() {
  refreshSettings();

  delay(2000);
}

void refreshSettings() {
  std::string ssid = server.getSSID();
  std::string password = server.getPassword();

  if (ssid.length() == 0 || password.length() == 0) {
    return;
  }

  Serial.print("SSID value: ");
  Serial.println(ssid.c_str());
  Serial.print("Passowrd value: ");
  Serial.println(password.c_str());
}
