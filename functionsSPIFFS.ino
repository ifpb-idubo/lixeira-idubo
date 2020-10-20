void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Escrevendo arquivo: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- Erro ao abrir caminho do arquivo");
        return;
    }
    if(file.print(message)){
        Serial.println("- Arquivo criado");
    } else {
        Serial.println("- Falha na criação do arquivo");
    }
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- Falha ao atualizar arquivo");
        return;
    }
    if(file.print(message)){
        Serial.println("- Atualização de aqrquivo concluida");
    } else {
        Serial.println("- Atualização falhou");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Lendo arquivo: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- Falha ao abrir o arquivo");
        return;
    }
    Serial.println("- leitura:");
    String tmp = String(path);
    if(tmp == "/nomerede.txt"){
      nomeRede = "";
      while(file.available()){
        nomeRede += char(file.read());
      }
      file.close();
      Serial.println(nomeRede);
    } else if(tmp == "/netpassword.txt"){
      senhaRede = "";
      while(file.available()){
        senhaRede += char(file.read());
      }
      file.close();
      Serial.println(senhaRede);
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

void verifyData(fs::FS &fs, const char * dirname, uint8_t levels){

    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
      Serial.println("- SPIFFS falhou");
      return;
    }
    
    Serial.printf("- Listando o diretorio: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- Falha ao abrir diretório");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - Não e um diretorio");
        return;
    }

    File file = root.openNextFile();
    if(!file) {
      Serial.println("- Sem dados de rede");
      hasNetwordData = false;
    } else {
      hasNetwordData = true;
    }
    while(file){
       Serial.print("ARQUIVO: ");
       Serial.print(file.name());
       Serial.print("\tTAMANHO: ");
       Serial.println(file.size());
       file = root.openNextFile();
    }
}

void deleteData(){
  deleteFile(SPIFFS, "/netssid.txt");
  deleteFile(SPIFFS, "/netpassword.txt");
}
