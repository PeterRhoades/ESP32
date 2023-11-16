// Motor A
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

// Setting PWM properties
const int freq = 4000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(motor1Pin1, OUTPUT); //sets the pins as outputs:
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  ledcSetup(pwmChannel, freq, resolution); //configure LED PWM functionalitites
  ledcAttachPin(enable1Pin, pwmChannel); //attach the channel to the GPIO to be controlled
  dutyCycle = 0;
  Serial.print("Testing DC Motor...");
  Serial.println(dutyCycle);
  delay(2000);
}

void loop() {
  
  // Stop the DC motor
  Serial.println("Motor stopped [LOW]");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(2000);
  
  // Move the DC motor forward at maximum speed
  Serial.print("Moving Forward "); Serial.println(155);
  ledcWrite(pwmChannel, 155);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  delay(4000);

  // Stop the DC motor
  Serial.println("Motor stopped [HIGH]");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, HIGH);
  delay(2000);

    // Move DC motor backwards at maximum speed
  Serial.print("Moving Backwards "); Serial.println(155);
  ledcWrite(pwmChannel, 155);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  delay(4000);

  // Stop the DC motor
  Serial.println("Motor stopped [LOW]");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(2000);

  // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  while (dutyCycle <= 255){
    ledcWrite(pwmChannel, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 0;
  delay(2000);

  // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  while (dutyCycle <= 255){
    ledcWrite(pwmChannel, dutyCycle);   
    Serial.print("Backward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 0;
  delay(2000);
}
