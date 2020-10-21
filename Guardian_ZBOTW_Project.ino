/* A program to simulate a Zelda BOTW Guardian
  The servo will make some movements with a certain color again and again
  until the Ultrasonic sensor "see" someting close to it,
  then, it will move faster and the color will be Red/purple
*/

#include <Servo.h>

Servo myServo; // Create servo object

const byte ledR = 11; //PWM pin for Red color
const byte ledG = 5; //PWM pin for Green color
const byte ledB = 6; //PWM pin for Blue color

int trigPin = 12;    // Trig pin
int echoPin = 13;    // Echo pin
long duration, cm; //variables for measurements

//Brightness values
const byte maxBrightness = 250;
const byte medBrightness = 150;
const byte minBrightness = 50;

byte minDistance = 30; // min distance in cm to activate a sequence

//Delays values
const byte verySmallDelay = 2;
const byte smallDelay = 5;
const byte mediumDelay = 100;

volatile byte testVariableFWD = 0;
volatile byte testVariableRVS = 0;

void setup() {
  myServo.attach(3); // attach servo to PWM output

  pinMode(ledR, OUTPUT);//Pin mode for the Red Color
  pinMode(ledG, OUTPUT);//Pin mode for the Green Color
  pinMode(ledB, OUTPUT);//Pin mode for the Blue Color

  pinMode(trigPin, OUTPUT);// Pin for Ultrasonic sensor
  pinMode(echoPin, INPUT);// Pin for Ultrasonic sensor

  Serial.begin (9600); // Serial communication set-up

}//Close setup

void loop() {


  //Recover the cm value fro the User defined function
  cm = getTheDistance();

  if (cm >= minDistance) {

    digitalWrite(ledR, LOW);
    for (int pos = 0; pos <= 120; pos ++) {
      myServo.write(pos);
      delay(verySmallDelay);
    }//close for loop

    for (int i = 0; i < 250; i++) {
      analogWrite(ledB, i);
      analogWrite(ledG, i);
      delay(smallDelay);
    }

    for (int pos = 120; pos > 0; pos --) {
      myServo.write(pos);
      delay(verySmallDelay);
    }//close for loop

    for (int i = 250; i > 0; i--) {
      analogWrite(ledB, i);
      analogWrite(ledG, i);
      delay(smallDelay);
    }

  }//Close if stmnt

  else {

    for (int pos = 0; pos <= 120; pos ++ ) {
      myServo.write(pos);
      delay(verySmallDelay);
    }//close for loop

    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    digitalWrite(ledB, LOW);
    delay(verySmallDelay);


    for (int pos = 120; pos > 0; pos -- ) {
      myServo.write(pos);
      delay(verySmallDelay);
    }//close for loop

  }//close ELSE

}//Close Loop
/*-----User Defined Function-----
   Function Definition:
   getTheDistance

   Purpose:
   Apply the sequence to get the measurements from a Ultrasonic
   Sensor

   Return value:
   distance to know the range to activate or not a sequence
*/

int getTheDistance() {

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(10);

  return cm;

}
