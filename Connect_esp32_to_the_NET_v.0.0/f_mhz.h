#define PIN_RX  16                           //Pin read data from mhz19
#define PIN_TX  17                           //Pin text data from mhz19

#include "mhz19.h"
#include "SoftwareSerial.h"
#include <Wire.h>

int co2;                                      //variable co2
int temp;                                     //variable temperature

static SoftwareSerial sensor(PIN_RX, PIN_TX);
static MHZ19 mhz19(&sensor);

int read_data_mhz19(){
  mhz19.readCO2(&co2, &temp);
  int a = co2 - 690;
  Serial.println(a);
  return a;
}
void init_mhz(){
  Wire.begin();
  sensor.begin(MHZ19::BIT_RATE);
}
