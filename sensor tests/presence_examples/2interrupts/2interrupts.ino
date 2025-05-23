/******************************************************************************
  Example2_Interrupts.ino
  
  Read human presence detection value from the STHS34PF80 sensor, print them
  to terminal using the interrupt flag instead of the typical data ready flag. 
  Prints raw IR presence values (cm^-1).

  SparkFun STHS34PF80 Arduino Library
  Madison Chodikov @ SparkFun Electronics
  Original Creation Date: September 19th, 2023
  https://github.com/sparkfun/SparkFun_STHS34PF80_Arduino_Library

  Wire up the connections using the header pins like so:

  ARDUINO --> STHS34PF80
  SDA (A4) --> SDA
  SCL (A5) --> SCL
  INT (D14) --> INT
  3.3V --> 3.3V
  GND --> GND
******************************************************************************/

#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;

// Values to fill with presence data
int16_t presenceVal = 0;

// Change the pin number to the pin that has been chosen for your setup
int intPin = 14;

// Star the flag as false
bool volatile interruptFlag = false;

// ISR to set the triggered interrupt
void isr1()
{
  interruptFlag = true;
}

void setup()
{
    Serial.begin(9600);
    Serial.println("STHS34PF80 Example 2: Interrupts");

    // Begin I2C
    Wire.begin();

    // Establish communication with device 
    if(mySensor.begin() == false)
    {
      Serial.println("Error setting up device - please check wiring.");
      while(1);
    }

    // Set INT pin to be triggered on rising and falling edges of INT pin
    pinMode(intPin, INPUT);
    // Attach interrupt to the pin as a digital pin that triggers on a change
    attachInterrupt(digitalPinToInterrupt(intPin), isr1, CHANGE);

    // Route all interrupts from device to interrupt pin
    mySensor.setTmosRouteInterrupt(STHS34PF80_TMOS_INT_OR);

    // Enable the presence interrupt source 
    // (see page 17 of application note AN5867 for more information)
    mySensor.setTmosInterruptOR(STHS34PF80_TMOS_INT_PRESENCE);

    // Set interrupt value to pulsed on the INT pin
    mySensor.setInterruptPulsed(0);

    delay(500);
}

void loop() 
{
  // If interrupt is triggered
  if(interruptFlag == true)
  {
    interruptFlag = false;
    
    sths34pf80_tmos_func_status_t status;
    mySensor.getStatus(&status);
    
    Serial.println("Data ready!");
    
    
    // If the flag is high, then read out the information
    if(status.pres_flag == 1)
    {
      // Presence Units: cm^-1
      mySensor.getPresenceValue(&presenceVal);
      Serial.print("Presence: ");
      Serial.print(presenceVal);
      Serial.println("cm^-1");
    }
  }
}