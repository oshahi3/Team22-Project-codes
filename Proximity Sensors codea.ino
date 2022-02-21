int Data_Bus = 3;
int clock = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(Data_Bus, OUTPUT);

}

void loop() {
  digitalWrite(clock, HIGH);
  delay(1000);  
  digitalWrite(Data_Bus, LOW); 
  delay(1000);
}
