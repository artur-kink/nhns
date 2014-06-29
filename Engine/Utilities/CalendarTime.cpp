#include "CalendarTime.hpp"

/**
 * Get the current system DateTime.
 * @return Returns Date and Time of the system.
 */
DateTime CalendarTime::getDateTime(){
#ifdef _PC_
    DateTime dt;
    time_t curTime = time(0);
    struct tm* _time = localtime(&curTime);
    dt.year = _time->tm_year;
    dt.month = _time->tm_mon + 1;
    dt.day = _time->tm_mday;
    dt.hour = _time->tm_hour;
    dt.minute = _time->tm_min;
    dt.second = _time->tm_sec;
    return dt;
#endif
}   