#include"f_wifi.h"              //Connect library wifi
#include"f_aws.h"               //Connect library aws
#include"f_ble.h"               //Connect library ble

bool connect_to_wifi();         //Prototipo funktion connect wifi
void disconnect_to_wifi();      //Prototipo funktion disconnect wifi
bool connect_to_aws();          //Prototipo funktion connect aws
void disconnect_to_aws();       //Prototipo funktion disconnect aws

void setup() {
  Serial.begin(115200);
  connect_to_wifi();
  //disconnect_to_wifi();

  connect_to_aws();
  //disconnect_to_aws();
}

void loop() {
  
}
