// code for accelerometer 

const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis 
int xVal, yVal, zVal;
void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
}

void loop() {
 xVal = digitalRead(xpin);
 int x = map(xVal, "%d", "%d", "%d", "%d");
 float xg = (float)x/(-100.00);
 Serial.print(xg);
 Serial.print("g     ");

 yVal = digitalRead(ypin);
 int y = map(yVal, "%d", "%d", "%d", "%d");
 float yg = (float)y/(-100.00);
 Serial.print("\t");
 Serial.print(yg);
 Serial.print("g     ");

zVal = digitalRead(zpin);
int z = map(zVal, "%d", "%d", "%d", "%d");
float zg = (float)z/(-100.00);
Serial.print("\t");
Serial.print(zg);
Serial.println("g     ");  
  delay(100);
}
