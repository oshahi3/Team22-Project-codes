// code for accelerometer 

int xpin = A3;                
 int ypin = A2;                
 int zpin = A1; 
 int xvalue;
 int yvalue;
 int zvalue;

void setup()
{
   Serial.begin(9600);          // initialize the serial communications:
}


void loop()
{
  xvalue = analogRead(xpin);                              //reads values from x-pin & measures acceleration in X direction 
  int x = map(xvalue, 267, 400, -100, 100);               //maps the extreme ends analog values from -100 to 100 for our understanding
//ou need to replace the 267 & 400 value with your values from calibration
  float xg = (float)x/(-100.00);                          //converts the mapped value into acceleration in terms of "g"
  Serial.print(xg);                                       //prints value of acceleration in X direction
  Serial.print("g   ");                                   //prints "g"
   
  yvalue = analogRead(ypin);
  int y = map(yvalue, 272, 406, -100, 100);
  float yg = (float)y/(-100.00);
  Serial.print("\t");
  Serial.print(yg);
  Serial.print("g   "); 
 
  zvalue = analogRead(zpin);
  int z = map(zvalue, 277, 410, -100, 100);
  float zg = (float)z/(100.00);
  Serial.print("\t"); 
  Serial.print(zg);
  Serial.println("g   ");
  delay(100);
}
