#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 
 
RF24 radio(8,9); // CE, CSN 
 
const byte address[6] = "09870"; //Unique Code that will be shared to you by the 
// coordinators
 
int xAxisValue = 0; 
int yAxisValue = 0; 
 
void setup() { 
  radio.begin(); 
  Serial.begin(115200); 
  radio.openWritingPipe(address); 
  radio.stopListening(); 
  pinMode(4, INPUT_PULLUP); 
} 
void loop() { 
  int xAxis = analogRead(A0);    //Write code to Read Joysticks X-axis 
  int yAxis = analogRead(A1); //Write code to Read Joysticks X-axis 
   
  // Convert integer values to strings 
  String xString = String(xAxis); 
  String yString = String(yAxis); 
 
  // Create a 2D character array to hold both values 
  char data[2][6]; // 2 strings of 5 characters each (including null terminator) 
 
  // Copy the strings to the 2D character array 
  xString.toCharArray(data[0], 6); 
  yString.toCharArray(data[1], 6); 
 
  // Send the 2D character array 
  radio.write(&data, sizeof(data)); 
 
  // Print the analog values for debugging 
  Serial.print("X Axis: "); 
  Serial.print(data[0]); 
  Serial.print("\tY Axis: "); 
  Serial.println(data[1]); 
 
  delay(60); 
}