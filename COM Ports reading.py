import serial
from serial import Serial

mySerial = serial.Serial("COM4", 9600) #specify com port number
myData = mySerial.readline(1000)
print(myData)