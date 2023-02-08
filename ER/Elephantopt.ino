#include <SoftwareSerial.h>

#include <HCSR04.h>

int pos = 0;

//#define LEDPIN 13
#define MotorDirection4 6
#define MotorSpeed4 7
#define MotorDirection1 8
#define MotorSpeed1 9
#define MotorDirection2 10
#define MotorSpeed2 11
#define MotorDirection3 3
#define MotorSpeed3 4
#define Motor1brake 22
#define Motor2brake 23
#define Motor3brake 24
#define Motor4brake 25
float target_height = 0;
float target_range = 0;

String state;
int SpeedVal = 0;
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  // pinMode(LED, OUTPUT);
  // Serial.println("Ready to connect\nDefualt password is 1234 or 000");
  bool state_buzz = false;
  pinMode(MotorDirection1, OUTPUT);
  pinMode(MotorSpeed1, OUTPUT);
  pinMode(MotorDirection2, OUTPUT);
  pinMode(MotorSpeed2, OUTPUT);
  pinMode(MotorDirection3, OUTPUT);
  pinMode(MotorSpeed3, OUTPUT);
  pinMode(MotorDirection4, OUTPUT);
  pinMode(MotorSpeed4, OUTPUT);
  pinMode(Motor1brake, OUTPUT);
  pinMode(Motor2brake, OUTPUT);
  pinMode(Motor3brake, OUTPUT);
  pinMode(Motor4brake, OUTPUT);
}
void drive(int MS1, int MD1, int MS2, int MD2, int MS3, int MD3, int MS4,int MD4) {
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
  digitalWrite(Motor1brake, HIGH);
  digitalWrite(Motor2brake, HIGH);
  digitalWrite(Motor3brake, HIGH);
  digitalWrite(Motor4brake, HIGH);

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
  // Serial.print("ss");
  while (Serial1.available()) {  // Check if there is an available byte to read
    delay(10);                   // Delay added to make thing stable
    char c = Serial1.read();     // Conduct a serial read
    state += c;
  }
  if (state=="stop")
    stop();

  else if (state.indexOf("rear") >= 0) {
    drive(speed, 0, speed, 0, speed, 0, speed, 0);
    Serial.println(speed);
  } 
   if (state=="front" )
    drive(speed, 1, speed, 1, speed, 1, speed, 1);
  else if (state.indexOf("right") >= 0)
    drive(speed, 0, speed, 1, speed, 0, speed, 1);

  else if (state.indexOf("left") >= 0)
    drive(speed, 1, speed, 0, speed, 1, speed, 0);
  else if (state.indexOf("lf") >= 0)
    drive(speed, 1, 0, 0, speed, 1, 0, 0);
  else if (state.indexOf("rf") >= 0)
    drive(0, 0, speed, 1, 0, 0, speed, 1);
  else if (state.indexOf("lr") >= 0)
    drive(0, 0, speed, 0, 0, 0, speed, 0);
  else if (state.indexOf("rr") >= 0)
    drive(speed, 0, 0, 0, speed, 0, 0, 0);

  else if (state.indexOf("lrot") >= 0)
    drive(speed, 1, speed, 1, speed, 1, speed, 1);
  else if (state.indexOf("rrot") >= 0)
    drive(speed, 1, speed, 1, speed, 0, speed, 0);
  else if (state.indexOf("a") >= 0)
    ;
  else if (state.indexOf("b") >= 0)
    ;
  else if (state.indexOf("c") >= 0)
    ;
  else if (state.indexOf("d") >= 0)
    ;
   else if (state.toInt() <= 99 && state.toInt() >= 0)
    speed = map(state.toInt(), 0, 99, 0, 255);
  else if (state.toInt() <= 199 && state.toInt() >= 100)
    launch = map(state.toInt(), 199, 200, 0, 255);
  else if (state.toInt() <= 299 && state.toInt() >= 200)
    angle = state.toInt();
     else if (state.indexOf("buzz") >= 0) {
    //  if (hc.dist() < 250) Serial.println("target aligned");
    // buzz is pole is aligned, give a short beep, calculate distance,
    // approximate speed and angle
  }
  if (state.length() > 0) {
    Serial.println(state);
    Serial1.println(state);
    Serial.println(speed);
    state = "";
  }
}  // Reset the variable