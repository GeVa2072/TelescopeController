#line 2 "SideralTimeTest.ino"
#include <ArduinoUnit.h>
#include "SideralTime.h"
#include "SideralTimeTest.h"

/*
 * Test date conversion
 */
test(EpochDateConversion1)
{
  time_t time = SideralTime::mktime(1970, 1, 1, 0, 0, 0);
  assertEqual(0, time);
}

test(EpochDateConversion2)
{
  time_t time = SideralTime::mktime(2018, 1, 10, 17, 10, 11);
  assertEqual(1515604211, time);
}

test(EpochDateConversion3)
{
  time_t time = SideralTime::mktime(2017, 9, 22, 20, 01, 48);
  assertEqual(1506110508, time);
}

/*
 * Test Julian calandar, should be improve, some rounding value ...
*/

test(JulienCalendar1) {
    time_t time = SideralTime::mktime(2000, 1, 1, 12, 0, 0);
    SideralTimeTest* sideral = new SideralTimeTest(time);
    int round = 100*sideral->julienCalendarTest(time);
    assertEqual(245154457, round);
    //assertEqual(2451544.5, sideral->julienCalendarTest(time));
}

test(JulienCalendar2) {
    time_t time = SideralTime::mktime(2018, 1, 10, 12, 0, 0);
    SideralTimeTest* sideral = new SideralTimeTest(time);
    int round = 100*sideral->julienCalendarTest(time);
    assertEqual(245812893, round);
    //assertEqual(2458129.57, sideral->julienCalendarTest(time));
}

test(JulienCalendar3) {
    time_t time = SideralTime::mktime(2018, 1, 10, 18, 25, 29);
    SideralTimeTest* sideral = new SideralTimeTest(time);
    int round = 100*sideral->julienCalendarTest(time);
    assertEqual(245812893, round);
    //assertEqual(2458129.5, sideral->julienCalendarTest(time));
}


test(JulienCalendar4) {
    time_t time = SideralTime::mktime(2017, 9, 22, 20, 01, 48);
    SideralTimeTest* sideral = new SideralTimeTest(time);
    int round = 100*sideral->julienCalendarTest(time);
    assertEqual(245801918, round);
    //assertEqual(2458019.5, sideral->julienCalendarTest(time));
}

test(UTCtoSideral)
{
  time_t time = SideralTime::mktime(2018, 3, 30, 10, 21, 34);
  time_t expectedResult = SideralTime::mktime(1970, 1, 1, 22, 52, 36);

  SideralTimeTest* sideral = new SideralTimeTest(time);
  time_t sideralTime = sideral->time();
  int round = 100*sideral->julienCalendarTest(time);
  //assertEqual(245820784, round);
  assertEqual(245820880, round);
  assertEqual(expectedResult, sideralTime);
}

/*
Exercise:

At midnight on 1998 February 4th,
Local Sidereal Time at St.Andrews was 8h45m.
St.Andrews has longitude 2°48'W.

*/
/*
test(St_Andrews_Local_Sidereal_Time) {
  time_t time = SideralTime::makeTime(1998, 2, 4, 0, 0, 0);
  SideralTime* sideral = new SideralTime(time);
  time_t sideralTime = sideral->time();
  assertEqual((8*60+45), (int) sideralTime/60);

}
*/

/*

What was the Local Hour Angle of Betelgeuse (R.A. = 5h55m) at midnight?

RA of Betelgeuse = 5h 55m
At midnight, LST = 8h 45m
Local Hour Angle = LST - RA
so the Local Hour Angle of Betelgeuse was 8h 45m - 5h 55m = 2h 50m.

At what time was Betelgeuse on the meridian at St.Andrews?

On the meridian, Local Hour Angle = 0,
so if Betelgeuse was on the meridian at St.Andrews,
LST in St.Andrews = RA of Betelgeuse = 5h 55m.
(Recall that LST = RA of stars on local meridian.)

We are told that the LST was 8h 45m at midnight.
But at midnight, Betelgeuse was at Hour Angle 2h 50m,
so it would be on the meridian 2h 50m before midnight,
that is, at 21h 10m.
So Betelgeuse was on the meridian in St.Andrews at 21h 10m.

At what time was Betelgeuse on the meridian at Greenwich?

St.Andrews is 2°48' west of Greenwich = 0h 11m (divide by 15).
So Betelgeuse was on the Greenwich meridian
11 minutes before it reached the St.Andrews meridian.
i.e. at 20h 59m.
*/
test(e) {



}

/*


test(GMST) {
    time_t time = SideralTime::makeTime(1994, 6, 16, 18, 0, 0);
    SideralTimeTest* sideralTime = new SideralTimeTest(time);
    assertEqual(174.7711135, sideralTime->GMST(time));
}

test(Ephemeride)
{
  time_t time = SideralTime::makeTime(2017, 9, 22, 20, 01, 48);
  SideralTime* sideral = new SideralTime(time);
  time_t sideralTime = sideral->time();
  assertEqual(0, sideralTime);
}

*/
void setup()
{
  Serial.begin(9600);
  while(!Serial); // for the Arduino Leonardo/Micro only
}

void loop()
{
  Test::run();
}
