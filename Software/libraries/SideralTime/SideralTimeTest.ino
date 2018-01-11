#line 2 "SideralTimeTest.ino"
#include <ArduinoUnit.h>
#include "SideralTime.h"
#include "SideralTimeTest.h"

/*
 * Test date conversion
 */
 /*
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
*/
/*
 * Test time function
 */

/*
test(keep_whole) {
    SideralTimeTest* sideral = new SideralTimeTest(0);
    assertEqual(1, sideral->keep_wholeTest(1.2));
    assertEqual(0, sideral->keep_wholeTest(0.0));
    assertEqual(45645643, sideral->keep_wholeTest(45645643.45435));
}

test(keep_fractional) {
    SideralTimeTest* sideral = new SideralTimeTest(0);
    assertAlmostEqual(0.2, sideral->keep_fractionalTest(1.2));
    assertAlmostEqual(0, sideral->keep_fractionalTest(0.0));
    assertAlmostEqual(0.45435, sideral->keep_fractionalTest(45645643.45435));
}

test(keep_time) {
    SideralTimeTest* sideral = new SideralTimeTest(0);
    time_t time = SideralTime::mktime(2000, 1, 1, 12, 0, 0);
    assertEqual(12*60*60, sideral->keep_timeTest(time));
}

test(remove_time) {
    SideralTimeTest* sideral = new SideralTimeTest(0);
    time_t time = SideralTime::mktime(2000, 1, 1, 12, 0, 0);
    time_t expected = SideralTime::mktime(2000, 1, 1, 0, 0, 0);
    assertEqual( expected, sideral->remove_timeTest(time));
}

*/

test(nbDays) {
    time_t time = SideralTime::mktime(2000, 1, 1, 12, 0, 0);
    SideralTimeTest* sideral = new SideralTimeTest(time);
    double* nbDays = sideral->getNbDaysTest(time);
    assertEqual(2000, nbDays[0]);
    assertEqual(1, nbDays[1]);
    assertEqual(1.5, nbDays[2]);
}


/*
 * Test Julian calandar, should be improve, some rounding value ...
 */
test(JulienCalendar1) {
    time_t time = SideralTime::mktime(2000, 1, 1, 12, 0, 0);
    SideralTimeTest* sideral = new SideralTimeTest(time);
    assertEqual(2451545.0, sideral->julienCalendarTest(time));
}

test(JulienCalendar2) {
    time_t time = SideralTime::mktime(2018, 1, 10, 12, 0, 0);
    SideralTimeTest* sideral = new SideralTimeTest(time);
    assertEqual(2458129, sideral->julienCalendarTest(time));
}


test(JulienCalendar3) {
    time_t time = SideralTime::mktime(2018, 1, 10, 18, 25, 29);
    SideralTimeTest* sideral = new SideralTimeTest(time);
    char s[10];
    sprintf(s, "%f", sideral->julienCalendarTest(time));
    assertEqual("2458129.267697", s);
}


test(JulienCalendar4) {
    time_t time = SideralTime::mktime(2017, 9, 22, 20, 01, 48);
    SideralTimeTest* sideral = new SideralTimeTest(time);
    char s[10];
    sprintf(s, "%f", sideral->julienCalendarTest(time));
    assertEqual("2458019.334583", s);
}


test(compareDouble) {
  assertEqual(1.11111, 1.11111);
}
test(UTCtoSideral)
{
  time_t time = SideralTime::mktime(2018, 3, 30, 10, 21, 34);

  SideralTimeTest* sideral = new SideralTimeTest(time);
  double sideralTime = sideral->time();
  char val[10];
  sprintf(val, "%d", sideralTime);
  //assertEqual("22.94", val);
  //assertEqual(22+52*60+36*3600, sideralTime*60*60);
  int h = sideralTime;
  int m = (sideralTime-h)*60;
  int s = sideralTime-h-m/60;
  assertEqual(22, h);
  assertEqual(52, m);
  assertEqual(36, s);
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
