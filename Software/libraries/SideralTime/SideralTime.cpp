#include "SideralTime.h"

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
#define SIDERAL_TIME_AT_GREENWICH_1_1_2000_12_UTC 67310 // Step 1
#define GREENWIH_TIME_1_1_2000_12_UTC 946728000
#define TIME_DAYS_DURATION_OVER_SIDERAL_DAYS_DURATION  0.9972696
#define DAYS_SHIFT  0.0027304


static long leaps_between(long y1, long y2)
{
	long leaps1 = (y1 - 1)/4 - (y1 - 1)/100
		+ (y1 - 1)/400;
	long leaps2 = (y2 - 1)/4 - (y2 - 1)/100
		+ (y2 - 1)/400;
	return leaps2 - leaps1;
}


static const unsigned short __mon_yday[2][13] = {
	/* Normal years. */
	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
	/* Leap years. */
	{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}
};

static int __isleap(long year)
{
	return (year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0);
}


SideralTime::SideralTime(time_t time)
{
    /*int ELAPSED_TIME_SINCE_GREENWIH_TIME_1_1_2000_12_UTC = (time - GREENWIH_TIME_1_1_2000_12_UTC); // Step 2a: Seconds passed since 1/1/2000 12h UTC and time
    time_t ELAPSED_SIDERAL_TIME_SINCE_GREENWIH_TIME_1_1_2000_12_UTC =
        (time_t) ((double)ELAPSED_TIME_SINCE_GREENWIH_TIME_1_1_2000_12_UTC * (double)DAYS_SHIFT); // step 2b: Sideral time elapse between time and sideral time at Greenwich 1/1/2000 12UTC SIDERAL_TIME_AT_GREENWICH_1_1_2000_12_UTC
    sideralTime = (time_t) ELAPSED_SIDERAL_TIME_SINCE_GREENWIH_TIME_1_1_2000_12_UTC + SIDERAL_TIME_AT_GREENWICH_1_1_2000_12_UTC; //Step3: Move 1/1/2000 12UTC sideral time to time.*/
    double d = (time - GREENWIH_TIME_1_1_2000_12_UTC) / 24 / 60 / 60;
    sideralTime = 18.697374558 + 24.06570982441908 * d;
}

SideralTime::~SideralTime()
{
    //dtor
}

time_t SideralTime::julienCalendarElapsedDaysFractionSinceJ2000(time_t time) {
    tm_time tm ;
    int days = time/(24*60*60);
    int remainder = time%(24*60*60);
    int rem = remainder;
    while (rem < 0) {
		rem += (24*60*60);
		--days;
	}
	// Should be not useful never append
	while (rem >= (24*60*60)) {
		rem -= (24*60*60);
		++days;
	}
	tm.hour = rem/(60*60);
	rem %= (60*60);
	tm.minutes = rem/60;
	tm.sec = rem%60;
	int y = 1970;

	while (days < 0 || days >= (__isleap(y) ? 366 : 365)) {
		/* Guess a corrected year, assuming 365 days per year. */
		long yg = y + days/365;

		/* Adjust DAYS and Y to match the guessed year. */
		days -= (yg - y) * 365 + leaps_between(y, yg);
		y = yg;
	}
    tm.year = y - 1900;
    tm.days=days;

    const unsigned short *ip = __mon_yday[__isleap(y)];
	for (y = 11; days < ip[y]; y--)
		continue;
	days -= ip[y];

	tm.month = y;

    double dwhole = 367*tm.year - (int)(7*(tm.year+ (int)( (tm.month+9)/12))/4)+(int)(275*tm.month/9) + tm.days-730531.5;
    double dfrac = (tm.hour + tm.minutes/60 + tm.sec/3600)/24;
    return dwhole;
}

double SideralTime::GMST(time_t time) {
    return 280.46061837 + 360.98564736629 * julienCalendarElapsedDaysFractionSinceJ2000(time);
}

time_t SideralTime::makeTime(const unsigned int year0, const unsigned int mon0,
		const unsigned int day, const unsigned int hour,
		const unsigned int min, const unsigned int sec){

    unsigned int mon = mon0, year = year0;

	/* 1..12 -> 11,12,1..10 */
	if (0 >= (int) (mon -= 2)) {
		mon += 12;	/* Puts Feb last since it has leap day */
		year -= 1;
	}

	return ((((time_t)
		  (year/4 - year/100 + year/400 + 367*mon/12 + day) +
		  year*365 - 719499
	    )*24 + hour /* now have hours - midnight tomorrow handled here */
	  )*60 + min /* now have minutes */
	)*60 + sec; /* finally seconds */
}

