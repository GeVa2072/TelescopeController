#include "SideralTime.h"
#include <malloc.h>
#include <HardwareSerial.h>
/*
 * Compute sideral time from UTC time.
 *
 * Step 1 :  Get sideral time at Greenwich 1/1/2000 12UTC SIDERAL_TIME_AT_GREENWICH_1_1_2000_12_UTC
 *           time corresponding to 1/1/2000 12UTC in epoch GREENWIH_TIME_1_1_2000_12_UTC
 *           epoch days duracion divide by sideral days duration TIME_DAYS_DURATION_OVER_SIDERAL_DAYS_DURATION
 *           sideral versus epoch days shift
 * Step 2a : Calculate second elapsed since 1/1/2000 12 UTC and time
 * Step 2b : Convert this epoch second to sideral second
 * Step 3 :  Add this sideral time difference to sideral time at Greenwich 1/1/2000 12UTC
*/
#define GREENWIH_TIME_1_1_2000_12_UTC 946728000
#define J2000 2451545.0
SideralTime::SideralTime(time_t time)
{
    double h = ((double)time/60/60) - ((int)time/60/60/24)*24;
    int t = ((int) time /(24*60*60)) - ((int)GREENWIH_TIME_1_1_2000_12_UTC /(24*60*60));
    double d =h/24 -0.5 + t;

    Serial.print(h);
    Serial.print("-");
    Serial.print(t);
    Serial.print("-");
    Serial.println(d);

    sideralTime= ((18.697374558 + 24.06570982441908*d) - ((int)18.697374558 + 24.06570982441908*d))*100;

    /*
   double ut = time % 24*60*60;
   ut = time / 60 / 60;
   double t = (julienCalendarElapsedDaysFractionSinceJ2000(time)-J2000)/36525.0;
   double d = (6.697374558+(2400.051336*t) + (0.000025862*t*t)+(ut*1.00273779093));
   d = d - ((int)d/24)*24;
   sideralTime = d*1000;*/
}

SideralTime::~SideralTime()
{
    //dtor
}

static const char monthtable[]=
{ 31,29,31,30,31,30,31,31,30,31,30 };

/* Rules for leap-years:
 * 1. every 4th year is a leap year
 * 2. every 100th year is none
 * 3. every 400th is one
 * 4. 1900 was none, 2000 is one
 */
 static double* getNbDays(time_t time) {
    int nbDays = time / (24*60*60);
    int nbLeapYear = nbDays / (4*365) /* every 4 years are leap*/
                        - nbDays / (100*365) /* every 100 years are not leap*/
                            + nbDays / (400 * 365); /* every 400 years are leap*/

    int year = (nbDays - nbLeapYear) / 365; // remove leap days

    int nbElapsedDaysDuringYear = (nbDays - nbLeapYear) - (365 * year);
    year+=1970;
    // number of days in the curent year.

    int nbDaysInMonth = nbElapsedDaysDuringYear;
    if( ! (year%4 == 0 && year%100 != 0 || year%400 == 0) )  {
        nbDaysInMonth++; // this year is NOT leap we correct month length in arrays.
    }
    int i;
    for(i=0;i<11;i++)
        if(nbDaysInMonth<monthtable[i])
          break;
        else
          nbDaysInMonth-=monthtable[i];

    double* result = (double *) malloc(3*sizeof(double));
    result[0] = (int) year;
    result[1] = (int) i+1;
    result[2] = nbDaysInMonth + (time%(24*60*60))/(24*60*60);

    return result;
 }

double SideralTime::julienCalendarElapsedDaysFractionSinceJ2000(time_t time) {
    double* splitTime = getNbDays(time);

    return (1461 * (splitTime[0] + 4800 + (splitTime[1]-14)/12))/4 + (367* (splitTime[1]-2-12*((splitTime[1]-14)/12)))/12 - (3 * ((splitTime[0] +4900 + (splitTime[1] -14)/12)/100))/4 +splitTime[2] -32075;
}

double SideralTime::GMST(time_t time) {
    return 280.46061837 + 360.98564736629 * julienCalendarElapsedDaysFractionSinceJ2000(time);
}


/*
 * mktime64 - Converts date to seconds.
 * Converts Gregorian date to seconds since 1970-01-01 00:00:00.
 * Assumes input in normal date format, i.e. 1980-12-31 23:59:59
 * => year=1980, mon=12, day=31, hour=23, min=59, sec=59.
 *
 * [For the Julian calendar (which was used in Russia before 1917,
 * Britain & colonies before 1752, anywhere else before 1582,
 * and is still in use by some communities) leave out the
 * -year/100+year/400 terms, and add 10.]
 *
 * This algorithm was first published by Gauss (I think).
 *
 * A leap second can be indicated by calling this function with sec as
 * 60 (allowable under ISO 8601).  The leap second is treated the same
 * as the following second since they don't exist in UNIX time.
 *
 * An encoding of midnight at the end of the day as 24:00:00 - ie. midnight
 * tomorrow - (allowable under ISO 8601) is supported.
 */
time_t SideralTime::mktime(const unsigned int year0, const unsigned int mon0,
		const unsigned int day0, const unsigned int hour,
		const unsigned int min, const unsigned int sec){

    unsigned int mon = mon0, year = year0;

	/* 1..12 -> 11,12,1..10 */
	if (0 >= (int) (mon -= 2)) {
		mon += 12;	/* Puts Feb last since it has leap day */
		year -= 1;
	}

    return ((((time_t) (year/4 - year/100 + year/400 + 367*mon/12 + day0) + (year*365) - 719499
                    )*24 + hour /* now have hours - midnight tomorrow handled here */
                )*60 + min /* now have minutes */
            )*60 + sec; /* finally seconds */
}

