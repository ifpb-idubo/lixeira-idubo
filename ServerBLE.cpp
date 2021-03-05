/*
  ServerBLE.cpp - Library for ESP32 board
  Created by Catalin Rizea, May 8, 2020
  Released into the public domain 
*/
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#include "ServerBLE.h"
#include "secret.h"

#define DESCRIPTOR_UUID BLEUUID((uint16_t)0x2901) // GATT Descriptor: Characteristic User Description

class Callback: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *characteristic) {
    std::string uuid = characteristic->toString();
    std::string value = characteristic->getValue();

    if (value.length() > 0) {
      if (uuid == CHARACTERISTIC_UUID_SSID) {
        Serial.print("\nNew SSID: ");
      } else if (uuid == CHARACTERISTIC_UUID_PASSWORD) {
        Serial.print("\nNew Password: ");
      }

      for (int i = 0; i < value.length(); i++) {
        Serial.print(value[i]);
      }
      Serial.println();
    }
  }
};

ServerBLE::ServerBLE() {}

void ServerBLE::start() {
  BLEDevice::init("Lixeira Idubo");
  this->_server = BLEDevice::createServer();

  BLEService *ssidService = this->createBLEWriteService(
    0,
    SERVICE_UUID_SSID,
    CHARACTERISTIC_UUID_SSID
  );

  BLEService *passwordService = this->createBLEWriteService(
    1,
    SERVICE_UUID_PASSWORD,
    CHARACTERISTIC_UUID_PASSWORD
  );

  ssidService->start();
  passwordService->start();

  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID_SSID);
  advertising->addServiceUUID(SERVICE_UUID_PASSWORD);
  advertising->setScanResponse(true);

  BLEDevice::startAdvertising();
  
  Serial.println("\nThe BLE server is ready!");
}

BLEService* ServerBLE::createBLEWriteService(
  byte type,  
  char* serviceUUID, 
  char* characteristicUUID
) {
  BLEService *service = this->_server->createService(serviceUUID);
  
  BLECharacteristic *characteristic = service->createCharacteristic(
    characteristicUUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE 
  );

  characteristic->setCallbacks(new Callback());

  switch (type) {
    case 1:
      this->_passwordCharacteristic = characteristic;
      break; 
    default:
      this->_ssidCharacteristic = characteristic;
      break;
  }

  return service;
}

std::string ServerBLE::getSSID() {
  return this->_ssidCharacteristic->getValue();
}

std::string ServerBLE::getPassword() {
  return this->_passwordCharacteristic->getValue();
}
