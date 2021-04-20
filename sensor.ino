void checkSensor(){
  sensorLevel = ultrasonic.read();
  Serial.println(sensorLevel);
  connectWifi();
  announce(sensorLevel);
  if(sensorLevel < 10){
    digitalWrite(33,HIGH);
    delay(200);
    digitalWrite(33,LOW);
  } else {
    digitalWrite(32,HIGH);
    delay(200);
    digitalWrite(32,LOW);
  }
  bootCount++;
  Serial.println("Preparando para dormir");
  esp_deep_sleep_start();
}
