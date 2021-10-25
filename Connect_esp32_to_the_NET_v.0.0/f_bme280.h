#ifndef bme280_h
#define bme280_h

#define SEALEVELPRESSURE_HPA (1013.25)

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

void read_date_bme280();
bool init_bme280();

Adafruit_BME280 bme; // I2C

void read_date_bme280() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    Serial.println();
}
bool init_bme280(){
  bool status;
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  return status;
}

#endif
