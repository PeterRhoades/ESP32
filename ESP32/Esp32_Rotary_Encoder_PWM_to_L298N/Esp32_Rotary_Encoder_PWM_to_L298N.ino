/*
Folder Esp32_Rotary_Encoder_PWM_to_L298N
*/


#include "AiEsp32RotaryEncoder.h"
 #define ROTARY_ENCODER_A_PIN 32
  #define ROTARY_ENCODER_B_PIN 21
   #define ROTARY_ENCODER_BUTTON_PIN 25
    #define ROTARY_ENCODER_STEPS 4
     AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1, ROTARY_ENCODER_STEPS);
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
 int CW = 2;
  int CCW = 1;
   int motorD = CCW;

void IRAM_ATTR readEncoderISR()
{
 rotaryEncoder.readEncoder_ISR();//
}

void setup()
{
Serial.begin(9600);
 rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
   rotaryEncoder.setBoundaries(0, 255, false); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
    rotaryEncoder.setAcceleration(250);
     pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
   pinMode(enable1Pin, OUTPUT);
   ledcSetup(pwmChannel, freq, resolution); //configure LED PWM functionalitites
    ledcAttachPin(enable1Pin, pwmChannel); //attach the channel to the GPIO to be controlled
     dutyCycle = 0;
    digitalWrite(motor1Pin1, HIGH);
   digitalWrite(motor1Pin2, LOW);
  Serial.println("Rotary Encoder PWM Speed Control CW-> <-CCW ");
 delay(2000);
}

void loop()
{
 if (rotaryEncoder.encoderChanged())
{
 Serial.println(rotaryEncoder.readEncoder());
  ledcWrite(pwmChannel, rotaryEncoder.readEncoder());// Write Encoder Data to PWM
}
 if (rotaryEncoder.isEncoderButtonClicked())
  if (motorD == CCW)//CW to CCW Loop:
{
 motorD = CW;
  digitalWrite(motor1Pin1, LOW);
   digitalWrite(motor1Pin2, HIGH);
    Serial.print("CCW ");
     Serial.println(rotaryEncoder.readEncoder());
     }else{
    motorD = CCW;
   digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
 Serial.print("CW ");
Serial.println(rotaryEncoder.readEncoder());
 }
}
  
