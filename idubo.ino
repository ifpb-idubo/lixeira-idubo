#include "FS.h"
#include "ServerBLE.h"
#include "SPIFFS.h"
#include <Ultrasonic.h>
#include <WiFi.h>
#include <EasyHTTP.h>

#define FORMAT_SPIFFS_IF_FAILED true
#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP  300

ServerBLE server;

int sensorLevel;
Ultrasonic ultrasonic(12, 13);

bool isDataSaved = false;
RTC_DATA_ATTR int bootCount = 0;

String ssid = "";
String password = "";

String baseURL = "http://192.168.1.7:3000";

char* _;

EasyHTTP http(_, _);

void setup() {
  Serial.begin(115200);
  Serial.println("Boot numero: " + String(bootCount));
  if(esp_sleep_get_wakeup_cause() == 1) Serial.println("Forçado a acordar");

  http.setBaseURL(baseURL);

  verifyFile(SPIFFS, "/", 0);
  //wipeData();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  if(!isDataSaved) server.start();
  else checkSensor();
}

void loop() {
  if(!isDataSaved) {
    refreshSettings(); 
    delay(2000);
  }
}
