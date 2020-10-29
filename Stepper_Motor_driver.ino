/*
  Driver for NMB Technologies Stepper Motor
  Coil windings: Hybrid 4-phase
  This was written in Arduino 1.6.5,
  for an Arduino Mega 2560, 5V, 16MHz
  Daniel Gochnauer, 9/2/16
  
  List of functions (Table of contents)
   ------------------------------------
   void setup()
   void loop()
   
   As a rule, self made funtions are first letter capitalized,
   while self made variables are first letter lower case.
*/

//Mapping of coil phase -> color wire -> pin numbers
/*
    A  X  B
    | _|_ |
    |/   \|
       O   
    |\_ _/|
    |  |  |
    D  Y  C

    A - Red
    X - Black
    B - Orange
    C - Yellow
    Y - White
    D - Blue
*/

//Designate "kPin" prefix for assigning Ardunio pins
const byte kPinPhaseA = 31;
const byte kPinPhaseB = 33;
const byte kPinPhaseC = 35;
const byte kPinPhaseD = 37;

const byte kPinMotorPower = 49;
const byte kPinShutterState = 53;
bool ShutterState = LOW;

//Ground both Black (X) and White (Y) pins

void setup() {
  //Initialize pin settings
  pinMode(kPinMotorPower, OUTPUT);
  digitalWrite(kPinMotorPower, LOW);
  pinMode(kPinPhaseA, OUTPUT);
  digitalWrite(kPinPhaseA, LOW);
  pinMode(kPinPhaseB, OUTPUT);
  digitalWrite(kPinPhaseB, LOW);
  pinMode(kPinPhaseC, OUTPUT);
  digitalWrite(kPinPhaseC, LOW);
  pinMode(kPinPhaseD, OUTPUT);
  digitalWrite(kPinPhaseD, LOW);
  pinMode(kPinShutterState, INPUT);
  
  //Energize Phase A coils
  digitalWrite(kPinPhaseA, HIGH);
  delay(20);
  digitalWrite(kPinPhaseA, LOW);
  
  //Store initial shutter state
  ShutterState = digitalRead(kPinShutterState);
}

void loop() {
  //
  if(ShutterState != digitalRead(kPinShutterState))
  {
    ShutterState = digitalRead(kPinShutterState);
    
    digitalWrite(kPinMotorPower, HIGH);
    if(ShutterState == HIGH)
    {
      
      for(int inc=0; inc<25; inc++)
      {
        digitalWrite(kPinPhaseB, HIGH);
        digitalWrite(kPinPhaseA, LOW);
        delay(5);
        digitalWrite(kPinPhaseC, HIGH);
        digitalWrite(kPinPhaseB, LOW);
        delay(5);
        digitalWrite(kPinPhaseD, HIGH);
        digitalWrite(kPinPhaseC, LOW);
        delay(5);
        digitalWrite(kPinPhaseA, HIGH);
        digitalWrite(kPinPhaseD, LOW);
        delay(5);
      }
    }
    if(ShutterState == LOW)
    {
      for(int inc=0; inc<25; inc++)
      {
        digitalWrite(kPinPhaseD, HIGH);
        digitalWrite(kPinPhaseA, LOW);
        delay(5);
        digitalWrite(kPinPhaseC, HIGH);
        digitalWrite(kPinPhaseD, LOW);
        delay(5);
        digitalWrite(kPinPhaseB, HIGH);
        digitalWrite(kPinPhaseC, LOW);
        delay(5);
        digitalWrite(kPinPhaseA, HIGH);
        digitalWrite(kPinPhaseB, LOW);
        delay(5);
      }
    }
    digitalWrite(kPinMotorPower, LOW);
    digitalWrite(kPinPhaseA, LOW);
  }
  
  ShutterState = digitalRead(kPinShutterState);
  delay(10);
}



