#include"lib.h"

void init_ccs811();
int send_ccs811();

Adafruit_CCS811 ccs;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  sensor.begin(MHZ19::BIT_RATE);
  init_ccs811();
  init_mhz();
  hdc1080.begin(0x40);
  init_bme280();
  connect_to_wifi();
  //disconnect_to_wifi();

  connect_to_aws();
  //disconnect_to_aws();
}

void loop() {
  read_data_hdc1080();
  read_date_bme280();
  read_data_mhz19();
  send_ccs811();
  delay(10000);
}

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
