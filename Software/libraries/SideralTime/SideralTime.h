#ifndef SIDERALTIME_H
#define SIDERALTIME_H

#ifndef _TIME_T_DEFINED
typedef long time_t;
#endif

struct tm_time {
    int year;
    int month;
    int days;
    int hour;
    int minutes;
    int sec;
};

class SideralTime
{
    public:
        SideralTime(time_t time);
        virtual ~SideralTime();
        inline time_t time();
        double GMST(time_t time);
        static time_t makeTime(const unsigned int year0, const unsigned int mon0,
                                    const unsigned int day, const unsigned int hour,
                                    const unsigned int min, const unsigned int sec);
    protected:
        time_t julienCalendarElapsedDaysFractionSinceJ2000(time_t time);
    private:
        time_t sideralTime;
};

time_t SideralTime::time() {
    return sideralTime;
}

#endif // SIDERALTIME_H
