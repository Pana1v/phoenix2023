/*
5th February 2023
First implementation on ESP32
Brakes : To be tested
Encoder: Not Implemented Yet
*/

#include <BluetoothSerial.h>

String text = "";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
String state;
BluetoothSerial SerialBT;
#define MotorDirection4 27
#define MotorSpeed4 33
#define MotorDirection1 21
#define MotorSpeed1 22
#define MotorDirection2 23
#define MotorSpeed2 25
#define MotorDirection3 26
#define MotorSpeed3 32
#define Motor1brake 16
#define Motor2brake 17
#define Motor3brake 18
#define Motor4brake 19
float target_height = 0;
float target_range = 0,speed;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Elephant Robot"); //Bluetooth device name
   speed = 255;
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
;}

void drive(int MS1, int MD1, int MS2, int MD2, int MS3, int MD3, int MS4,
		   int MD4) {
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

  digitalWrite(Motor1brake, HIGH);
  digitalWrite(Motor2brake, HIGH);
  digitalWrite(Motor3brake, HIGH);
  digitalWrite(Motor4brake, HIGH);
  delay(100);
  digitalWrite(Motor1brake, LOW);
  digitalWrite(Motor2brake, LOW);
  digitalWrite(Motor3brake, LOW);
  digitalWrite(Motor4brake, LOW);
}
void bp(String x) {
  SerialBT.println(x);
  Serial.println(x);
}
// Initialize variables
int launch = 0;
int angle = 0;

void loop() {

  float s1 = speed, s2 = s1, s3 = s1, s4 = s1;
  //SerialBT.print(state);
  // Serial.print("ss");
  while (SerialBT.available()) {  // Check if there is an available byte to read
	delay(10);                   // Delay added to make thing stable
	char c = SerialBT.read();     // Conduct a serial read
	state += c;
  //state=readString();
  //state.trim();
	// build the string- either "On" or "off"
  }
	/*
		NAVIGATION CONTROLS
	*/
  if ( state == "stop" || state.endsWith("stop") || state.startsWith("stop"))
	stop();
  else if (state == "rear" || state.startsWith("rear")) {
	drive(speed, 0, speed, 0, speed, 0, speed, 0);
	Serial.println(speed);
  } else if (state == "front" || state.startsWith("front"))
	drive(speed, 1, speed, 1, speed, 1, speed, 1);
  else if (state == "right" || state.startsWith("right"))
	drive(224, 0, 211, 1, 222, 0, 255, 1);
  else if (state == "left" || state.startsWith("left"))
	drive(speed, 1, speed, 1, speed, 1, speed, 0);
  else if (state == "rrot" || state.startsWith("lrot"))
	drive(speed, 1, speed, 1, speed, 1, speed, 1);
  else if (state == "lrot" || state.startsWith("rrot"))
	drive(speed, 0, speed, 0, speed, 0, speed, 0);
  else if (state == "lf" || state.startsWith("lf"))
	drive(speed, 1, 0, 0, speed, 1, 0, 0);
  else if (state == "rf" || state.startsWith("rf"))
	drive(0, 0, speed, 1, 0, 0, speed, 1);
  else if (state == "lr" || state.startsWith("lr"))
	drive(0, 0, speed, 0, 0, 0, speed, 0);
  else if (state == "rr" || state.startsWith("rr"))
	drive(speed, 0, 0, 0, speed, 0, 0, 0);
	/*
		EXTRA MODES HERE
	*/
  else if (state == "a");
  else if (state == "b");
  else if (state == "c");
  else if (state == "d");
  //if(state="")continue;
  else if (state.toInt() <= 99 && state.toInt() >= 0) {
	speed = map(state.substring(8,state.length()).toFloat(), 0, 99, 0, 255);
	//Serial.print( speed);
  } else if (state.toInt() <= 199 && state.toInt() >= 100)
	launch = map(state.toInt(), 199, 200, 0, 255);
  else if (state.toInt() <= 299 && state.toInt() >= 200)
	angle = state.toInt();
  else if (state == "buzz") {
	//  if (hc.dist() < 250) Serial.println("target aligned");
	// buzz is pole is aligned, give a short beep, calculate distance,
	// approximate speed and angle
  }
  
  if (state.length() > 0) {
	Serial.println(state);
	SerialBT.println(state);
	//Serial.println(speed);
	state = "";
  }
}