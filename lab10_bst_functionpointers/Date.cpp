#include "Date.h"

Date::Date(int day, int month, int year)
    : m_day(1), m_month(1), m_year(2000)
{
    Set(day, month, year);
}

bool Date::Set(int day, int month, int year)
{
    if (month < 1 || month > 12)
    {
        return false;
    }

    if (day < 1 || day > 31)
    {
        return false;
    }

    if (year < 1900 || year > 2100)
    {
        return false;
    }

    m_day = day;
    m_month = month;
    m_year = year;
    return true;
}

int Date::GetDay() const
{
    return m_day;
}

int Date::GetMonth() const
{
    return m_month;
}

int Date::GetYear() const
{
    return m_year;
}

bool Date::IsValid() const
{
    return (m_month >= 1 && m_month <= 12) &&
           (m_day >= 1 && m_day <= 31) &&
           (m_year >= 1900 && m_year <= 2100);
}

std::istream& operator>>(std::istream& is, Date& date)
{
    int day;
    int month;
    int year;
    char slash1;
    char slash2;

    if (!(is >> day >> slash1 >> month >> slash2 >> year))
    {
        return is;
    }

    if (slash1 != '/' || slash2 != '/' || !date.Set(day, month, year))
    {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.GetDay() << '/' << date.GetMonth() << '/' << date.GetYear();
    return os;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.GetYear() != rhs.GetYear())
    {
        return lhs.GetYear() < rhs.GetYear();
    }

    if (lhs.GetMonth() != rhs.GetMonth())
    {
        return lhs.GetMonth() < rhs.GetMonth();
    }

    return lhs.GetDay() < rhs.GetDay();
}

bool operator>(const Date& lhs, const Date& rhs)
{
    return rhs < lhs;
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.GetDay() == rhs.GetDay() &&
           lhs.GetMonth() == rhs.GetMonth() &&
           lhs.GetYear() == rhs.GetYear();
}
