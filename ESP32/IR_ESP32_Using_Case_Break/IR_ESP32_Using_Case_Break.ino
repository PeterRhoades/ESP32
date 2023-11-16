
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
int kRecvPin = 33; //ESP32 InfaRad Working GIOP Pins=14,27,26,25,33,32,35,34,39,36
IRrecv irrecv(kRecvPin);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();  // Start the receiver
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
}

void loop() {
  if (irrecv.decode(&results)) // have we received an IR signal?
{
  switch(results.value)
{
  case 0xFFA25D: Serial.print(results.value); Serial.println(" POWER"); 
  break;
  case 0xFFE21D: Serial.print(results.value); Serial.println(" FUNC/STOP "); 
  break;
  case 0xFF629D: Serial.print(results.value); Serial.println(" VOL+"); 
  break;
  case 0xFF22DD: Serial.print(results.value); Serial.println(" |<<");    
  break;
  case 0xFF02FD: Serial.print(results.value); Serial.println(" >||");    
  break;
  case 0xFFC23D: Serial.print(results.value); Serial.println(" >>|");   
  break;
  case 0xFFE01F: Serial.print(results.value); Serial.println(" V ");    
  break;
  case 0xFFA857: Serial.print(results.value); Serial.println(" VOL-");    
  break;
  case 0xFF906F: Serial.print(results.value); Serial.println(" ^");    
  break;
  case 0xFF9867: Serial.print(results.value); Serial.println(" EQ");    
  break;
  case 0xFFB04F: Serial.print(results.value); Serial.println(" ST/REPT");    
  break;
  case 0xFF6897: Serial.print(results.value); Serial.println(" 0");    
  break;
  case 0xFF30CF: Serial.print(results.value); Serial.println(" 1");    
  break;
  case 0xFF18E7: Serial.print(results.value); Serial.println(" 2");    
  break;
  case 0xFF7A85: Serial.print(results.value); Serial.println(" 3");    
  break;
  case 0xFF10EF: Serial.print(results.value); Serial.println(" 4");    
  break;
  case 0xFF38C7: Serial.print(results.value); Serial.println(" 5");    
  break;
  case 0xFF5AA5: Serial.print(results.value); Serial.println(" 6");    
  break;
  case 0xFF42BD: Serial.print(results.value); Serial.println(" 7");    
  break;
  case 0xFF4AB5: Serial.print(results.value); Serial.println(" 8");    
  break;
  case 0xFF52AD: Serial.print(results.value); Serial.println(" 9");    
  break;
  default: 
  Serial.print(results.value); Serial.println(" Repeat or other button   ");
}
  delay(200); // Do not get immediate repeat
  irrecv.resume();
 }
}
