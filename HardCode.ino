#include <Servo.h>

// Assign Pin Connections and variables
const int solarPanelPin = A5;
const int servo1Pin = 9;
const int servo2Pin = 10;

//create floats for calculations
float volt;
float voltage1;
float voltage;
float current;
float resistance = 2;
float power;

// Create Servos
Servo servov;
Servo servoh;

// Create intervals for timers
const long analogInterval = 1000; // 30 seconds (changed for demonstration)
const long servoInterval = 10000; // 1 hour (changed for demonstration)

// Hard code array of angles
const int servo1Angles[] = {58,61, 58, 50, 40};
const int servo2Angles[] = {134, 105, 75, 53, 38};
const int numAngles = 5;

// Define variables analog value and the time
int analogValue;
unsigned long previousTime = 0;

void setup() {
  // Arduino setup
  Serial.begin(9600);

  // Attach the servo motors to the pins
  servov.attach(servo1Pin);//attach to pins
  servoh.attach(servo2Pin);//attach to pins
  servov.write(58); //initialize to first position
  servoh.write(134); //initialize to first position
}

void loop() {
  // Read analog value from the solar panel
    volt = analogRead(A5);
    voltage1 = (volt/1024)*5; //normalize because read is from 0 to 5 volts from 0-1023
    voltage = voltage1*(2); //calculates real voltage value from voltage divider circuit
    //current = (voltage/resistance); //used in testing and debugging
    //power = (current*voltage); //used in testing and debugging
    Serial.println(voltage); //prints voltage reading to serial monitor

  // Moves servo motors
  unsigned long currentTime = millis(); // set up timer
  //Serial.println(currentTime); //used for debugging/testing
  int hour = currentTime / 10000 % 5; // Calculate hour from 0 to 4
  int servo1Angle = servo1Angles[hour]; // Get angle for servo1 for current hour
  int servo2Angle = servo2Angles[hour]; // Get angle for servo2 for current hour
  if (currentTime - previousTime >= servoInterval && hour < numAngles) {
    previousTime = currentTime;
    servov.write(servo1Angle);
    servoh.write(servo2Angle);
  }//write angles to servo motor at proper time

  // Wait for 30 seconds to read analog value in loop
  delay(analogInterval);
}