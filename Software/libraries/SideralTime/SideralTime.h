#ifndef SIDERALTIME_H
#define SIDERALTIME_H

#include "../Time/Time.h"

class SideralTime
{
    public:
        SideralTime(time_t time);
        virtual ~SideralTime();
        inline time_t time();
    protected:
    private:
        time_t sideralTime;
};

time_t SideralTime::time() {
    return sideralTime;
}

#endif // SIDERALTIME_H
