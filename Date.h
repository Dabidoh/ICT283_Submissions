#ifndef DATE_H
#define DATE_H

#include <iostream>

/**
 * @class Date
 * @brief Represents a calendar date.
 *
 * This class encapsulates a simple date consisting of day, month, and year.
 */
class Date
{
public:
    /**
     * @brief Constructor with default parameters.
     * @param day Day of the month.
     * @param month Month of the year.
     * @param year Year value.
     */
    Date(int day = 1, int month = 1, int year = 2000);

    /**
     * @brief Sets the date if the values are valid.
     * @param day Day of the month.
     * @param month Month of the year.
     * @param year Year value.
     * @return true if the date was set, false otherwise.
     */
    bool Set(int day, int month, int year);

    /**
     * @brief Gets the day.
     * @return The day value.
     */
    int GetDay() const;

    /**
     * @brief Gets the month.
     * @return The month value.
     */
    int GetMonth() const;

    /**
     * @brief Gets the year.
     * @return The year value.
     */
    int GetYear() const;

    /**
     * @brief Checks whether the current date is valid.
     * @return true if valid, false otherwise.
     */
    bool IsValid() const;

private:
    int m_day;
    int m_month;
    int m_year;
};

/**
 * @brief Extracts a date from an input stream.
 * @param is Input stream.
 * @param date Date object to read into.
 * @return Reference to the input stream.
 */
std::istream& operator>>(std::istream& is, Date& date);

/**
 * @brief Inserts a date into an output stream.
 * @param os Output stream.
 * @param date Date object to output.
 * @return Reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const Date& date);

/**
 * @brief Compares two dates for chronological ordering.
 * @param lhs Left-hand date.
 * @param rhs Right-hand date.
 * @return true if lhs is earlier than rhs, false otherwise.
 */
bool operator<(const Date& lhs, const Date& rhs);

/**
 * @brief Compares two dates for chronological ordering.
 * @param lhs Left-hand date.
 * @param rhs Right-hand date.
 * @return true if lhs is later than rhs, false otherwise.
 */
bool operator>(const Date& lhs, const Date& rhs);

/**
 * @brief Compares two dates for equality.
 * @param lhs Left-hand date.
 * @param rhs Right-hand date.
 * @return true if both dates are equal, false otherwise.
 */
bool operator==(const Date& lhs, const Date& rhs);

#endif
