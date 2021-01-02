#include <Arduino.h>
#include "RTClib.h"
#include "LedControl.h"

RTC_DS1307 RTC;
LedControl lc = LedControl(4, 2, 3, 1);

int lightSensorPin = A0;
int analogValue = 0;

void setup() {
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);

  Serial.begin(9600);
  RTC.begin();
  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  else {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}


void loop() {
  DateTime now = RTC.now();
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  String h1;
  String m1;
  String s1;
  char hh1;
  char hh2;
  char mm1;
  char mm2;
  char ss1;
  char ss2;

  if(now.hour() < 10){
    h1 = String(now.hour(), DEC);
    hh1 = '0';
    hh2 = h1.charAt(0);
  } else {
    h1 = String(now.hour(), DEC);
    hh1 = h1.charAt(0);
    hh2 = h1.charAt(1);
  }
 

  if(now.minute() < 10){
    m1 = String(now.minute(), DEC);
    mm1 = '0';
    mm2 = m1.charAt(0);
  } else {
    m1 = String(now.minute(), DEC);
    mm1 = m1.charAt(0);
    mm2 = m1.charAt(1);
  }
  

  if (now.second() < 10){
    s1 = String(now.second(), DEC);
    ss1 = '0';
    ss2 = s1.charAt(0);
  } else {
    s1 = String(now.second(), DEC);
    ss1 = s1.charAt(0);
    ss2 = s1.charAt(1);
  }

  
  lc.setChar(0, 0, hh1, false);
  lc.setChar(0, 1, hh2, false);
  lc.setRow(0, 2, B10000000);
  lc.setChar(0, 3, mm1, false);
  lc.setChar(0, 4, mm2, false);
  lc.setRow(0, 5, B10000000);
  lc.setChar(0, 6, ss1, false);
  lc.setChar(0, 7, ss2, false);

  analogValue = analogRead(lightSensorPin);
  Serial.println(analogValue);

  lc.setIntensity(0, 8);
  if (analogValue < 50)
  {
    lc.setIntensity(0, 3);
  }
  else if (analogValue >= 50 && analogValue <= 100)
  {
    lc.setIntensity(0, 8);
  }
  else
  {
    lc.setIntensity(0, 15);
  }

  delay(1000);
}