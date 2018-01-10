#line 2 "SideralTimeTest.ino"
#include <ArduinoUnit.h>
#include "SideralTime.h"
#include "SideralTimeTest.h"

/*
 * Test date conversion
 */
test(DateConversion1)
{
  time_t time = SideralTime::makeTime(1970, 1, 1, 0, 0, 0);
  assertEqual(0, time);
}

test(DateConversion2)
{
  time_t time = SideralTime::makeTime(2018, 1, 10, 17, 10, 11);
  assertEqual(1515604211, time);
}

/*
 * Test date conversion
 */
test(Equinoxe)
{
  time_t time = SideralTime::makeTime(2017, 9, 22, 20, 01, 48);
  assertEqual(1506110508, time);
}

test(JulienCalendar1) {
    time_t time = SideralTime::makeTime(2000, 1, 1, 0, 0, 0);
    SideralTimeTest* sideralTime = new SideralTimeTest(time);
    assertEqual(0, sideralTime->julienCalendarTest(time));
}

test(JulienCalendar2) {
    time_t time = SideralTime::makeTime(2018, 1, 10, 18, 25, 29);
    SideralTimeTest* sideralTime = new SideralTimeTest(time);
    assertEqual(2458129, sideralTime->julienCalendarTest(time));
}

test(GMST) {
    time_t time = SideralTime::makeTime(1994, 6, 16, 18, 0, 0);
    SideralTimeTest* sideralTime = new SideralTimeTest(time);
    assertEqual(174.7711135, sideralTime->GMST(time));
}

/*
 * Ephemeride date align Sideral time to UTC time.
 */
test(Ephemeride)
{
  time_t time = SideralTime::makeTime(2017, 9, 22, 20, 01, 48);
  SideralTime* sideral = new SideralTime(time);
  time_t sideralTime = sideral->time();
  assertEqual(0, sideralTime);
}

test(UTCtoSideral)
{
  time_t time = SideralTime::makeTime(2018, 3, 30, 10, 21, 34);
  time_t expectedResult = SideralTime::makeTime(1970, 1, 1, 22, 52, 36);

  SideralTime* sideral = new SideralTime(time);
  time_t sideralTime = sideral->time();

  assertEqual(expectedResult, sideralTime);
}

void setup()
{
  Serial.begin(9600);
  while(!Serial); // for the Arduino Leonardo/Micro only
}

void loop()
{
  Test::run();
}
