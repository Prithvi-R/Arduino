int IRSensor = 9;                                     //IR sensor output pin to D9
int LED = 13;                                         //LED output pin to 13
void setup() {
<<<<<<< HEAD
=======
  //put your setup code here, to run once:
>>>>>>> d0626f3f82085c44b2e91507836b7f8d9072f515
  pinMode(IRSensor, INPUT);                           //Defining IR Sensor pin INPUT
  pinMode(LED, OUTPUT);                               //Defining LED Pin Output
}

void loop(){
  int sensorStatus = digitalRead(IRSensor);           //Read the readings of IR Sesnor
  if (sensorStatus == 0)                              //Check if the pin high or not
  {
    digitalWrite(LED, LOW);                           //LED to LOW
  }
  else  {
    digitalWrite(LED, HIGH);                           //LED to High
  }
}