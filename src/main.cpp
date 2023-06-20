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
String Date="Jun 20 2023";
String Time="Jun 20 2023";
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

char Week_days[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

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
   //DS1307_RTC.adjust(DateTime("Jun 20 2023","14:47:30"));
}


void loop () {
    DateTime now = DS1307_RTC.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(Week_days[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    if (Display.displayAnimate()) {
    Display.displayReset();
    }
    Display.setTextAlignment(PA_CENTER);
    Display.print(now.minute());
    Display.print(now.second());

    // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
    DateTime future (now );
    delay(1000);
}