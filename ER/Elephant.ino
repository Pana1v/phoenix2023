#include <SoftwareSerial.h>
#include <Servo.h>
#include <HCSR04.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;
//Cytron_PS2Shield ps2; // HardwareSerial

#define LEDPIN 13
#define MotorDirection1 6
#define MotorSpeed4 7
#define MotorDirection4 8
#define MotorSpeed1 9
#define MotorDirection2 10
#define MotorSpeed2 11
#define MotorDirection3 3
#define MotorSpeed3 4
float target_height = 0;
float target_range = 0;
#include <SoftwareSerial.h>
String state;
int SpeedVal = 0;
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  
  //pinMode(LED, OUTPUT);
  //Serial.println("Ready to connect\nDefualt password is 1234 or 000");
  bool state_buzz = false;
  pinMode(MotorDirection1, OUTPUT);
  pinMode(MotorSpeed1, OUTPUT);

  pinMode(MotorDirection2, OUTPUT);
  pinMode(MotorSpeed2, OUTPUT);

  pinMode(MotorDirection3, OUTPUT);
  pinMode(MotorSpeed3, OUTPUT);
  pinMode(MotorDirection4, OUTPUT);
  pinMode(MotorSpeed4, OUTPUT);
}
void drive(int MS1, int MD1, int MS2, int MD2, int MS3, int MD3, int MS4, int MD4) {
  analogWrite(MotorSpeed1, MS1);
  digitalWrite(MotorDirection1, MD1);
  analogWrite(MotorSpeed2, MS2);
  digitalWrite(MotorDirection2, MD2);
  analogWrite(MotorSpeed3, MS3);
  digitalWrite(MotorDirection3, MD3);
  analogWrite(MotorSpeed4, MS4);
  digitalWrite(MotorDirection4, MD4);
}
void stop() {
  analogWrite(MotorSpeed1, 0);
  analogWrite(MotorSpeed2, 0);
  analogWrite(MotorSpeed3, 0);
  analogWrite(MotorSpeed4, 0);
}
void bp(String x) {
  Serial1.println(state);
  Serial.println(state);
}
// Initialize variables
float speed = 255;
int launch = 0;
int angle = 0;

void loop() {
  Serial1.print(state);
  //Serial.print("ss");
  speed = 254;
  while (Serial1.available()) {  //Check if there is an available byte to read
    delay(10);                   //Delay added to make thing stable
    char c = Serial1.read();     //Conduct a serial read
    state += c;
    //build the string- either "On" or "off"
  }
  if (state == "stop"||state.endsWith("stop")) stop();

  else if (state == "rear"||state.startsWith("rear")) {
    drive(speed, 0, speed, 0, speed, 0, speed, 0);
    Serial.println(speed);
  } 
  else if (state == "front"||state.startsWith("front")) 
  {
    analogWrite(MotorSpeed1, speed);
  digitalWrite(MotorDirection1, 1);
  analogWrite(MotorSpeed2, speed);
  digitalWrite(MotorDirection2, 1);
  analogWrite(MotorSpeed3, speed);
  digitalWrite(MotorDirection3,1);
  analogWrite(MotorSpeed4, speed);
  digitalWrite(MotorDirection4, 1);
  }

  else if (state == "left"||state.startsWith("left")) drive(speed, 0, speed, 1, speed, 0, speed, 1);

  else if (state == "right"||state.startsWith("right")) drive(speed, 1, speed, 0, speed, 1, speed, 0);
  else if (state == "lf"||state.startsWith("lf")) drive(speed, 1, 0, 0, speed, 1, 0, 0);
  else if (state == "rf"||state.startsWith("rf")) drive(0, 0, speed, 1, 0, 0, speed, 1);
  else if (state == "lr") drive(0, 0, speed, 0, 0, 0, speed, 0);
  else if (state == "rr") drive(speed, 0, 0, 0, speed, 0, 0, 0);

  else if (state == "lrot"||state.startsWith("lrot")) drive(speed, 1, speed, 1, speed, 0, speed, 0);
  //else if (state == "lrot"||state.startsWith("lrot")) drive(speed, 1, speed, 1, speed, 0, speed, 0);
  else if (state == "rrot"||state.startsWith("rrot")) drive(speed,0,speed,0,speed,1,speed,1);
 
  else if (state == "a")
    ;  //set target heights
  else if (state == "b")
    ;
  else if (state == "c")
    ;
  else if (state == "d")
    ;
  else if (state.toInt() <= 99 && state.toInt() >= 0) speed = map(state.toInt(), 0, 99, 0, 255);
  else if (state.toInt() <= 199 && state.toInt() >= 100) launch = map(state.toInt(), 199, 200, 0, 255);
  else if (state.toInt() <= 299 && state.toInt() >= 200) angle = state.toInt();
  else if (state == "buzz") {
    //  if (hc.dist() < 250) Serial.println("target aligned");
    //buzz is pole is aligned, give a short beep, calculate distance, approximate speed and angle
  }
  if (state.length() > 0) {
    Serial.println(state);
    Serial1.println(state);
    Serial.println(speed);
    state = "";
  }
}  //Reset the variable
