#define HOME_SERVICE_UUID       "19B10000-E8F2-537E-4F6C-D104768A1214"                 //UUID BLE
#define SSID_CHARACTERISTIC_UUID "ec5397a2-0afe-4bd9-9403-0cd230976fa8"
#define PASSWORD_CHARACTERISTIC_UUID "1fc79774-fb73-453e-af23-61439d87a389"
#define INTERVAL_CHARACTERISTIC_UUID "4b411f8a-fcb8-11ea-adc1-0242ac120002" 
#define SWITCH_CHARACTERISTIC_UUID  "2dc43574-fb73-453e-af23-61439d87a389"


#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class MyServerCallbacks;                                            //Class connect and disconnect
class MyCallbacksSwitch;                                            //Class switch flag
class MyCallbacksSSID;                                              //Class formation loggin
class MyCallbacksPass;                                              //Class formation password
class MyCallbacksInterval;

class MyServerCallbacks: public BLEServerCallbacks{
  void onConnect(BLEServer* pServer){
    Serial.println("Connected BLE.");
  }
  void onDisconnect(BLEServer* pServer){
    Serial.println("Disconnected BLE.");
  }
};

class MyCallbacksInterval: public BLECharacteristicCallbacks{
  void onWrite(BLECharacteristic *pCharacteristic){
    std::string rxValue = pCharacteristic->getValue();
    if(rxValue.length() > 0){
      Serial.print("Period Received: ");
      //conf_interval = atoi(rxValue.c_str());
      //Serial.print(conf_interval);
      Serial.println();
    }
  }
};

class MyCallbacksSwitch: public BLECharacteristicCallbacks{
  void onWrite(BLECharacteristic *pCharacteristic){
    Serial.println("Switch");
//    a_status = BLE_OFF;
  }
};

class MyCallbacksSSID: public BLECharacteristicCallbacks{
  void onWrite(BLECharacteristic *pCharacteristic){
    std::string rxValue = pCharacteristic->getValue();
    if(rxValue.length() > 0){
      Serial.print("Login Received: ");
      for(int i = 0; i < rxValue.length(); i++){
//        conf_wifi_ssid[i]=rxValue[i];
      }
//      conf_wifi_ssid[rxValue.length()] = '\0';
//      Serial.print(conf_wifi_ssid);
      Serial.println();
    }
  }
};

class MyCallbacksPass: public BLECharacteristicCallbacks{
  void onWrite(BLECharacteristic *pCharacteristic){
    std::string rxValue = pCharacteristic->getValue();
    if(rxValue.length() > 0){
      Serial.print("Password received: ");
      for(int i = 0; i < rxValue.length(); i++){
//        conf_wifi_password[i]=rxValue[i];
      }
//      conf_wifi_password[rxValue.length()]='\0';
//      Serial.print(conf_wifi_password);
      Serial.println();
    }
  }
};

void init_ble() {
  BLEDevice::init("Home Sensor");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(HOME_SERVICE_UUID);
  
  BLECharacteristic *pCharacteristicSSID = pService->createCharacteristic(
                                         SSID_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristicSSID->setCallbacks(new MyCallbacksSSID());
  
  BLECharacteristic *pCharacteristicPass = pService->createCharacteristic(
                                         PASSWORD_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristicPass->setCallbacks(new MyCallbacksPass());
  
  BLECharacteristic *pCharacteristicInterval = pService->createCharacteristic(
                                         INTERVAL_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristicInterval->setCallbacks(new MyCallbacksInterval());
  
  BLECharacteristic *pCharacteristicSwich = pService->createCharacteristic(
                                         SWITCH_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristicSwich->setCallbacks(new MyCallbacksSwitch());
  pService->start();
  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(HOME_SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::getAdvertising()->start();

  Serial.println("Home Sensor BLE Service successfully create.");
}

void start_ble() {  
  init_ble();
  
  Serial.println("BLE mode is ON now.");
//  a_status = BLE_TRANSFERING;
}

void stop_ble(){
//  save_creds();
  ESP.restart();    
  Serial.println("BLE mode is OFF now.");
}
