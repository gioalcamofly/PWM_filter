#include <Arduino.h>
#include <stdint.h>

#define OC2A_PIN 11
uint8_t dutyCycle;

void set_timer2() {
  TCCR2A = 0;
  TCCR2A |= (1<<(WGM21)) | (1<<(WGM20));
  TCCR2A |= (1<<(COM2A1)) | (1<<(COM2B1));
  TCCR2B = 4;
  OCR2A = dutyCycle;
}

void setup() {
  pinMode(OC2A_PIN, OUTPUT);
  Serial.begin(9600);
  printSetMillivolts();
  set_timer2();
}

void printSetMillivolts() {
  Serial.println("Please, enter the output setting --> Output [0-5000]");
  while (!Serial.available()) {}
  String command = Serial.readStringUntil('\n');
  if (command.startsWith("Output")) {
    uint16_t value = command.substring(7).toInt();
    if (value >= 0 && value <= 5000) {
      dutyCycle = map(value, 0, 5000, 0, 255);
      return;
    }
    Serial.println("Value must be between 0 and 5000. Please, try again.");
  }
  printSetMillivolts();
  
}

void loop() 
{   
    Serial.println("Do you want to change the output?");
    byte key=0;
    while( (key!='y') && (key!='Y') )
    {
      if(Serial.available()>0) key=Serial.read();
    }
    printSetMillivolts();
    set_timer2();
    Serial.println("Signal changed");
}  

