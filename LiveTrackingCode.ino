#include <Servo.h>
//create servos
Servo vertical;
Servo horizontal;

//create resistor variables and analog reads
int analogPin_TR = 0;
int analogPin_TL = 1;
int analogPin_BL = 2;
int analogPin_BR = 3;
int read0 = 0;
int read1 = 0;
int read2 = 0;
int read3 = 0;

//create variables to read resistance values
int Vin = 5;
float Vout0 = 0;
float Vout1 = 0;
float Vout2 = 0;
float Vout3 = 0;
int R1 = 10000;
float TR = 0;
float TL = 0;
float BL = 0;
float BR = 0;

//create limits for servo motors
int servohLimitHigh = 200;
int servohLimitLow = 10;
int servovLimitHigh = 75;
int servovLimitLow = 15;

//set starting positions
int servoh = 100;
int servov = 45;

//create variables to read voltage from solar panel
float volt;
float voltage1;
float voltage;
float current;
float resistance = 2;
float power;


void setup() { //attach servos to pins
  Serial.begin(9600);
  vertical.attach(9);
  vertical.write(servov);
  horizontal.attach(10);
  horizontal.write(servoh);
  delay(100);
}

void loop() {


//below code used for debugging
// volt = analogRead(A5);
//   if (volt) {
//     voltage1 = (volt/1024)*5;
//     voltage = voltage1*(2);
//     current = (voltage/resistance);
//     power = ((current*voltage));
//     Serial.println(power);
//     delay(100);
//   }
  read0 = analogRead(analogPin_TR); //read the top right resistor
  if (read0) {
    Vout0 = read0 / 1024.0;
    TR = ((Vin / Vout0) - 1) * R1;
    // Serial.print("VoutTR: "); //used to read values of resistances
    // Serial.println(Vout0);
    // Serial.print("TR: ");
    // Serial.println(TR);
    // delay(10);
  }

  read1 = analogRead(analogPin_TL); //read the top left resistor
  if (read1) {
    Vout1 = read1 / 1024.0;
    TL = ((Vin / Vout1) - 1) * R1;
    // Serial.print("VoutTL: ");
    // Serial.println(Vout1);
    // Serial.print("TL: ");
    // Serial.println(TL);
    // delay(10);
  }
  read2 = analogRead(analogPin_BL); //read the bottom left resistor
  if (read2) {
    Vout2 = read2 / 1024.0;
    BL = ((Vin / Vout2) - 1) * R1;
    // Serial.print("VoutBL: ");
    // Serial.println(Vout2);
    // Serial.print("BL: ");
    // Serial.println(BL);
    // delay(10);
  }
  read3 = analogRead(analogPin_BR); //read the bottom right resistor
  if (read3) {
    Vout3 = read3 / 1024.0;
    BR = ((Vin / Vout3) - 1) * R1;
    // Serial.print("VoutBR: ");
    // Serial.println(Vout3);
    // Serial.print("BR: ");
    // Serial.println(BR);
    // delay(10);
  }

//average resistance values in order to know which direction to move
  unsigned int top_ave = ((TL + TR) / 2);
  unsigned int bottom_ave = ((BL + BR) / 2);
  unsigned int left_ave = ((BL + TL) / 2);
  unsigned int right_ave = ((BR + TR) / 2);
  // int tol = 0;
  // int dvert = top_ave - bottom_ave;
  // int dhoriz = left_ave - right_ave;
  // Serial.println(top_ave);
  // Serial.println(bottom_ave);
  // Serial.println(left_ave);
  // Serial.println(right_ave);
  


  // Changes horizontal position
  if (left_ave > right_ave) {
    servoh = servoh - 1; //moves servo left by one degree
    if (servoh < servohLimitLow) {
      servoh = servohLimitLow;
    }
  } else if (left_ave < right_ave) {
    servoh = servoh + 1; //moves servo right by one degree
    if (servoh > servohLimitHigh) {
      servoh = servohLimitHigh;
    }
  }
  horizontal.write(servoh);
  
  // Changes vertical position
  if (top_ave > bottom_ave) {
    servov = (servov - 1); // moves servo down by one degree
    if (servov < servovLimitLow) {
      servov = servovLimitLow;
    }

  } else if (top_ave < bottom_ave) {
    servov = servov + 1; //moves servo up by one degree
    if (servov > servovLimitHigh) {
      servov = servovLimitHigh;
    }
  }
  vertical.write(servov);
  //  }
  delay(100);

  volt = analogRead(A5); //reads analog voltage value
  if (volt) {
    voltage1 = (volt/1024)*5; //normalize to arudino input of 0 to 1023
    voltage = voltage1*(2); //voltage divider because max read is 5 volts from arduino
    //current = (voltage/resistance);
    //power = ((current*voltage));
    //Serial.println(power); //used to see power calculation in set up
    Serial.println(voltage); //prints voltage value to serial monitor
    
    delay(100);
  }
}