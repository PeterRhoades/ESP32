#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti WiFiMulti;

void setup()
 {
 Serial.begin(9600);
  delay(10);
   wificonnect();
 }

void wificonnect()
 {  
 WiFiMulti.addAP("Galaxy A71", "Emcor1966!");
  WiFiMulti.addAP("VM6535101", "pzpt3DvVssfj"); 
   Serial.println();
   Serial.println();
   Serial.println("Waiting for WiFi... \n");
     
 while(WiFiMulti.run() != WL_CONNECTED) {
  Serial.print(".");
   delay(500);
 }
 Serial.print("WiFi connected: ");
  Serial.print(WiFi.SSID());
   Serial.print(".......");
    Serial.println(WiFi.localIP());
     Serial.println("");
      delay(500);
    }
     
void loop()
 {
if (WiFi.status() != WL_CONNECTED)
 {
 wificonnect();
 }
 Serial.print(WiFi.SSID());
  Serial.print(".......");
   Serial.println(WiFi.localIP());
    Serial.println("");
     delay(1000);
    }
