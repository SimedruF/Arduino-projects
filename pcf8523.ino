// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
#include "RTClib.h"
#include <Servo.h> 
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#define PIN_SERVO 3

RTC_PCF8523 rtc;
Servo myservo;  // create servo object to control a servo 
int pos = 0;    // variable to store the servo position
int pos_read = 0;    // variable to store the servo position
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int alarm = 0;

void setup () {

  while (!Serial) {
    delay(1);  // for Leonardo/Micro/Zero
  }

  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
     //rtc.adjust(DateTime(2020, 4, 17, 10, 38, 0));
  }

  myservo.attach(PIN_SERVO);  //the pin for the servoa control
  if(myservo.attached() == 1)
  {
    Serial.println("Servo motor was attched ."); 
    Servo_parking();
  }
}

void loop () {
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    /*Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");*/

    // calculate a date which is 7 days, 12 hours and 30 seconds into the future
    /*DateTime future (now + TimeSpan(1,12,3,0));

    Serial.print(" now + 7d + 12h + 30m + 6s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();*/

Serial.println();
if((now.hour()== 7) && (now.minute()==30)&& ((now.second()== 10)||(now.second()== 20)||(now.second()== 30)))
{
  alarm = 1; 
  if(myservo.attached() == 0)
  {
     myservo.attach(PIN_SERVO);
  }
  
}
else
{
  alarm = 0;  
  if( myservo.attached() == 1)
  {
    myservo.detach();  
    Serial.println("Servo motor was detached ."); 
  }
}

if(alarm ==1) 
{
  Servo_click();
  pos_read= myservo.read();
  Serial.println(pos_read);
}
 Serial.print(" Alarma: ");
 Serial.print(alarm, DEC);
 Serial.println();
 delay(1000);
}

void Servo_click()
{
 for (pos = 0; pos <= 90; pos += 1) 
   { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  pos_read= myservo.read();
  Serial.println(pos_read); 
  for (pos = 90; pos >= 0; pos -= 1) 
  { // goes from 90 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }  
}

void Servo_parking()
{
  pos_read= myservo.read();
  Serial.println(pos_read); 
  for (pos = 90; pos >= 0; pos -= 1)
  { // goes from 90 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }  
}
