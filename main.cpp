#include <Arduino.h>

//variable definitions 
const int trigPin = 2;
const int echoPin = 4;
int far = 100;
int safe = 30; //full speed above this distance
const int m1 = 7;
const int m2 = 5;
const int m3 = 6;
long duration;
int distance;
const int r = 10;
const int y = 11;
const int g = 12;

void setup() {
  //set pinmodes
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);

  //add pinmode for LED 
  pinMode(r, OUTPUT);
  pinMode(y,OUTPUT);
  pinMode(g,OUTPUT);

  Serial.begin(9600); 
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(2000);

  if (distance > far)
  {
    analogWrite(m2,0);
    analogWrite(m1,255);

    //leds off
    digitalWrite(r, 0);
    digitalWrite(y, 0);
    digitalWrite(g, 0);
  }
  if (distance < safe)
  {
    //motor off, led on
    analogWrite(m1,0);
    analogWrite(m2,0);
    analogWrite(m3,0); 

    //all led's on 
    digitalWrite(r, 1);
    digitalWrite(y, 1);
    digitalWrite(g, 1);
  }
  else
  {
    int motor_speed = map(distance, 0, 100, 0, 255);
    //led controls 
    if ((distance<100) && (distance>=50))
    {
      //1 led on 
      digitalWrite(r, 0);
      digitalWrite(y, 0);
      digitalWrite(g, 1);
      ///motor
      analogWrite(m1,motor_speed);
    }
    else if ((distance<50) && (distance>=safe))
    {
     //2 leds on
     digitalWrite(r, 0);
     digitalWrite(y, 1);
     digitalWrite(g, 1);
     ///motor
      analogWrite(m1,motor_speed);
    }
     
  }
}