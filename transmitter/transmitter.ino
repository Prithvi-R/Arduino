#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//transmitter

const byte address[6] = "hello";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);  //hello
  radio.setPALevel(RF24_PA_MIN);    //comment
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  {
    byte data[13]="Hello World!";
    
    radio.write(&data,sizeof(data));
    Serial.print("Data Transferred: ");
    Serial.println(data);
  }
}
