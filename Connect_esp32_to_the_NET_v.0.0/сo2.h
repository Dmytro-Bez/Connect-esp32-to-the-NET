#include <Wire.h>
#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

void init_ccs811(){
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
  //calibrate temperature sensor
  while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);
}

int send_ccs811(){
  float temp = ccs.calculateTemperature();
  if(!ccs.readData()){
    Serial.print("CO2: ");
    Serial.print(ccs.geteCO2());
    Serial.print("ppm, TVOC: ");
    Serial.print(ccs.getTVOC());
    Serial.print("ppb Temp:");
    Serial.println(temp);
  }
  return ccs.getTVOC();
}