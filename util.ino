void setPins(){
  pinMode(redLED, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(26, OUTPUT);

  for(int i=0;i<5;i++){
    digitalWrite(redLED,HIGH);
    delay(100);
    digitalWrite(redLED,LOW);
    delay(50);
  }
}
