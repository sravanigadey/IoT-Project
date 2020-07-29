
/*  Getting_BPM_to_Monitor prints the BPM to the Serial Monitor, using the least lines of code and PulseSensor Library.
 *  Tutorial Webpage: https://pulsesensor.com/pages/getting-advanced
 *
--------Use This Sketch To------------------------------------------
1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
2) Learn about using a PulseSensor Library "Object".
4) Blinks LED on PIN 13 with user's Heartbeat.
--------------------------------------------------------------------*/
#include <SoftwareSerial.h>
SoftwareSerial s(2,3);
SoftwareSerial s1(0,1);
#define USE_ARDUINO_INTERRUPTS true   
#include <PulseSensorPlayground.h>
const int PulseWire = 0;   
const int LED13 = 13;          
int Threshold = 550;           
PulseSensorPlayground pulseSensor;  
void setup() {   
Serial.begin(9600);
s.begin(9600);
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);     
  pulseSensor.setThreshold(Threshold);   
  pinMode(7,OUTPUT);
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");
  }
}
void loop() {
 int myBPM = pulseSensor.getBeatsPerMinute(); 
 Serial.println(myBPM);
if (pulseSensor.sawStartOfBeat()) {  
  if(myBPM > 150) { 
    SendMessage();         
    
  }
}       
delay(20);     
}
void SendMessage() {
  s.println("AT+CMGF=1");
  delay(1000);
  s.println("AT+CMGS=\"+918498944761\"\r");
  delay(1000);
  s.println("abnormal conditions in heart beat of soldiers");
  Serial.println("Message sent");
  delay(1000);
  s.println((char)26);
  delay(100);
}
