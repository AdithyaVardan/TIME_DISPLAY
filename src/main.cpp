#include <Arduino.h>
#include <string.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <iostream>
#include <WiFi.h>
#include <string>
#include "time.h"
#include "Ticker.h"

const char* ssid     = "your SSID NAME";
const char* password = "your SSID PASSWORD";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19850;
const int   daylightOffset_sec = 0;

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 5
char timeHour[4];
char timeMin[4];
String s;
int i=0;
bool f=true;
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
String printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "ERR";
  }
  Serial.println(&timeinfo, "   %H:%M:%S  %d  %B  %Y");
  s="";
  strftime(timeMin,4,"%M",&timeinfo);
  strftime(timeHour,4, "%I", &timeinfo);
  if(f==true){
    s=strcat(strcat(timeHour,":"),timeMin);
    f=false;
  }
  else
  {
    s=strcat(strcat(timeHour," "),timeMin);
    f=true;
  }
  Serial.println(s);
  Serial.println(i);
  return s;
  }
void setup(){
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  Display.begin();
  Display.setIntensity(10);
  Display.displayClear();
}
void loop(){
  // printLocalTime();
  if (Display.displayAnimate()) {
    Display.displayReset();
  }
  Display.setTextAlignment(PA_CENTER);
  Display.print(printLocalTime());

  delay(1000);
}