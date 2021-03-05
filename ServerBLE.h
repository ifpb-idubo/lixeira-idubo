#ifndef ServerBLE_h
#define ServerBLE_h

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

class ServerBLE {
  public:
    ServerBLE();
    void start();
    std::string getSSID();
    std::string getPassword();
  private:
    BLEServer *_server;
    BLECharacteristic *_ssidCharacteristic;
    BLECharacteristic *_passwordCharacteristic;
    BLEService *createBLEWriteService(
      byte type,  
      char* serviceUUID, 
      char* characteristicUUID
    );
};

#endif
