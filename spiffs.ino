void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Escrevendo arquivo: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- erro ao abrir arquivo para escrever");
        return;
    }
    if(file.print(message)){
        Serial.println("- arquivo escrito");
    } else {
        Serial.println("- falha na escritura");
    }
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- falha ao dar append");
        return;
    }
    if(file.print(message)){
        Serial.println("- append concluido");
    } else {
        Serial.println("- append falhou");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Lendo arquivo: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- falha ao abrir o arquivo");
        return;
    }
    Serial.println("- leitura:");
    String tmp = String(path);
    if(tmp == "/nomerede.txt"){
      ssid = "";
      while(file.available()){
        ssid += char(file.read());
      }
      file.close();
      Serial.println(ssid);
    } else if(tmp == "/senharede.txt"){
      ssid = "";
      while(file.available()){
        ssid += char(file.read());
      }
      file.close();
      Serial.println(ssid);
    }
    
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- Arquivo deletado");
    } else {
        Serial.println("- Falha ao deletar");
    }
}

void verifyFile(fs::FS &fs, const char * dirname, uint8_t levels){

    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
      Serial.println("SPIFFS falhou");
      wipeData();
      return;
    }
    
    Serial.printf("Listando o diretorio: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- falha ao abrir diretorio");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - nao e um diretorio");
        return;
    }

    File file = root.openNextFile();
    if(!file) {
      Serial.println("SEM ARQUIVO");
      isDataSaved = false;
    } else {
      isDataSaved = true;
    }
    while(file){
       Serial.print("ARQUIVO: ");
       Serial.print(file.name());
       Serial.print("\tTAMANHO: ");
       Serial.println(file.size());
       file = root.openNextFile();
    }
}

void wipeData(){
  deleteFile(SPIFFS, "/nomerede.txt");
  deleteFile(SPIFFS, "/senharede.txt");
}
