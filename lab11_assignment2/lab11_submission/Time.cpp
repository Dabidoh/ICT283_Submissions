#include "Time.h"

Time::Time(int h, int m) : hours(h), minutes(m) {}

int Time::GetHour() const {
    return hours;
}

int Time::GetMinute() const {
    return minutes;
}

void Time::SetTime(int h, int m) {
    hours = h;
    minutes = m;
}

std::istream& operator>>(std::istream& input, Time& t)
{
    int h = 0;
    int m = 0;
    char colon = '\0';

    if (!(input >> h >> colon >> m))
    {
        return input;
    }

    if (colon != ':' || h < 0 || h > 23 || m < 0 || m > 59)
    {
        input.setstate(std::ios::failbit);
        return input;
    }

    t.SetTime(h, m);
    return input;
}

std::ostream& operator<<(std::ostream& output, const Time& t) {
    // Outputs the time in HH:MM format
    output << t.GetHour() << ":" << t.GetMinute();

    return output;
}
