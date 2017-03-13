
#include <SDI12.h>
#include <AltSoftSerial.h>
/*
########################
#        OVERVIEW      #
########################
 
 Example A: Using the wildcard. 

 This is a simple demonstration of the SDI-12 library for Arduino.
 It requests information about the attached sensor, including its address and manufacturer info. 

#########################
#      THE CIRCUIT      #
#########################
 
 You should not have more than one SDI-12 device attached for this example.

 See: 
 https://raw.github.com/Kevin-M-Smith/SDI-12-Circuit-Diagrams/master/basic_setup_no_usb.png
 or
 https://raw.github.com/Kevin-M-Smith/SDI-12-Circuit-Diagrams/master/compat_setup_usb.png

###########################
#      COMPATIBILITY      #
###########################
 
 This library requires the use of pin change interrupts (PCINT). 
 Not all Arduino boards have the same pin capabilities. 
 The known compatibile pins for common variants are shown below.
 
 Arduino Uno: 	All pins. 

 Arduino Mega or Mega 2560:
 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), 
 A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69).

 Arduino Leonardo:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI)

#########################
#      RESOURCES        #
#########################

 Written by Kevin M. Smith in 2013. 
 Contact: SDI12@ethosengineering.org

 The SDI-12 specification is available at: http://www.sdi-12.org/
 The library is available at: https://github.com/StroudCenter/Arduino-SDI-12
*/


#define DATAPIN 9         // change to the proper pin
SDI12 mySDI12(DATAPIN); 
//AltSoftSerial altSerial;
/*
  '?' is a wildcard character which asks any and all sensors to respond
  'I' indicates that the command wants information about the sensor
  '!' finishes the command
*/
String CommandTemp = "0M2!";
String CommandMoist = "0M!";
String CommandGet = "0D0!";   
String myResponse = "";

void setup(){
  Serial.begin(9600); 
  mySDI12.begin(); 
}

void loop(){
  //Serial.write("1st: ");// wait a while for a response
  MeasureTemp();
  delay(1000);
  MeasureMoisture();
  delay(1000);
  SendResult();
  //delay(1000);
  
}

void MeasureTemp(){
  myResponse += "T";
  mySDI12.sendCommand(CommandTemp); 
  mySDI12.end();  
  delay(1000);
  mySDI12.begin();
  mySDI12.sendCommand(CommandGet);
  delay(300);
  while(mySDI12.available())
  {
    myResponse += mySDI12.readString();
  }
  myResponse.trim();
  
}
void MeasureMoisture(){
  myResponse += "M";
  mySDI12.sendCommand(CommandMoist); 
  mySDI12.end();  
  delay(1000);
  mySDI12.begin();
  mySDI12.sendCommand(CommandGet);
  delay(300);
  while(mySDI12.available())
  {
    myResponse += mySDI12.readString();
  }
  myResponse.trim();

}

void SendResult()
{
      myResponse += "!";
      Serial.print(myResponse);
      myResponse = "";
      //delay(5000);
      
}



