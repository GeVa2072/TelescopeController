#ifndef SIDERALTIMETEST_H_INCLUDED
#define SIDERALTIMETEST_H_INCLUDED

#include "SideralTime.h"

class SideralTimeTest : public SideralTime {
public:
    inline SideralTimeTest(time_t time) : SideralTime(time) { }
    inline double julienCalendarTest(time_t time) {
        return julienCalendarElapsedDaysFractionSinceJ2000(time);
    }
    inline int keep_wholeTest(double d) {
        return keep_whole(d);
    }

    inline double keep_fractionalTest(double d) {
        return keep_fractional(d);
    }

    inline time_t keep_timeTest(time_t t) {
        return keep_time(t);
    }

    inline time_t remove_timeTest(time_t t) {
        return remove_time(t);
    }
    inline double* getNbDaysTest(time_t time) {
        return getNbDays(time);
    }
};

#endif // SIDERALTIMETEST_H_INCLUDED
