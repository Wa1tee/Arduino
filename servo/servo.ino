#include <Encoder.h>
#include <Servo.h> 

Encoder myEnc(D1, D2);

long oldPosition = -999;
boolean isButtonPressed = false;
long lastUpdateMillis = 0;


Servo myservo;

int servoPos = 100;

void handleKey(){
  isButtonPressed = true;
}

void sweepTest(){
  Serial.print("Testing servo.");
  
  int pos;
  for(pos = 20; pos <= 180; pos += 20)
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  Serial.print(".");
  for(pos = 200; pos>=20; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  Serial.print(".");
  delay(200);
  Serial.println("Servo sweep done."); 
}

void setup(){
  Serial.begin(115200);
  delay(10);
  
  pinMode(D3, INPUT_PULLUP);
  attachInterrupt(D3, handleKey, RISING);
  
  myservo.attach(16);
  sweepTest();
} 
 
void loop(){
  

  long newEncPos = myEnc.read();

  if(newEncPos > oldPosition){
    oldPosition = newEncPos;
    // Serial.println(newEncPos);
    servoPos += 1;
    Serial.println(servoPos);
    myservo.write(servoPos);
  }else if (newEncPos < oldPosition){
    oldPosition = newEncPos;
    // Serial.println(newEncPos);
    servoPos += -1;
    Serial.println(servoPos);
    myservo.write(servoPos);
  }
  if (isButtonPressed ){
    isButtonPressed = false;
    servoPos = 90;
    myservo.write(servoPos);
    Serial.print("Reset: ");
    Serial.println(servoPos);
  }
  
}