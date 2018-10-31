#ifndef SDK_FEATURE_TOOLSET_UTILS_TIMING_H_
#define SDK_FEATURE_TOOLSET_UTILS_TIMING_H_

#include <time.h>
#include <string>

typedef int64_t timevalue;

inline timevalue getCurrentTimeInMillis(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME , &ts) == 0)
    {
        return (timevalue)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    }
    else
    {
        return -1;
    }
}

inline std::string getCurrentTimeString(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0)
    {
        /*
         * struct tm contains all possible time values
         * (seconds, hour, day, year, timezone ...)
         */
        tm r;

        /* mapping timestamp to tm */
        localtime_r(&ts.tv_sec, &r);

        char buffer[50];
        /* specifier "%X" correspond to time format "14:55:02" */
        strftime(buffer, sizeof(buffer), "%X", &r);

        return buffer;
    }
    else {
        return "";
    }
}

#endif // SDK_FEATURE_TOOLSET_UTILS_TIMING_H_
