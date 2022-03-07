#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>

int Data_Bus = 3;
int clock = 4;


void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 7);    // request 6 bytes from slave device #7

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
  }

  delay(500);
}
//
//void setup() {
//  // put your setup code here, to run once:
//  pinMode(Data_Bus, OUTPUT);
//
//}

//void loop() {
//  digitalWrite(clock, HIGH);
//  delay(1000);  
//  digitalWrite(Data_Bus, LOW); 
//  delay(1000);
//}
