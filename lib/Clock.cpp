//
// Created by Andrey on 28.04.2019.
//

#include <ctime>
#include "Clock.h"

static  const uint8_t monthDays[]={31, 28,31,30,31,30,31,31,30,31,30,31};

#define LEAP_YEARS(Y) ((Y) / 4 + (Y) / 100 - (Y) / 400)
#define LEAP_YEARS_SINCE_1970(YEAR) (LEAP_YEARS(1970 + YEAR) - LEAP_YEARS(1970))
#define IS_LEAP_YEAR(Y)    ( !( (Y) % 4 ) && ( ((Y) % 100 ) || !( (Y) % 400 ) ) )

DateTime sNow = DateTime::createFromUtc(0);

DateTime::DateTime(uint8_t aYear, uint8_t aMonth, uint8_t aDay, uint8_t aHour, uint8_t aMinutes, uint8_t aSeconds) :
        mYear(aYear), mMonth(aMonth), mDay(aDay),
        mHour(aHour), mMinute(aMinutes), mSecond(aSeconds) {}

time_t DateTime::getUtc() const {

    // At first, seconds sync month the current month
    time_t seconds = (mDay - 1) * SEC_PER_DAY + daySeconds() + (mYear + 30)  * SEC_PER_YEAR;

    // add previous months
    for(int i = 1; i < mMonth; i++) {
        seconds += monthDays[i - 1] * SEC_PER_DAY;
    }
    // Decide if current leap year can affect calculation.
    int years = mYear + ((mMonth < 3) ? 2000 - 1: 2000);
    // add additional days of the leap years.
    seconds +=  (LEAP_YEARS (years) - LEAP_YEARS(1970)) * SEC_PER_DAY;

    return seconds;
}

DateTime DateTime::createFromUtc(time_t aTicks) {
    uint8_t second = static_cast<uint8_t>(aTicks % 60);
    aTicks /= 60; // now it is minutes
    uint8_t minute = static_cast<uint8_t>(aTicks % 60);
    aTicks /= 60; // now it is hours
    uint8_t hour = static_cast<uint8_t>(aTicks % 24);
    aTicks /= 24; // now it is days

    int tmp = static_cast<int>(aTicks / DAYS_PER_YEAR); // years since 1970
    aTicks = (aTicks % DAYS_PER_YEAR); // Days since the year
    aTicks -= LEAP_YEARS_SINCE_1970(tmp - 1); // take into the account number of leap years before.
    // Correct the year.
    if (aTicks < 0) {
        aTicks += DAYS_PER_YEAR;
        tmp --;
    }
    uint8_t year = static_cast<uint8_t>(tmp - 30); // years since 2000
    uint8_t month, day = 1;
    for(month = 0; month < 12; month++) {
        int m = (month == 1) && IS_LEAP_YEAR(2000 + year) ? 29 : monthDays[month];
        if (aTicks < m) {
            day = static_cast<uint8_t>(aTicks + 1);
            break;

        } else {
            aTicks -= m;
        }
    }
    return {year, static_cast<uint8_t>(month + 1), day, hour, minute, second};
}

const DateTime & Clock::now() {
    return sNow;
}

void Clock::setNow(DateTime aNow) {
    sNow = aNow;
}
