/*

# About program
This program detects the distance using proximity sensor and
based on distance value decides the direction of DC motor rotation.

###### Concept behind the project
Read from thesagarsutar.me/portfolio/intution

###### Requirements
1. Arduino Microcontroller
2. Ultrasonic Proximity Sensor
3. DC Motor
4. L293d Motor driver IC

*/

#include <NewPing.h>


#define MAX_DISTANCE 60

#define MOTOR1IN1 0
#define MOTOR1IN2 1
#define SEN1_TRIGGER_PIN  2
#define SEN1_ECHO_PIN     3
#define MOTOR2IN1 4
#define MOTOR2IN2 5
#define SEN2_TRIGGER_PIN  6
#define SEN2_ECHO_PIN     7
#define MOTOR3IN1 8
#define MOTOR3IN2 9
#define SEN3_TRIGGER_PIN  11
#define SEN3_ECHO_PIN     12

int motorStatus[4] = {0,0,0,0};

NewPing sen1(SEN1_TRIGGER_PIN, SEN1_ECHO_PIN, MAX_DISTANCE);
NewPing sen2(SEN2_TRIGGER_PIN, SEN2_ECHO_PIN, MAX_DISTANCE);
NewPing sen3(SEN3_TRIGGER_PIN, SEN3_ECHO_PIN, MAX_DISTANCE);

int distance1, distance2, distance3;

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR1IN1, OUTPUT);
  pinMode(MOTOR1IN2, OUTPUT);
  pinMode(MOTOR2IN1, OUTPUT);
  pinMode(MOTOR2IN2, OUTPUT);
  pinMode(MOTOR3IN1, OUTPUT);
  pinMode(MOTOR3IN2, OUTPUT);
  turnMotorAntiClockwise(2, 120);
  turnMotorOff(2);
  turnMotorClockwise(1, 120);
  turnMotorOff(1);
  turnMotorClockwise(3, 120);
  turnMotorOff(3);
}

void loop() {
  delay(70);
  long ran = random(70)%7;
  Serial.println(ran);
  if( ran == 2) {
    if(motorStatus[1] == 1) {
      distance1 = sen1.ping() / US_ROUNDTRIP_CM;
      Serial.print("[sensor1] start Ping: ");
      Serial.println(distance1);
      if((distance1!=0) && (distance1 > 7 && distance1 <= 40)) {
       onGesture(1);
      }
    }

    if(motorStatus[2] == 1) {
      distance2 = sen2.ping() / US_ROUNDTRIP_CM;
      Serial.print("[sensor2] start Ping: ");
      Serial.println(distance2);
      if((distance2!=0) && (distance2 > 7 && distance2 <= 40)) {
       onGesture(2);
      }
    }

    if(motorStatus[3] == 1) {
      distance3 = sen3.ping() / US_ROUNDTRIP_CM;
      Serial.print("[sensor3] start Ping: ");
      Serial.println(distance3);
      if((distance3!=0) && (distance3 > 7 && distance3 <= 40)) {
       onGesture(3);
      }
    }
  }
}

void onGesture(int motorNumber) {
  int randNumber;
  do {
    randNumber = (int)random(1,4);
  }while(randNumber == motorNumber);


  Serial.println("Gesture");
  turnMotorClockwise(motorNumber, 120);
  turnMotorOff(motorNumber);
  //delay(2000);
  turnMotorAntiClockwise(randNumber, 120);
  turnMotorOff(randNumber);
}

void turnMotorOff(int motorNumber) {
  switch(motorNumber) {
    case 1:
      digitalWrite(MOTOR1IN1, LOW);
      digitalWrite(MOTOR1IN2, LOW);
      break;
    case 2:
      digitalWrite(MOTOR2IN1, LOW);
      digitalWrite(MOTOR2IN2, LOW);
      break;
    case 3:
      digitalWrite(MOTOR3IN1, LOW);
      digitalWrite(MOTOR3IN2, LOW);
      break;
  }

}

void turnMotorClockwise(int motorNumber, int dly) {
  switch(motorNumber) {
    case 1:
      digitalWrite(MOTOR1IN1, LOW);
      digitalWrite(MOTOR1IN2, HIGH);
      break;
    case 2:
      digitalWrite(MOTOR2IN1, LOW);
      digitalWrite(MOTOR2IN2, HIGH);
      break;
    case 3:
      digitalWrite(MOTOR3IN1, LOW);
      digitalWrite(MOTOR3IN2, HIGH);
      break;
  }
  motorStatus[motorNumber] = 0;
  delay(dly);
}

//take actuator out
void turnMotorAntiClockwise(int motorNumber, int dly) {
  switch(motorNumber) {
    case 1:
      digitalWrite(MOTOR1IN1, HIGH);
      digitalWrite(MOTOR1IN2, LOW);
      break;
    case 2:
      digitalWrite(MOTOR2IN1, HIGH);
      digitalWrite(MOTOR2IN2, LOW);
      break;
    case 3:
      digitalWrite(MOTOR3IN1, HIGH);
      digitalWrite(MOTOR3IN2, LOW);
      break;
  }
  motorStatus[motorNumber] = 1;
  delay(dly);
}
