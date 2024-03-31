long duration;
int distance;
const int trigPin = 4;                //UV sensor trigger pin to D4
const int echoPin = 5;                //UV sensor echo pin to D5
int LED = 13;                         //LED output pin to 13

void setup() {
  Serial.begin(9600);                 //initialize the SerialMonitor addressed "9600" to interact with you
  pinMode(trigPin, OUTPUT);           //Defining UV Sensor pin OUTPUT
  pinMode(echoPin, INPUT);            //Defining UV Sensor pin INPUT
  pinMode(LED, OUTPUT);               //Defining LED Pin Output
}

void loop() {
  delay(2);
  digitalWrite(trigPin, HIGH);        //sends the signal from trigger pin
  delay(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);   //time interval till which echo pin recieves the signal

  /*Speed of Sound = 343m/sec and the sound covers twice the distance of the object.
  Therefore, distance = (time_interval) * 0.0343/2 ------> dist(in cm)*/
  distance = duration * 0.0343 / 2;      

  //printing Result on the SerialMonitor
  Serial.print("Distance: ");                           
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10) {                  //if distance less than 10cm
    digitalWrite(LED, HIGH);
    delay(2000);
  } else
    digitalWrite(LED, LOW);
  delay(300);
}
