#include <cstdio>
#include <stdint.h>
#include <cstring>
#include <mosquitto.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "../include/parson.h"
#include <cstdlib>
#include <ctime> 
#include <signal.h>

#define DEBUG 1
#define MQTT_HOST "3.34.185.128"
#define MQTT_PORT 1883
#define MQTT_TOPIC "announce"
#define VILLAGE 0
#define DISASTER 1
#define VILLAGE_INFO_FILE_PATH "/home/pi/smartnotice/broadcast/village/"
#define DISASTER_INFO_FILE_PATH "/home/pi/smartnotice/broadcast/disaster/"
#define VILLAGE_AUDIO_FILE_PATH "/home/pi/smartnotice/broadcast/audio/village/"
#define DISASTER_AUDIO_FILE_PATH "/home/pi/smartnotice/broadcast/audio/disaster/"
#define VOICE_DATA_NAME "voiceData"

using namespace std;

pid_t ppid;

class Announce {
    private:
        JSON_Value *root_value;
        JSON_Object *root_object;
        string announceTime;
        string status;
        string voiceData;
        string audio_file_path;
        string info_file_path;

    public:
        Announce(char *broadcastData);
        void parseJSONObject(char *broadcastData);
        void setFilePath();
        string decodeBase64(const string &in);
        void saveVoiceData();
        void saveBroadcastInfoFile();
        void output();
};

Announce::Announce(char *broadcastData) {
    root_value = json_value_init_object();
    root_object = json_value_get_object(root_value);

    this->root_value = json_parse_string(broadcastData);
    this->root_object = json_value_get_object(root_value);

    this->announceTime = json_object_get_string(root_object, "announceTime");
    this->announceTime[10] = '_';
    this->voiceData = json_object_get_string(root_object, "voiceData");
    this->status = json_object_get_string(root_object, "status");
}

string Announce::decodeBase64(const string &in) {
    typedef unsigned char uchar;
    static const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out; std::vector<int> T(256, -1);

    for (int i = 0; i < 64; i++)
        T[b[i]] = i;

    int val = 0, valb = -8;
    for (uchar c : in) {
        if (T[c] == -1)
            break;

        val = (val << 6) + T[c];
        valb += 6;

        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

// set the path that the voice data and info data saved
void Announce::setFilePath(){
    if(this->status == "NORMAL"){
        this->audio_file_path = string(VILLAGE_AUDIO_FILE_PATH) + this->announceTime + string(".mp3");
        this->info_file_path = string(VILLAGE_INFO_FILE_PATH) + this->announceTime + string(".json");
    }
    else if(this->status == "DISASTER"){
        this->audio_file_path = string(DISASTER_AUDIO_FILE_PATH) + this->announceTime + string(".mp3");
        this->info_file_path = string(DISASTER_INFO_FILE_PATH) + this->announceTime + string(".json");
    }
}

//output the saved voice data
void Announce::output(){
    string cmd("mpg123 ");
    cmd += this->audio_file_path;

    system(cmd.c_str());
}

void Announce::saveVoiceData(){
   ofstream writeFile;

    // base64 decode
    string voiceData(json_object_get_string(this->root_object, VOICE_DATA_NAME));
    string voiceDecodedData(decodeBase64(voiceData));

    if (DEBUG)
        cout << "fileName: " << this->audio_file_path << endl;
	
    writeFile.open(this->audio_file_path);
	if(writeFile.is_open())
		writeFile.write(voiceDecodedData.c_str(), voiceDecodedData.length());

	writeFile.close();
}

void Announce::saveBroadcastInfoFile(){

    std::ofstream writeFile;

    json_object_remove(this->root_object, VOICE_DATA_NAME);
    json_object_set_string(this->root_object, "VOICE_FILE_PATH", this->audio_file_path.c_str());

    string infoData(json_serialize_to_string_pretty(root_value));
    
    writeFile.open(this->info_file_path);
    
    if(writeFile.is_open())
        writeFile << infoData;

	writeFile.close();
}

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
   printf("connect callback, rc=%d\n", result);
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    if (DEBUG){
        printf("receive message(%s) : len %d\n",message->topic, message->payloadlen);
        printf("%s\n", message->payload);
    }

    Announce announce((char *)message->payload);
    announce.setFilePath();
    announce.saveVoiceData();
    announce.saveBroadcastInfoFile();
    announce.output();
}

int main(int argc, char *argv[])
{
   uint8_t reconnect = true;
   struct mosquitto *mosq;
   int rc = 0;

   mosquitto_lib_init();
   ppid = getppid();

    // create mosquitto client
   mosq = mosquitto_new(NULL, true, 0);

    // set username/password
   if(mosquitto_username_pw_set(mosq, "user1", "user1") != MOSQ_ERR_SUCCESS){
      perror("Can't set username and password\n");
      exit(-1);
   }

   if(mosq){
       if (DEBUG){
            mosquitto_connect_callback_set(mosq, connect_callback);     
       }
      
      mosquitto_message_callback_set(mosq, message_callback);

      rc = mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60); // connect to MQTT server
      mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 0); // subscribe to MQTT topic

      while(1){
         rc = mosquitto_loop(mosq, -1, 1);
         if(rc){
            printf("connection error!\n");
            sleep(10);
            mosquitto_reconnect(mosq);
         }
      }
      mosquitto_destroy(mosq);
   }

   mosquitto_lib_cleanup();

   return rc;
}
