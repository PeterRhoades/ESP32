/*
See https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md for details. 
ThingSpeak ( https://www.thingspeak.com ) Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
Copyright 2020, The MathWorks, Inc.
Folder ESP32\Three Field Individual and Multiple Read
*/

#include <WiFi.h>
#include "ThingSpeak.h" //Thingspeak Header File:
char ssid[] = "VM6535101"; //WiFi Name:  
char password[] = "pzpt3DvVssfj"; //WiFi Pass Code:   
WiFiClient  client;
unsigned long WriteChannelNumber = 1396346; //Write Channel Number and API Key:
const char * WriteAPIKey = "IOKJYS8558STU0YW";
unsigned long ReadChannelNumber = 1341661; //Read Channel Number and API Key:
const char * ReadAPIKey = "PJPXZGAIKRFQUC8R";
int field[8] = {1,2,3,4,5,6,7,8}; //8 Field Array Only 3 Used:
int DL = 1000; //Delay Period:

void setup() 
{
Serial.begin(9600);  //Initialize Serial:
 WiFi.mode(WIFI_STA);   
 ThingSpeak.begin(client);  //Initialize ThingSpeak:
wificonnect();
 }

void wificonnect()
 {
 WiFi.begin(ssid, password);
  Serial.println(".....Conneting to Home WiFi.....");
   while(WiFi.status() != WL_CONNECTED){
  Serial.print("...");
 delay(500);  
 }
 Serial.println();
  Serial.print("WiFi Name:"); Serial.print(WiFi.SSID());
   Serial.print("   IP Address:");
    Serial.print(WiFi.localIP());
     Serial.print("   RRSI:");
      Serial.println(WiFi.RSSI());
     Serial.println("");
    Serial.println("Three Field Individual and Multiple Read Write:");
  Serial.println('\n'); 
 delay(5000);
 }

void loop() 
 {
 Individual(); //Three Field Individual Read Write:
 delay(2000);
 Multiple(); //Three Field Multiple Read Write
 delay(2000);
 }
 
 void Individual()
 {
 Serial.println ("Three Field Individual Read Summer House Write Mobil Scanner\n");
  float tempC = ThingSpeak.readFloatField(ReadChannelNumber, field[0], ReadAPIKey); //Field 1 Read:
   ThingSpeak.writeField(WriteChannelNumber, field[0], tempC, WriteAPIKey); //Field 1 Write:
    Serial.print("Temperature: "); Serial.print(tempC); Serial.println ("°C");
     float humiD = ThingSpeak.readFloatField(ReadChannelNumber, field[1], ReadAPIKey); //Field 2 Read:
      ThingSpeak.writeField(WriteChannelNumber, field[1], humiD, WriteAPIKey);  //Field 2 Write:
      Serial.print("Humidity:    "); Serial.print(humiD); Serial.println ("%");
     float presU = ThingSpeak.readFloatField(ReadChannelNumber, field[2], ReadAPIKey); //Field 3 Read:
    ThingSpeak.writeField(WriteChannelNumber, field[2], presU, WriteAPIKey); //Field 3 Write:
   Serial.print("Pressure:    "); Serial.print(presU); Serial.println ("mBar\n");
  int statusCode = ThingSpeak.getLastReadStatus();
if(statusCode == 200)
 {
 Serial.print("Status Code "); Serial.print(statusCode); Serial.println(" ThingSpeak Individual Read-Write Completed\n");
 } 
}
 
 void Multiple()
 {
 Serial.println ("Three Field Multiple Read Summer House Write Mobil Scanner\n");
  ThingSpeak.readMultipleFields(ReadChannelNumber, ReadAPIKey); //Read Fields 1,2,3, as Multiple:
   float tempC = ThingSpeak.getFieldAsFloat(field[0]); //Field 1 Read:
    float humiD = ThingSpeak.getFieldAsFloat(field[1]); //Field 2 Read:
     float presU = ThingSpeak.getFieldAsFloat(field[2]); //Field 3 Read:
      ThingSpeak.setField(field[3], tempC); //Field 4 Write:
       ThingSpeak.setField(field[4], humiD); //Field 5 Write:
       ThingSpeak.setField(field[5], presU); //Field 6 Write:
      ThingSpeak.writeFields(WriteChannelNumber, WriteAPIKey); //Write Fields 4,5,6, as Multiple:
     Serial.print("Temperature: "); Serial.print(tempC); Serial.println ("°C "); delay(DL); 
    Serial.print("Humidity:    "); Serial.print(humiD); Serial.println ("% "); delay(DL);
   Serial.print("Pressure:    "); Serial.print(presU); Serial.println ("mBar\n"); delay(DL);
  int statusCode = ThingSpeak.getLastReadStatus();
if(statusCode == 200)
 {
 Serial.print("Status Code "); Serial.print(statusCode); Serial.println(" ThingSpeak Multiple Read-Write Completed\n");
 } 
}
