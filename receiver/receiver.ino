#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//include lib


//include
const int motorForward = A1;
const int motorBackward = A2;
const int motorLeft = A3;
const int motorRight = A4;
int data[2];

RF24 radio( 8,9);  //CNS,CS

const byte address[6] = "hello";

void setup() {
  // put your setup code here, to run once:
  pinMode(motarForward, OUTPUt);
  pinMode(motarBackward, OUTPUt);
  pinMode(motarLeft, OUTPUt);
  pinMode(motarRight, OUTPUt);
  Serial.begin(9600);


  radio.begin();
  radio.openReadingPipe(0, address);  //1,address
  radio.setPALevel(RF24_PA_MIN);      //comment
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    radio.read(data,1);
    if(data[0]>1 && data[0]<51){
      digitalWrite(motorForward,LOW);
      digitalWrite(motarBackward,HIGH);
    }
    if(data[0]>52 && data[0]<76){
      digitalWrite(motorForward,LOW);
      digitalWrite(motarBackward,LOW);
    }
    if(data[0]>77 && data[0]<120){
      digitalWrite(motorForward,HIGH);
      digitalWrite(motarBackward,LOW);
    }
    
    if(data[0]>129 && data[0]<179){
      digitalWrite(motorLeft,HIGH);
      digitalWrite(motarRight,LOW);
    }
    if(data[0]>180 && data[0]<204){
      digitalWrite(motorLeft,LOW);
      digitalWrite(motarRight,LOW);
    }
    if(data[0]>205 && data[0]<255){
      digitalWrite(motorLeft,LOW);
      digitalWrite(motarRight,HIGH);
    }
  }
}
