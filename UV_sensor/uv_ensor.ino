long duration;
int distance;
const int trigPin = 4;
const int echoPin = 5;
int LED = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;                      // time_interval * 0.034/2 ----> dist(in cm)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 10) {                            //if distance less than 10cm
    digitalWrite(LED, HIGH);
    delay(2000);
  } else
    digitalWrite(LED, LOW);
  delay(300);
}
