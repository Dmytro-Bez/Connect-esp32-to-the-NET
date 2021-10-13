#include<WiFi.h>

const int conf_size = 25;
char wifi_ssid[conf_size] = "";
char wifi_password[conf_size] = "";
const int max_connect_attempts = 10;                                            //variable repeat connect

bool connect_to_wifi(){
  bool wifi_status = false;
  int retries = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);
  while(WiFi.status() != WL_CONNECTED && retries < max_connect_attempts){       //Only try $max_connect_attempts times to connect to the WiFi
    delay(500);
    Serial.println(".");
    retries++;
  }
  Serial.println(".");
  if(WiFi.status() != WL_CONNECTED){                                            //If we still couldn't connect to the WiFi, go to deep sleep for a minute and try again.
    esp_sleep_enable_timer_wakeup(1 * 10L * 100000L);
    esp_deep_sleep_start();
    wifi_status = false;
  }
  Serial.println("Connect_wifi");
  return wifi_status;
}

void disconnect_to_wifi(){
  Serial.println("Disconnect_wifi");
  WiFi.disconnect();                                                            // Cut off the WIFI connection
  WiFi.softAPdisconnect();                                                      // We disconnect the access point (if it was)
  WiFi.mode(WIFI_OFF);                                                          // Off WIFI
}
