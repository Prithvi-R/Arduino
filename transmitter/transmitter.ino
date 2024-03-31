#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//transmitter
int xAxis = A0;
int yAxis = A1;
int xValue;
int yValue;
int data[2];

RF24 radio(8,9);  //CNS,CS

const byte address[6] = "hello";

void setup() {
  // put your setup code here, to run once:
  radio.begin();
  radio.openWritingPipe(address);  //hello
  radio.setPALevel(RF24_PA_MIN);    //comment
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  {
    xValue = analogRead(xAxis);
    xValue = map(xValue, 0, 1023, 0, 127);
    data[0] = xValue;
    radio.write(data, 1);
  }
  {
    yValue = analogRead(yAxis);
    yValue = map(yValue, 0, 1023, 128, 255);
    data[0] = yValue;
    radio.write(data, 1);
  }
}
