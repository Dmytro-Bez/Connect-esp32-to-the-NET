#ifndef hdc1080_h
#define hdc1080_h

#include <Wire.h>
#include "ClosedCube_HDC1080.h"

ClosedCube_HDC1080 hdc1080;

float read_data_hdc1080(){
  //=============================================HDC1080 test==============================//
  Serial.println("HDC1080 test: ");
  Serial.print("T:");
  float Temper = hdc1080.readTemperature();
  Serial.print(Temper);
  Serial.println("C");
  
  Serial.print("Rh:");
  float Humid = hdc1080.readHumidity();
  Serial.print(Humid);
  Serial.println("%");
  Serial.println("===============");
  return Temper;
  return Humid;
}

#endif
