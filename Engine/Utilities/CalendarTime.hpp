#ifndef _CALENDARTIME_
#define _CALENDARTIME_

#ifdef _PC_
#include <time.h>
#endif

#include "Types.hpp"

/** 
 * Current local date and time.
 */
struct DateTime{
    /** Current year. */
    unsigned short year;
    /** Current month. [1-12] */
    byte month;
    /** Current day of month. */
    byte day;    

    /** 24 clock hour. [0-24) */
    byte hour;
    /** Minute of the hour. [0-60) */
    byte minute;
    /** Second of the minute. [0-60) */
    byte second;
};

/**
 * Static class used to get the calendar time and date.
 */
class CalendarTime{
private:
public:
    static DateTime getDateTime();
};

#endif