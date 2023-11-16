/*
See https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md for details. 
ThingSpeak ( https://www.thingspeak.com ) Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
Copyright 2020, The MathWorks, Inc.
Folder ESP32\Three Field Individual and Multiple Read
*/

#include <WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
char ssid[] = "VM6535101";   // your network SSID (name) 
char password[] = "pzpt3DvVssfj";   // your network password
WiFiClient  client;
unsigned long WriteChannelNumber = 1396346;
const char * WriteAPIKey = IOKJYS8558STU0YW;
unsigned long ChannelNumber = 1341661;
const char * ReadAPIKey = "PJPXZGAIKRFQUC8R";
int field[8] = {1,2,3,4,5,6,7,8};

void setup() {
  Serial.begin(9600);  //Initialize serial
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
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
  Serial.print(WiFi.SSID());
   Serial.print(".......");
    Serial.println(WiFi.localIP());
     Serial.println("");
    Serial.println("Three Field Individual and Multiple Read:");
  Serial.println('\n'); 
 delay(500);
 }

void loop() 
 {
 Serial.println ("Three Field Individual Read");
  float tempC = ThingSpeak.readFloatField(ChannelNumber, field[0], ReadAPIKey);  
   Serial.print(tempC); Serial.println ("°C");
    float humiD = ThingSpeak.readFloatField(ChannelNumber, field[1], ReadAPIKey);  
     Serial.print(humiD); Serial.println ("%");
     float presU = ThingSpeak.readFloatField(ChannelNumber, field[2], ReadAPIKey);  
    Serial.print(presU); Serial.println ("mBar\n");
   int statusCode = ThingSpeak.getLastReadStatus();
  Serial.print("Status Code "); Serial.println(statusCode); Serial.println("");
 delay(1000); 
   
 ThingSpeak.readMultipleFields(ChannelNumber, ReadAPIKey);
  Serial.println ("Three Field Multiple Read");
   float tempmC = ThingSpeak.getFieldAsFloat(field[0]); // Field 1
    float humiiD = ThingSpeak.getFieldAsFloat(field[1]); // Field 2
     float pressU = ThingSpeak.getFieldAsFloat(field[2]); // Field 3
      Serial.print(tempmC); Serial.println ("°C "); 
       delay(600);
        Serial.print(humiiD); Serial.println ("% "); 
       delay(600);
      Serial.print(pressU); Serial.println ("mBar\n"); 
    delay(600);
   statusCode = ThingSpeak.getLastReadStatus();
  Serial.print("Status Code "); Serial.println(statusCode); Serial.println("");
 delay(1000); 
}
