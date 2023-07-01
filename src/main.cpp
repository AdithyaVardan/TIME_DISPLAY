// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"
#include <SPI.h>
#include <string.h>
#include <iostream>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <WiFi.h>
#include "time.h"
#include "Ticker.h"
Ticker One_Second;
Ticker Alarm_System;
RTC_DS1307 DS1307_RTC;
#define LED_BUILTIN 2
using namespace std;

const char *ssid = "ACT102533919250";
const char *password = "29283905";

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19850;
const int daylightOffset_sec = 0;

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
// #define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 4
#define CS_PIN 5
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
String s = "";
bool f1 = true;
char timeMin[10];
char timeHour[10];

char Set_Time[10] = {0};
bool Blink = false;
uint32_t One_Second_Timer = 0;
int hour = 0;
int mini = 0;
int day = 0;
bool f = true;
char Buffer[50] = {0};
char Temp_Buffer[10] = {0};
void alarm()
{
  if(Blink == true)
  {
    Display.print("BREAK");
  }
  else
  {
    Display.print("     ");
  }
  if(One_Second_Timer >= 30)
  {
    Alarm_System.detach();
  }
  One_Second_Timer++;
}
void Blink_Cursor(void)
{
  DateTime now = DS1307_RTC.now();
  hour = now.twelveHour();
  mini = now.minute();
  memset(Temp_Buffer, 0, sizeof(Temp_Buffer));
  memset(Buffer, 0, sizeof(Buffer));
  sprintf(Temp_Buffer, "%02d", hour);
  strcat(Buffer, Temp_Buffer);
  if (f == true)
  {
    strcat(Buffer, ":");
    f = false;
  }
  else
  {
    strcat(Buffer, " ");
    f = true;
  }
  memset(Temp_Buffer, 0, sizeof(Temp_Buffer));
  sprintf(Temp_Buffer, "%02d", mini);
  strcat(Buffer, Temp_Buffer);
  if (Display.displayAnimate())
  {
    Display.displayReset();
  }
  Display.setTextAlignment(PA_CENTER);
  Serial.println(Buffer);
  Display.print(Buffer);
  String v = Buffer;
  if ((v == "06:14") || (v == "06 14"))
  {
    Alarm_System.attach(1,alarm);
    One_Second_Timer=0;
  }
  
}
String rtcset()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo, 500))
  {
    Serial.println("Failed to obtain time");
    return "ERR";
  }
  // Serial.println(&timeinfo, "   %H:%M:%S  %d  %B  %Y");
  s = "";
  strftime(timeMin, 4, "%M", &timeinfo);
  strftime(timeHour, 4, "%H", &timeinfo);
  s = strcat(strcat(timeHour, ":"), timeMin);
  // if(f1==true){
  //   s=strcat(strcat(timeHour,":"),timeMin);
  //   f1=false;
  // }
  // else
  // {
  //   s=strcat(strcat(timeHour," "),timeMin);
  //   f1=true;
  // }
  s.toCharArray(Set_Time, 5);
  DS1307_RTC.adjust(DateTime("Jun 20 2023", Set_Time));
  Serial.println(s);
  return s;
}

void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // disconnect WiFi as it's no longer needed
  // WiFi.disconnect(true);
  // WiFi.mode(WIFI_OFF);

  Display.begin();
  Display.setIntensity(10);
  Display.displayClear();

#ifndef ESP8266
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB
#endif

  if (!DS1307_RTC.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }
  One_Second.attach(1,Blink_Cursor);
  Alarm_System.attach(1,alarm);
  if (Display.displayAnimate())
  {
    Display.displayReset();
  }
  // DS1307_RTC.adjust(DateTime("Jun 20 2023","16:26:00"));
}



void loop()
{
 // rtcset();

}