// Time.h

//---------------------------------------------------------------------------------

#ifndef TIME_H
#define TIME_H

//---------------------------------------------------------------------------------

#include <iostream>

    /**
     * @class Time
     * @brief Represents a specific time of day using hours and minutes.
     * * This class encapsulates the hours and minutes of a time, providing
     * methods to safely set, retrieve, and perform input/output operations
     * tailored to the HH:MM format found in the weather data.
     *
     * @author David Chew (35655813)
     * @date 25/02/2026
     * @version 1.0
     */
class Time {
public:
    /**
     * @brief Default constructor with optional parameters.
     * * Initializes the time. If no parameters are provided, it defaults to 00:00.
     * * @param h The hour to set (defaults to 0).
     * @param m The minute to set (defaults to 0).
     */
    Time(int h = 0, int m = 0);

    /**
     * @brief Retrieves the hour component of the time.
     * * @return The hour as an integer.
     */
    int GetHour() const;

    /**
     * @brief Retrieves the minute component of the time.
     * * @return The minute as an integer.
     */
    int GetMinute() const;

    /**
     * @brief Sets the time to the specified hour and minute.
     * * @param h The hour to set.
     * @param m The minute to set.
     */
    void SetTime(int h, int m);

private:
    int hours;   ///< The hour of the day (expected 0-23).
    int minutes; ///< The minute of the hour (expected 0-59).
};

    /**
     * @brief Overloaded input operator to read Time from an input stream.
     * * Expects the time to be in the format HH:MM. It reads the hour,
     * consumes the colon separator, and reads the minute.
     * * @param input The input stream (e.g., cin or an ifstream).
     * @param t The Time object to populate.
     * @return A reference to the modified input stream.
     */
std::istream& operator>>(std::istream& input, Time& t);

    /**
     * @brief Overloaded output operator to print Time to an output stream.
     * * Prints the time in the format HH:MM.
     * * @param output The output stream (e.g., cout or an ofstream).
     * @param t The Time object to output.
     * @return A reference to the modified output stream.
     */
std::ostream& operator<<(std::ostream& output, const Time& t);

#endif // TIME_H
