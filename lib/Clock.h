//
// Created by Andrey on 28.04.2019.
//

#ifndef HYDROLIB2_CLOCK_H
#define HYDROLIB2_CLOCK_H

#include "hydro_types.h"

#define SEC_PER_HOUR (3600)
#define SEC_PER_DAY (24 * 3600)
#define DAYS_PER_YEAR 365
#define SEC_PER_YEAR (SEC_PER_DAY * DAYS_PER_YEAR)

struct DateTime {
    const static time_t SEC_IN_DAY = 24 * 3600;
    uint8_t mYear; // years since 2000
    uint8_t mMonth; // month starting from 1
    uint8_t mDay; // Day of month starting from 1
    uint8_t mHour; // 0 - 23
    uint8_t mMinute; // 0 - 59
    uint8_t mSecond; // 0 - 59

    DateTime(uint8_t aYear,  uint8_t aMonth, uint8_t aDay,
             uint8_t aHour, uint8_t aMinutes, uint8_t aSeconds);

    time_t daySeconds() const  {
        return mHour * 3600ul + mMinute * 60 + mSecond;
    }
    time_t getUtc() const ;
    static DateTime createFromUtc(time_t aTicks);
};

class Clock {
public:
    static void setNow(DateTime aNow);
    static const DateTime & now();
};

time_t dateTime2Seconds(const DateTime &aDateTime);

#endif //HYDROLIB2_CLOCK_H
