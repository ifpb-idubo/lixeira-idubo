void setarPinos(){
  pinMode(pinoVermelho, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(26, OUTPUT);

  for(int i=0;i<5;i++){
    digitalWrite(pinoVermelho,HIGH);
    delay(100);
    digitalWrite(pinoVermelho,LOW);
    delay(50);
  }
}
