//*****************************************************************************/
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
const int outPin=8;
const int outButton=11; 

int buttonState = 0;

int lastMillis = 0;

float allowedGVariation = .17;

double baseZG = 0.0;

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

  delay(500);
  
  accelemeter.getAcceleration(&ax,&ay,&az);
  baseZG = az - .25;
  
  pinMode(buttonPin, INPUT);
  pinMode(outPin, OUTPUT);
}

void loop()
{

  Serial.print("base ");
  Serial.println(baseZG);
  
  Serial.println(tempImproper);
  Serial.println(proper);  
  buttonState = digitalRead(buttonPin);
  
  if (buttonState)
  {
    
    digitalWrite(outButton,HIGH);
    
    if (improperPosition()){
      tempImproper += 1;
      digitalWrite(outPin,HIGH);
    }
    else
    {
      proper += 1;
      digitalWrite(outPin,LOW);
    }
  }else{
   digitalWrite(outButton,LOW); 
    
  }
}
  /*
  if(improper >= reminderFrequency)
  {
    reminder();
    totalImproper = tempImproper;
    tempImproper = 0;
  }
  */

void dataCollect(){
   
  accelemeter.getXYZ(&x,&y,&z);

    Serial.println("Position of X/Y/Z: ");
    Serial.println(x); 
    Serial.print("y = ");
    Serial.println(y);   
    Serial.print("z = ");
    Serial.println(z);
  
  accelemeter.getAcceleration(&ax,&ay,&az);
   
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

boolean improperPosition(){
  
   dataCollect();
   Serial.print("VAR1 ");
   Serial.println(baseZG + allowedGVariation);

   Serial.print("VAR2 ");
   Serial.println(baseZG - allowedGVariation);

   Serial.print("AZ ");
   Serial.println(az);
   
   if(baseZG + allowedGVariation < az  || baseZG - allowedGVariation > az )
    {
      delay(3000);
      dataCollect();
      if(baseZG + allowedGVariation < az  || baseZG - allowedGVariation > az ){

      return true;
      }
      else
      {
        delay(3000);
        return false;
      }
    }
    else
    { 
      delay(3000);
    
      return false; 
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
}
*/

void endProcess(){
  float bad=tempImproper/(tempImproper + proper);
  printf("You did not sit in a proper posture for %f% of the time sitting this session.", bad);
}

