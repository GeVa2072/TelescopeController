#ifndef SIDERALTIMETEST_H_INCLUDED
#define SIDERALTIMETEST_H_INCLUDED

#include "SideralTime.h"

class SideralTimeTest : public SideralTime {
public:
    inline SideralTimeTest(time_t time) : SideralTime(time) { }
    inline double julienCalendarTest(time_t time) {
        return julienCalendarElapsedDaysFractionSinceJ2000(time);
    }
};

#endif // SIDERALTIMETEST_H_INCLUDED
