#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 
 
RF24 radio(8,9); // CE, CSK
 
const byte address[6] = "R6T9U";    //Unique Code
 
int xAxisValue = 0; 
int yAxisValue = 0; 
int switchStatus=0;

void setup() { 
  radio.begin(); 
  Serial.begin(115200); 
  radio.openWritingPipe(address); 
  radio.stopListening(); 
  pinMode(4, INPUT_PULLUP); 
} 
void loop() { 
  int xAxis = analogRead(A0);       //Read Joysticks X-axis 
  int yAxis = analogRead(A1);       //Read Joysticks X-axis 
  int switchStatus =digitalRead(4); //Read Button Pressed

  //Convert integer values to strings 
  String xString = String(xAxis); 
  String yString = String(yAxis); 
  String status = Sring(switchStatus);

  char data[3][6];                  //3 strings of 5 characters each(including null terminator) 
 
  xString.toCharArray(data[0], 6); 
  yString.toCharArray(data[1], 6); 
  status.toCharArray(data[2], 6);

  radio.write(&data, sizeof(data)); 
 
  //Print the values for debugging 
  Serial.print("X Axis: "); 
  Serial.print(data[0]); 
  Serial.print("\tY Axis: "); 
  Serial.print(data[1]); 
  Serial.print("\tSwitch Status: ");
  Serial.println(data[2]);

  delay(60); 
}