#include"f_wifi.h"
#include"f_aws.h"

bool connect_to_wifi();                                                         //Prototipo funktion connect wifi
void disconnect_to_wifi();
bool connect_to_aws();
void disconnect_to_aws();

void setup() {
  Serial.begin(115200);
  connect_to_wifi();
  //disconnect_to_wifi();

  connect_to_aws();
  //disconnect_to_aws();
}

void loop() {
  
}
