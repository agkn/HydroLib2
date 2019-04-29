//
// Created by Andrey on 28.04.2019.
//

#ifndef HYDROLIB2_CLOCK_H
#define HYDROLIB2_CLOCK_H

#include "hydro_types.h"

struct DateTime {
    const time_t SEC_IN_DAY = 24 * 3600;
    const uint8_t mYear;
    const uint8_t mMonth;
    const uint8_t mDay;
    const uint8_t mHour;
    const uint8_t mMinutes;
    const uint8_t mSeconds;

    DateTime(uint8_t aYear,  uint8_t aMonth, uint8_t aDay,
             uint8_t aHour, uint8_t aMinutes, uint8_t aSeconds):
            mYear(aYear), mMonth(aMonth), mDay(aDay),
            mHour(aHour), mMinutes(aMinutes), mSeconds(aSeconds) {};

    time_t daySeconds() const  {
        return mHour * 3600ul + mMinutes * 60 + mSeconds;
    }
};
class Clock {
public:
    DateTime now();
};


#endif //HYDROLIB2_CLOCK_H
