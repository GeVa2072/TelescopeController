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
        inline double time();
        double GMST(time_t time);
        static time_t mktime(const unsigned int year0, const unsigned int mon0,
                                    const unsigned int day, const unsigned int hour,
                                    const unsigned int min, const unsigned int sec);
    protected:
        double julienCalendarElapsedDaysFractionSinceJ2000(time_t time);
        inline int keep_whole(double d) {
            return (int)d ;
        }
        inline double keep_fractional(double d) {
            return d - (int)d;
        }
        inline time_t keep_time(time_t t) {
            return t%(24*60*60);
        }
        inline time_t remove_time(time_t t) {
            return (t/24/60/60)*24*60*60;
        }
        double* getNbDays(time_t time);
    private:
        double sideralTime;
};

double SideralTime::time() {
    return sideralTime;
}

#endif // SIDERALTIME_H
