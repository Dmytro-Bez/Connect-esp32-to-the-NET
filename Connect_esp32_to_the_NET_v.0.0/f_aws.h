#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "key.h"

#define DEVICE_NAME "DEV01"                                                       //The name of the device. This MUST match up with the name defined in the AWS console
#define AWS_IOT_ENDPOINT "..."                                                    //The MQTTT endpoint for the device (unique for each AWS account but shared amongst devices within the account)
#define AWS_IOT_TOPIC "/"+ DEVICE_NAME+ "/comand"                                 //The MQTT topic that this device should publish to
#define AWS_MAX_RECONNECT_TRIES 50 

void message_handler(String &topic, String &payload);

MQTTClient client = MQTTClient(256);
WiFiClientSecure net = WiFiClientSecure();

bool connect_to_aws(){
  bool aws_status = false;
  int retries = 0;
  
  net.setCACert(aws_cert_ca);                                                     //Configure WiFiClientSecure to use the AWS certificates we generated
  net.setCertificate(aws_cert_crt);
  net.setPrivateKey(aws_cert_private);
  client.begin(AWS_IOT_ENDPOINT, 8883, net);
  Serial.println("Connect to AWS IOT");
  while(!client.connect(DEVICE_NAME) && retries < AWS_MAX_RECONNECT_TRIES){
    Serial.println(".");
    delay(500);
    retries++;
  }
  if(!client.connected()){
    Serial.println("Timeout!");
  } else {
    Serial.println("Connect.");
    client.subscribe("/" DEVICE_NAME "/");
    client.onMessage(message_handler);
    aws_status = true;
  }
  return aws_status;
}

void disconnect_to_aws(){
  Serial.println("disconnect_aws");
  client.disconnect();
}

void message_handler(String &topic, String &payload){
  Serial.println("incoming: " + topic + " - " + payload);
}
