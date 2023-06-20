// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"
#include <SPI.h>
#include <string.h>
#include <iostream>
RTC_DS1307 DS1307_RTC;
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
using namespace std;


// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 4
#define CS_PIN 5
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


void setup () {
  Serial.begin(115200);
  Display.begin();
  Display.setIntensity(10);
  Display.displayClear();

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (!DS1307_RTC.begin()) {
    Serial.println("Couldn't find RTC");
    while(1);
  }
   //DS1307_RTC.adjust(DateTime("Jun 20 2023","16:26:00"));
}

int hour = 0;
int mini = 0;
int day = 0;
bool f=true;
char Buffer[50]={0};
char Temp_Buffer[10]={0};
void loop () {
    DateTime now = DS1307_RTC.now();
    hour = now.twelveHour();
    mini =now.minute();
    memset(Temp_Buffer,0,sizeof(Temp_Buffer));
    memset(Buffer,0,sizeof(Buffer));
    sprintf(Temp_Buffer,"%02d",hour);
    strcat(Buffer,Temp_Buffer);
    if(f==true){
    strcat(Buffer,":");
    f=false;
    }
    else
    {
    strcat(Buffer," ");
    f=true;
    }
    memset(Temp_Buffer,0,sizeof(Temp_Buffer));
    sprintf(Temp_Buffer,"%02d",mini);
    strcat(Buffer,Temp_Buffer);
    Buffer[8]=NULL;
    if (Display.displayAnimate()) {
    Display.displayReset();
    }
    Display.setTextAlignment(PA_CENTER);
    Display.print(Buffer);
    delay(1000);
}