#line 2 "SideralTimeTest.ino"
#include <ArduinoUnit.h>
#include "../Time/Time.h"
#include "SideralTime.h"

test(Ephemeride)
{
  static tmElements_t testTime;
  testTime.Day = 21;
  testTime.Month=8;
  testTime.Year=2018 - 1970;
  testTime.Hour=4;
  testTime.Minute=16;
  testTime.Second=00;
  time_t time = makeTime(testTime);
  SideralTime* sideral = new SideralTime(time);
  time_t sideralTime = sideral->time();
  assertEqual(0, sideralTime);
}

test(UTCtoSideral)
{
  static tmElements_t testTime;
  testTime.Day = 30;
  testTime.Month=2;
  testTime.Year=2018 - 1970;
  testTime.Hour=10;
  testTime.Minute=21;
  testTime.Second=34;

  static tmElements_t expectedResult;
  expectedResult.Day = 1;
  expectedResult.Month=0;
  expectedResult.Year=0;
  expectedResult.Hour=22;
  expectedResult.Minute=52;
  expectedResult.Second=36;

  time_t time = makeTime(testTime);
  SideralTime* sideral = new SideralTime(time);
  time_t sideralTime = sideral->time();
  assertEqual(makeTime(expectedResult), sideralTime);
}
#define SECS_PER_MIN  ((time_t)(60UL))
#define SECS_PER_HOUR ((time_t)(3600UL))
#define SECS_PER_DAY  ((time_t)(SECS_PER_HOUR * 24UL))
#define DAYS_PER_WEEK ((time_t)(7UL))
#define SECS_PER_WEEK ((time_t)(SECS_PER_DAY * DAYS_PER_WEEK))
#define SECS_PER_YEAR ((time_t)(SECS_PER_DAY * 365UL)) // TODO: ought to handle leap years
#define SECS_YR_2000  ((time_t)(946684800UL)) // the time at the start of y2k

#define LEAP_YEAR(Y)     ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )
static  const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0

time_t makeTime(const tmElements_t &tm){
// assemble time elements into time_t
// note year argument is offset from 1970 (see macros in time.h to convert to other formats)
// previous version used full four digit year (or digits since 2000),i.e. 2009 was 2009 or 9

  int i;
  uint32_t seconds;

  // seconds from 1970 till 1 jan 00:00:00 of the given year
  seconds= tm.Year*(SECS_PER_DAY * 365);
  for (i = 0; i < tm.Year; i++) {
    if (LEAP_YEAR(i)) {
      seconds +=  SECS_PER_DAY;   // add extra days for leap years
    }
  }

  // add days for this year, months start from 1
  for (i = 1; i < tm.Month; i++) {
    if ( (i == 2) && LEAP_YEAR(tm.Year)) {
      seconds += SECS_PER_DAY * 29;
    } else {
      seconds += SECS_PER_DAY * monthDays[i-1];  //monthDay array starts from 0
    }
  }
  seconds+= (tm.Day-1) * SECS_PER_DAY;
  seconds+= tm.Hour * SECS_PER_HOUR;
  seconds+= tm.Minute * SECS_PER_MIN;
  seconds+= tm.Second;
  return (time_t)seconds;
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
