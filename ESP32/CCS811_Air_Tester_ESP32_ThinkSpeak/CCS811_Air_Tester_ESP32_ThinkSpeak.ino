
#include "Adafruit_CCS811.h"
#include <WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
char ssid[] = "VM6535101";   // your network SSID (name) 
char password[] = "pzpt3DvVssfj";   // your network password
WiFiClient  client;
unsigned long WriteChannelNumber =  1396346;
const char * WriteAPIKey = "IOKJYS8558STU0YW";
float field[8] = {1,2,3,4,5,6,7,8};
Adafruit_CCS811 ccs;
int count = 0;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  wificonnect();
  Serial.println("CCS811 test");
  delay (1000);
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
 }
while(!ccs.available()); // Wait for the sensor to be ready
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
    Serial.println("CCS811_Air_Tester_ESP32_ThinkSpeak:");
  Serial.println('\n'); 
 delay(500);
 }
 
void loop()
{
 if(ccs.available()&&!ccs.readData()){
   Serial.print("CO2: ");
   Serial.println(ccs.geteCO2());
   Serial.print("ppp. TVOC: ");
   Serial.println(ccs.getTVOC());
   count++;
   Serial.print("Count=");
   Serial.println(count);
   Serial.println("");
  ThingSpeak.setField(1, ccs.geteCO2()); //Field 1 Write:
  ThingSpeak.setField(2, ccs.getTVOC()); //Field 2 Write:
  ThingSpeak.setField(3, count); //Field 3 Write:
  ThingSpeak.writeFields(WriteChannelNumber, WriteAPIKey);
  int statusCode = ThingSpeak.getLastReadStatus();
 
 if(statusCode == 200)
 {
 Serial.print("Status Code "); Serial.print(statusCode); Serial.println(" ThingSpeak CCS811 CO2 TVOC ESP32 Write Completed\n");
 delay(30000);
  }
 } 
}
