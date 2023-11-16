
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
int kRecvPin = 25; //ESP32 InfaRad Working GIOP Pins=14,27,26,25,33,32,35,34,39,36
IRrecv irrecv(kRecvPin);
decode_results results;
LiquidCrystal_I2C lcd (0x23, 20, 4);
// Motor A
 int motor1Pin1 = 27; 
  int motor1Pin2 = 26; 
   int enable1Pin = 14; 
// Setting PWM properties
 const int freq = 4000;
  const int pwmChannel = 0;
   const int resolution = 8;
   int dutyCycle ;
//Motor Reversing 
 int Stop = 2;
  int Go = 1;
   int motorD = Go;

void setup() {
  Serial.begin(9600);
  lcd.begin(); //Turn on LCD:
  lcd.backlight();             
  irrecv.enableIRIn();  // Start the receiver
  Serial.println();
   pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
   pinMode(enable1Pin, OUTPUT);
   ledcSetup(pwmChannel, freq, resolution); //configure LED PWM functionalitites
    ledcAttachPin(enable1Pin, pwmChannel); //attach the channel to the GPIO to be controlled
     dutyCycle = 0;
    digitalWrite(motor1Pin1, HIGH);
   digitalWrite(motor1Pin2, LOW);
  Serial.print("IRrecv now running On ESP32, waiting for IR message on Pin ");
  Serial.println(kRecvPin);
  Serial.println("Folder ESP32/IR_ESP32_PWM_Case_Break");
  lcd.clear(); lcd.setCursor (0,0); lcd.print("IR Reciver Running");
               lcd.setCursor (0,2); lcd.print("      On ESP32");
 }

