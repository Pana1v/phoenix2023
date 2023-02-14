#include <Servo.h>
#include <SoftwareSerial.h>

#define emergencyStopButtonPin 2
#define IR_sensor_1_pin 3
#define IR_sensor_2_pin 4
#define IR_sensor_3_pin 5
#define actuatorPin 6
#define servoPin 9
#define bluetoothRxPin 10
#define bluetoothTxPin 11

Servo servo;
SoftwareSerial Bluetooth(bluetoothRxPin, bluetoothTxPin);
int ringsShot = 0;
bool emergencyStop = false;

void setup() {
  pinMode(emergencyStopButtonPin, INPUT_PULLUP);
  pinMode(IR_sensor_1_pin, INPUT);
  pinMode(IR_sensor_2_pin, INPUT);
  pinMode(IR_sensor_3_pin, INPUT);
  pinMode(actuatorPin, OUTPUT);
  servo.attach(servoPin);
  Bluetooth.begin(9600);
}

void loop() {
  if (!emergencyStop) {
    // Check for emergency stop button press
    if (digitalRead(emergencyStopButtonPin) == LOW) {
      emergencyStop = true;
      // Stop the actuator and servo
      digitalWrite(actuatorPin, LOW);
      servo.write(90);
    } else {
      // Read data from Bluetooth app
      if (Bluetooth.available() > 0) {
        String command = Bluetooth.readStringUntil('\n');
        // Process the command received from the Bluetooth app
        processCommand(command);
      }
      // Check for ring shots using IR sensors
      checkForRingsShot();
    }
  } else {
    // Check for emergency stop button release
    if (digitalRead(emergencyStopButtonPin) == HIGH) {
      emergencyStop = false;
    }
  }
}

void processCommand(String command) {
  if (command == "actuator_on") {
    // Turn on the actuator
    digitalWrite(actuatorPin, HIGH);
  } else if (command == "actuator_off") {
    // Turn off the actuator
    digitalWrite(actuatorPin, LOW);
  } else if (command.startsWith("servo_")) {
    // Set the angle of the servo
    int angle = command.substring(6).toInt();
    servo.write(angle);
  }
}

void checkForRingsShot() {
  int IR_sensor_1_value = digitalRead(IR_sensor_1_pin);
  int IR_sensor_2_value = digitalRead(IR_sensor_2_pin);
  int IR_sensor_3_value = digitalRead(IR_sensor_3_pin);
  if (IR_sensor_1_value == LOW) {
    ringsShot++;
  }
  if (IR_sensor_2_value == LOW) {
    ringsShot++;
