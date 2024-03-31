#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

byte address[6] = "hello";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);  //1,address
  radio.setPALevel(RF24_PA_MIN);      //comment
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    const byte data[13];
    radio.read(&data,sizeof(data));
    Serial.print("Data Recieved: ");
    Serial.println(data);    
  }
}