void loop() {
  if (irrecv.decode(&results)) // have we received an IR signal?
{
  switch(results.value)
{
  case 0xFF629D: Serial.print(results.value); 
                 dutyCycle = dutyCycle + 15; // Add to Motor PWM:
                 if (dutyCycle > 255) // Stop Motor PWM Going > 255:
                 {
                  dutyCycle = 255;
                 }
                 ledcWrite(pwmChannel, dutyCycle); 
                 Serial.print(" VOL+ PWM "); Serial.println(dutyCycle);
                  lcd.clear(); lcd.setCursor (0,0); lcd.print(" VOL+ PWM "); lcd.print(dutyCycle);
                  lcd.setCursor (7,2); lcd.print(results.value, HEX);
                 break;
  case 0xFFA857: Serial.print(results.value);
                 dutyCycle = dutyCycle - 15;
                 if (dutyCycle < 0) // Stop Motor PWM Going < 0:
                 {
                  dutyCycle = 0;
                 }
                 ledcWrite(pwmChannel, dutyCycle); 
                 Serial.print(" VOL- PWM "); Serial.println(dutyCycle);
                  lcd.clear(); lcd.setCursor (0,0); lcd.print(" VOL- PWM "); lcd.print(dutyCycle);
                  lcd.setCursor (7,2); lcd.print(results.value, HEX);
                 break;
  case 0xFF22DD: Serial.print(results.value); Serial.print(" |<< "); Serial.println(dutyCycle);
                  lcd.clear(); lcd.setCursor (0,0); lcd.print(" |<< "); lcd.print(dutyCycle);
                  lcd.setCursor (7,2); lcd.print(results.value, HEX);
                 digitalWrite(motor1Pin1, LOW);
                 digitalWrite(motor1Pin2, HIGH);   
                 break;
  case 0xFFC23D: Serial.print(results.value); Serial.print(" >>| "); Serial.println(dutyCycle);
                  lcd.clear(); lcd.setCursor (0,0); lcd.print(" >>| "); lcd.print(dutyCycle);
                  lcd.setCursor (7,2); lcd.print(results.value, HEX);
                 digitalWrite(motor1Pin1, HIGH);
                 digitalWrite(motor1Pin2, LOW); 
                 break;
  case 0xFF02FD: Serial.print(results.value); //Serial.print(" >|| "); 
                 if (motorD == Go){//Stop-Go Loop:
                  motorD = Stop;
                   digitalWrite(motor1Pin1, LOW);
                    digitalWrite(motor1Pin2, LOW);
                     Serial.print(" >|| PWM "); Serial.println(dutyCycle);
                      lcd.clear(); lcd.setCursor (0,0); lcd.print(" >|| PWM "); lcd.print(dutyCycle);
                      lcd.setCursor (7,2); lcd.print(results.value, HEX);
                      }else{
                     motorD = Go;
                    digitalWrite(motor1Pin1, HIGH);
                   digitalWrite(motor1Pin2, LOW);
                  Serial.print(" > PWM "); Serial.println(dutyCycle);
                   lcd.clear(); lcd.setCursor (0,0); lcd.print(" > PWM "); lcd.print(dutyCycle);
                   lcd.setCursor (7,2); lcd.print(results.value, HEX);
                  } 
                  delay(500);
                 break;
  case 0xFFE01F: Serial.print(results.value); Serial.println(" DOWN");    
                 break;
  case 0xFF906F: Serial.print(results.value); Serial.println(" UP");    
                 break;
  case 0xFF9867: Serial.print(results.value); Serial.println(" EQ");    
                 break;
  case 0xFFB04F: Serial.print(results.value); Serial.println(" ST/REPT");    
                 break;
  case 0xFF6897: Serial.print(results.value); Serial.println(" 0 PWM 0"); 
                 lcd.clear(); lcd.setCursor (0,0); lcd.print(" 0 PWM 0"); 
                 lcd.setCursor (7,2); lcd.print(results.value, HEX);
                 dutyCycle = 0;  
                  ledcWrite(pwmChannel, dutyCycle); 
                 break;
  case 0xFF30CF: Serial.print(results.value); Serial.println(" 1");    
                 break;
  case 0xFF18E7: Serial.print(results.value); Serial.println(" 2");    
                 break;
  case 0xFF7A85: Serial.print(results.value); Serial.println(" 3");    
                 break;
  case 0xFF10EF: Serial.print(results.value); Serial.println(" 4");    
                 break;
  case 0xFF38C7: Serial.print(results.value); Serial.println(" 5 PWM 155"); 
                 lcd.clear(); lcd.setCursor (0,0); lcd.print(" 5 PWM 155");
                 lcd.setCursor (7,2); lcd.print(results.value, HEX);
                 dutyCycle = 155;
                  ledcWrite(pwmChannel, dutyCycle);   
                 break;
  case 0xFF5AA5: Serial.print(results.value); Serial.println(" 6");    
                 break;
  case 0xFF42BD: Serial.print(results.value); Serial.println(" 7");    
                 break;
  case 0xFF4AB5: Serial.print(results.value); Serial.println(" 8");    
                 break;
  case 0xFF52AD: Serial.print(results.value); Serial.println(" 9 PWM 255");
                  lcd.clear(); lcd.setCursor (0,0); lcd.print(" 9 PWM 255"); 
                  lcd.setCursor (7,2); lcd.print(results.value, HEX);
                 dutyCycle = 255;
                 ledcWrite(pwmChannel, dutyCycle);   
                 break;
  case 0xFFA25D: Serial.print(results.value); Serial.println(" POWER"); 
                  lcd.clear(); lcd.setCursor (0,0); lcd.print("IR Reciver Running");
                  lcd.setCursor (0,2); lcd.print("      On ESP32");
                 break;
  case 0xFFE21D: Serial.print(results.value); Serial.println(" FUNC/STOP "); 
                 break;
  default: 
  int l = 0;//Serial.println(results.value); //Serial.println(" Repeat or other button   ");
}
  delay(100); // Do not get immediate repeat
  irrecv.resume();
 }
}
