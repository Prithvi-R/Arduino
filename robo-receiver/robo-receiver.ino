#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define enA 2
#define in1 3
#define in2 4
#define enB 7
#define in3 5
#define in4 6

RF24 radio(8, 9);                // pin(CE, CSK)
const byte address[6] = "R6T9U"; // Unique Code that will be shared to you by the coordinators
char receivedData[32] = "";
int xAxis, yAxis, switchStatus;
int motorSpeedA = 0;
int motorSpeedB = 0;

Servo myservo;
int pos = 90;

void setup()
{
  myservo.attach(10);

  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop()
{
  if (radio.available())
  { // If the NRF240L01 module received data
    char data[3][6];
    radio.read(&data, sizeof(data)); // Recieve the data
    xAxis = atoi(data[0]);           // Convert the data to integer
    Serial.print("XAxis: ");
    Serial.print(xAxis);
    yAxis = atoi(data[1]);
    Serial.print("\tYAxis: ");
    Serial.print(yAxis);
    switchStatus = atoi(data[2]);
    Serial.print("\tSwitch Status: ");
    Serial.println(switchStatus);
    delay(60);
  }

  if (switchStatus == 0)
  {
    myservo.write(pos);
  }
  else
  {
    myservo.write(0);
  }

  if (yAxis < 470)
  { // Set Motor A and B backward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }
  else if (yAxis > 550)
  { // Set Motor A and B forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
  }
  else
  {
    // The motors wouldnt move for rest
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  if (xAxis > 550)
  {

    // int xMapped = map(xAxis, 550, 1023, 0, 255);  //Map the declining X-axis readings
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
  }
  else if (xAxis < 470)
  {

    // int xMapped = map(xAxis, 470, 0, 0, 255);     //Map the increasing X-axis readings
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
  }

  // Constraint the motorSpeed limits to valid range
  motorSpeedA = constrain(motorSpeedA, 0, 255);
  motorSpeedB = constrain(motorSpeedB, 0, 255);

  // Send signals to motors
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
}
