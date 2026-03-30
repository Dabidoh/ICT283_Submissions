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

std::istream& operator>>(std::istream& input, Time& t) {
    int h, m;
    char colon; // Variable to temporarily hold the ':' character

    // Read the hour, then the colon separator, then the minute
    input >> h >> colon >> m;

    // Set the values into the object
    t.SetTime(h, m);

    return input;
}

std::ostream& operator<<(std::ostream& output, const Time& t) {
    // Outputs the time in HH:MM format
    output << t.GetHour() << ":" << t.GetMinute();

    return output;
}
