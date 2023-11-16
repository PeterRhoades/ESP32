/*
See https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md for details. 
ThingSpeak ( https://www.thingspeak.com ) Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
Copyright 2020, The MathWorks, Inc.
Folder ESP32_ThinkSpeak_Read_One_Field
*/

#include <WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
char ssid[] = "VM5774222";   // your network SSID (name) 
char password[] = "b3rVddgtbvmp";   // your network password
WiFiClient  client;
unsigned long counterChannelNumber = 1696082;
const char * myCounterReadAPIKey = "GB08F126BLJOIPJW";
unsigned int counterFieldNumber = 1; 

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
  Serial.println(".....Connected to Home WiFi.....");
  Serial.println();
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println('\n'); 
  delay(500);
  Serial.println("Reciver nRF Data from Three Transmitters");
  Serial.println('\n'); 
 }

void loop() 
 {
  long count = ThingSpeak.readLongField(counterChannelNumber, counterFieldNumber, myCounterReadAPIKey);  
  int statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Channel ID: " + String(counterChannelNumber) + " Field:" + String(counterFieldNumber) + " " + String(count) + "°C");
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
  
  delay(3000); // No need to read the counter too often.
  
}
