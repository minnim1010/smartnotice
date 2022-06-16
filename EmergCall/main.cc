#include <cstdio>
#include <cstring>
#include <mosquitto.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "../include/parson.h"
#include <cstdlib>

#define MQTT_HOST "3.34.185.128"
#define MQTT_PORT 1883
#define MQTT_TOPIC "emergency"
#define CLIENT "01072887522"

/*
mosquitto_pub -h 3.34.185.128 -p 1883 -t "emergency" -m "{\"client\": \"010-0000-0002\", \"emergency\": \"user\"}"
*/

int main(int argc, char **argv) {
   struct mosquitto *mosq = NULL;
   std::string msg("{\"client\": \"010-0000-0002\", \"emergency\": \"user\"}");

   mosquitto_lib_init();

   // create mosquitto client
   mosq = mosquitto_new(NULL, true, NULL);
   if (!mosq) {
      printf("Cant initiallize mosquitto library\n");
      exit(-1);
   }

   // set username/password
   if(mosquitto_username_pw_set(mosq, "user1", "user1") != MOSQ_ERR_SUCCESS){
      perror("Can't set username and password\n");
      exit(-1);
   }

   // connect to MQTT broker
   int ret = mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 0);
   if (ret) {
      printf("Cant connect to mosquitto server\n");
      exit(-1);
   }

   ret = mosquitto_publish(mosq, NULL, MQTT_TOPIC, msg.length(), msg.c_str(), 1, false);
   if (ret) {
      printf("Cant connect to mosquitto server\n");
      exit(-1);
   }

   printf("pulish success!\n");
   sleep(1);

   mosquitto_disconnect(mosq);
   mosquitto_destroy(mosq);
   mosquitto_lib_cleanup();

   return 0;
}
