// THIS REQUIRES YOU TO INSTALL FIRST Pedvide's ADC LIB
// Fetch it here: https://github.com/pedvide/ADC

#include <ADC.h>
#include "Teensy31FastADC.h"

int LED = 13;
int AIN = A3;
// for the highspeed functions you need to figure out the right channel via ADC_Module::channel2sc1aADC0["APIN#"]
const int channelA3 = ADC_Module::channel2sc1aADC0[3];

void setup() {                
  highSpeed8bitADCSetup();
  pinMode(LED, OUTPUT); 
  pinMode(AIN, INPUT); 
  Serial.begin(115200);  

}

int val = 0;
int startTime;
int stopTime;
int totalTime;
int i;
int samples = 1000000;
int samplesPerSec;

void loop() {

  startTime = millis();
  
  for(i=0;i<samples;i++) {     
//     val = analogRead(AIN);
     val = highSpeed8bitAnalogRead(channelA3);
//     highSpeed8bitAnalogReadMacro(channelA3,val);
  }
  
  stopTime = millis();
  totalTime = stopTime-startTime;
  samplesPerSec = samples*1000/totalTime;

  //PRINT Sample/sec
  Serial.print("T: ");
  Serial.print(totalTime);
  Serial.print(" S/sec: ");
  Serial.println(samplesPerSec);

  //BLINK
  digitalWrite(LED, HIGH);   
  delay(100);               
  digitalWrite(LED, LOW); 
  delay(100);
} 



/*
Timings in ms for 1.000.000 readings

analogRead
T: 8881 S/sec: 112599
T: 8882 S/sec: 112587
T: 8881 S/sec: 112599
T: 8881 S/sec: 112599

analogRead + highSpeed8bitADCSetup
T: 1630 S/sec: 613496
T: 1631 S/sec: 613120
T: 1631 S/sec: 613120
T: 1631 S/sec: 613120

highSpeedAnalogRead + highSpeed8bitADCSetup
T: 1022 S/sec: 978473
T: 1023 S/sec: 977517
T: 1022 S/sec: 978473
T: 1023 S/sec: 977517

ighSpeedAnalogReadMacro + highSpeed8bitADCSetup
T: 813 S/sec: 1230012
T: 814 S/sec: 1228501
T: 813 S/sec: 1230012
T: 814 S/sec: 1228501


*/
