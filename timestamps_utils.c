#include "include/philo.h"

TimeMs time_now_ms(TimeMs start_time)
{
    struct timeval  tv;
    long long   time_in_ms;

    gettimeofday(&tv, NULL);
    time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time_in_ms - start_time);
}
