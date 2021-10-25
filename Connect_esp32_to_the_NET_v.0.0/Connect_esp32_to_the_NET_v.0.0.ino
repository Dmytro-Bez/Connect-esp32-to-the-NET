#include"lib.h"

void setup() {
  Serial.begin(115200);
//  Wire.begin();
//  sensor.begin(MHZ19::BIT_RATE);
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
  delay(10000);
}
