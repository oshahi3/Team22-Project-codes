//STILL HAVING ISSUES WITH LIBRARIES

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

#include <I2C.h>

#define ACCELEROMETER_ADDR 0x18 // Alternative: 0x19

static LIS331HH accelerometer{ACCELEROMETER_ADDR};


void setup()
{
Serial.begin(9600);

    I2c.begin();
    I2C.pullup(1);
    I2C.setSpeed(1); // 400 kHz
    I2C.timeOut(2000); // Reset communication when it's blocking the system for more than 2 seconds

    uint8_t err = accelerometer.setRebootMemoryContent(true); // Reset sensor register values to default
    print_err(err);
    bool rebootInProgress = true;
    while (rebootInProgress && err == E_OK) {
        err = accelerometer.getRebootMemoryContent(rebootInProgress);
    }
    err = accelerometer.setPowerMode(LIS331::PowerMode::normalMode);
    print_err(err);
    err = accelerometer.setDataRate(LIS331::DataRate::odr1000Hz);
    print_err(err);
    err = accelerometer.setBDUEnabled(true);
    print_err(err);
    err = accelerometer.setScale(LIS::Scale::scale24g);
    print_err(err);
    err = accelerometer.setAxisEnabled(LIS::Axis::X, true);
    print_err(err);
    err = accelerometer.setAxisEnabled(LIS::Axis::Y, true);
    print_err(err);
    err = accelerometer.setAxisEnabled(LIS::Axis::Z, true);
    print_err(err);
}
void loop()
{
    int16_t x = 0, y = 0, z = 0; // Raw values. To get them in [g] use `getAxisValuesG()`
    accelerometer.getAxisValue(LIS::Axis::X, x);
    accelerometer.getAxisValue(LIS::Axis::Y, y);
    accelerometer.getAxisValue(LIS::Axis::Z, z);

    bool xOverran = false, yEnabled = false, zAvailable = false;
    accelerometer.isAxisDataOverrun(LIS::Axis::X, xOverran);
    accelerometer.isAxisEnabled(LIS::Axis::Y, yEnabled);
    accelerometer.isAxisDataAvailable(LIS::Axis::Z, zAvailable);

    Serial.print(F("X: "));
    Serial.print(x);
    Serial.print(F(", Y: "));
    Serial.print(y);
    Serial.print(F(", Z: "));
    Serial.print(z);
    Serial.print(F(", X overran: "));
    Serial.print(xOverran);
    Serial.print(F(", Y enabled: "));
    Serial.print(yEnabled);
    Serial.print(F(", Z available: "));
    Serial.println(zAvailable);
}















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
