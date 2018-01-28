/*****************************************************************************/
//	Function:    Get the accelemeter of the x/y/z axis. 
//  Hardware:    Grove - 3-Axis Digital Accelerometer(±1.5g)
//	Arduino IDE: Arduino-1.0
//	Author:	 Frankie.Chu		
//	Date: 	 Jan 10,2013
//	Version: v0.9b
//	by www.seeedstudio.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
/*******************************************************************************/

#include <Wire.h>
#include "MMA7660.h"
MMA7660 accelemeter;

//import some time shiet
//import processing.serial.*;
//PrintWriter output;

const int buttonPin = 2;

int buttonState = 0;

int lastMillis = 0;

int allowedGVariation = .15;

int baseZG = 0;

int proper = 0;
int tempImproper = 0;
int totalImproper = 0;

int reminderFrequency = 3600;

int8_t x;
int8_t y;
int8_t z;
float ax,ay,az;


void setup()
{
	accelemeter.init();  
	Serial.begin(9600);
 
  pinMode(buttonPin, INPUT);
}

void loop()
{
    
  buttonState = digitalRead(buttonPin);

  if (buttonState)
  {
    
    if (improperPosition()){
      tempImproper += 1;
    }
    else
    {
      proper += 1;
    }

    
   
  /*if (buttonState && ((millis() - lastMillis)/1000 > 2.00)){
    dataCollect();
  }else{
    endProcess();
  }
  */
  }
  /*
  if(improper >= reminderFrequency)
  {
    reminder();
    totalImproper = tempImproper;
    tempImproper = 0;
  }
  */
}

void dataCollect(){
   

  accelemeter.getXYZ(&x,&y,&z);

  //value = value + x + "\t" + y + "\t" + z + "\t";

    serial.println("Position of X/Y/Z: ")
    Serial.println(x); 
    Serial.print("y = ");
    Serial.println(y);   
    Serial.print("z = ");
    Serial.println(z);
  
  accelemeter.getAcceleration(&ax,&ay,&az);

  value= value + ax + "\t" + ay + "\t" + az;
  
  Serial.println("accleration of X/Y/Z: ");
  Serial.print(ax);
  Serial.println(" g");
  Serial.print(ay);
  Serial.println(" g");
  Serial.print(az);
  Serial.println(" g");
  Serial.println("*************");
  delay(1000); 
}

bool improperPosition(){
  
   dataCollect();
   if(baseZG + allowedGVariation < az  || baseZG - allowedGVariation > az )
    {
      delay(1000);
      dataCollect();
      if(baseZG + allowedGVariation > az  || baseZG - allowedGVariation < az ){

      tempImproper += 1;
      
    }
    else
    {
      delay(1000);
    }
  }
  
}
/*
void properPosition(){
  
  dataCollect();
  if(baseZG + allowedGVariation > az  && baseZG - allowedGVariation < aZ )
    {
      delay(1000);
      dataCollect();
      if(baseZG + allowedGVariation > az  || baseZG - allowedGVariation < aZ ){

      proper += 1;
      
    }
    else
    {
      delay(1000);
    }
  }

  
}
*/

  
}

void draw() {
    if (mySerial.available() > 0 ) {
         if ( value != null ) {
              output.println(value);
         }
    }
}

void endProcess(){
  draw();  
}

