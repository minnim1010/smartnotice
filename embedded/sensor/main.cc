#include <cstdio>
#include <cstring>
#include <mosquitto.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "../include/parson.h"
#include <cstdlib>
#include <ctime>

#define MOTION_DATA_FILE_PATH "../measure/get_motion_data/motion_data.txt"
#define GET_CO2_DATA_CMD "sudo python ../measure/get_co2_data/get_co2_data.py --co2valueonly"
#define GET_TEMP_DATA_CMD "python ../measure/get_temp_data/get_temp_data.py"
#define GET_LUX_DATA_CMD "python ../measure/get_lux_data/get_lux_data.py"
#define GET_OXY_DATA_CMD "python ../measure/get_oxygen_data/get_oxygen_data.py"

#define MQTT_HOST "3.34.185.128"
#define MQTT_PORT 1883
#define MQTT_TOPIC "sensor"
#define CLIENT_ID "010-0000-0002"
#define TRANSMISSION_INTERVAL 5
#define DEBUG 1

class Sensor
{
   private: 
      JSON_Value *root_value = json_value_init_object();
      JSON_Object *root_object = json_value_get_object(root_value);
      char measureTime[18];
      int action = 0;
      int lumnc = 0;
      double temp = 0;
      double oxy = 0;
      double co2 = 0;

   public:
      char *msg = NULL;
      void createMessage();
      void updateMeasureTime();
      void updateAction();
      void updateLumnc();
      void updateTemp();
      void updateOxy();
      void updateCo2();
      void setMessageValue();
      void releaseResources();
};

void Sensor::createMessage(){
    json_object_set_string(this->root_object, "client", CLIENT_ID);
    json_object_set_string(this->root_object, "measureTime", "");
    json_object_set_number(this->root_object, "action", 0);
    json_object_set_number(this->root_object, "lumnc", 0);
    json_object_set_number(this->root_object, "temp", 0);
    json_object_set_number(this->root_object, "oxy", 0);
    json_object_set_number(this->root_object, "co2", 0);
    this->msg = json_serialize_to_string_pretty(this->root_value);
}

/*
sensor publish message format:
{
   'client': '010-0000-0002',
   'measureTime': '2022-12-31 12:23:12',
   'action': 10,
   'lumnx': 100,
   'temp': 21.6,
   'oxy': 21.8,
   'co2': 0.3
}
*/
void Sensor::setMessageValue(){
    json_object_set_string(this->root_object, "measureTime", this->measureTime);
    json_object_set_number(this->root_object, "action", this->action);
    json_object_set_number(this->root_object, "lumnc", this->lumnc);
    json_object_set_number(this->root_object, "temp", this->temp);
    json_object_set_number(this->root_object, "oxy", this->oxy);
    json_object_set_number(this->root_object, "co2", this->co2);
   this->msg = json_serialize_to_string_pretty(this->root_value);
}

void Sensor::updateMeasureTime(){
   time_t timer;
   struct tm* t;
   timer = time(NULL);
   t = localtime(&timer);

   sprintf(this->measureTime, "%02d-%02d-%02dT%02d:%02d:%02d\0", 
      t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec
   );
}

void Sensor::updateAction(){
   std::string action;
   std::ifstream file (MOTION_DATA_FILE_PATH);
   if (file.is_open()){
      getline(file, action);
      file.close();
   }
   
   this->action = atoi(action.c_str());
}

void Sensor::updateLumnc(){
   std::string cmd(GET_LUX_DATA_CMD);
   std::string result;
   FILE* stream;
   const int maxBuffer = 10;
   char buffer[maxBuffer];

   cmd.append(" 2>&1");
   stream = popen(cmd.c_str(), "r");
   if (stream) {
    		while (fgets(buffer, maxBuffer, stream) != NULL) 
            result.append(buffer);
    		pclose(stream);
    	}
   else
      result.append("-1");

   if (DEBUG)
      std::cout << "lux: " << result << '\n';
   this->lumnc = atoi(result.c_str());
}

void Sensor::updateTemp(){
   std::string cmd(GET_TEMP_DATA_CMD);
   std::string result;
   FILE* stream;
   const int maxBuffer = 10;
   char buffer[maxBuffer];
   cmd.append(" 2>&1");

   stream = popen(cmd.c_str(), "r");
   if (stream) {
    		while (fgets(buffer, maxBuffer, stream) != NULL) 
            result.append(buffer);
    		pclose(stream);
    	}
   else
      result.append("-1");

   if (DEBUG)
      std::cout << "temp: " << result << '\n';
   this->temp = std::stod(result);
}

void Sensor::updateOxy(){
   std::string cmd(GET_OXY_DATA_CMD);
   std::string result;
   FILE* stream;
   const int maxBuffer = 10; // 버퍼의 크기는 적당하게
   char buffer[maxBuffer];
   cmd.append(" 2>&1"); // 표준에러를 표준출력으로 redirect

   stream = popen(cmd.c_str(), "r");
   if (stream) {
    		while (fgets(buffer, maxBuffer, stream) != NULL) 
            result.append(buffer);
    		pclose(stream);
    	}
   else
      result.append("-1");


   if (DEBUG)
      std::cout << "oxy: " << result << '\n';
   this->oxy = std::stod(result);
}

void Sensor::updateCo2(){
   std::string cmd(GET_CO2_DATA_CMD);
   std::string result;
   FILE* stream;
   const int maxBuffer = 10;
   char buffer[maxBuffer];
   cmd.append(" 2>&1");

   stream = popen(cmd.c_str(), "r");
   if (stream) {
    		while (fgets(buffer, maxBuffer, stream) != NULL) 
            result.append(buffer);
    		pclose(stream);
    	}
   else
      result.append("-1");

   if (DEBUG)
      std::cout << "co2: " << result << '\n';
   this->co2 = std::stod(result)*0.0001; //Change ppm to vol%
}

void Sensor::releaseResources(){
   if(!this->msg) json_free_serialized_string(this->msg);
   if(!this->root_value) json_value_free(this->root_value);
}

int main(int argc, char **argv) {
   Sensor sensor;
   struct mosquitto *mosq = NULL;
   sensor.createMessage();

   // init
   mosquitto_lib_init();

   // Create mosquitto instance
   mosq = mosquitto_new(NULL, true, NULL);
   if (!mosq) {
      perror("Can't initiallize mosquitto library\n");
      exit(-1);
   }

   if(mosquitto_username_pw_set(mosq, "user1", "user1") != MOSQ_ERR_SUCCESS){
      perror("Can't set username and password\n");
      exit(-1);
   }

   // Connect server, keep-alive = 0: sensor send message 5s
   int ret = mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 0);
   if (ret) {
      perror("Can't connect to mosquitto server\n");
      exit(-1);
   }

   while(1){
      sensor.updateMeasureTime();
      //sensor.updateAction();
      //sensor.updateLumnc();
      sensor.updateTemp();
      sensor.updateOxy();
      sensor.updateCo2();
      sensor.setMessageValue();
      printf("%s\n", sensor.msg);
      ret = mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(sensor.msg), sensor.msg, 0, false);
      
      if (DEBUG){
         if(ret == MOSQ_ERR_SUCCESS) printf("pulish success!\n");
         else printf("pulish failed!\n");
      }
      
      if (ret) {
         printf("Cant connect to mosquitto server\n");
         exit(-1);
      }
      
      sleep(TRANSMISSION_INTERVAL);
   }

   sensor.releaseResources();

   mosquitto_disconnect(mosq);
   mosquitto_destroy(mosq);
   mosquitto_lib_cleanup();

   return 0;
}
