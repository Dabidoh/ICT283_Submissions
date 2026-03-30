#include "WeatherRecord.h"

WeatherRecord::WeatherRecord()
    : m_date(), m_time(), m_windSpeed(0.0f), m_solarRadiation(0.0f), m_temperature(0.0f)
{
}

WeatherRecord::WeatherRecord(const Date& d, const Time& t, float windSpeed, float solarRad, float temp)
    : m_date(d), m_time(t), m_windSpeed(windSpeed), m_solarRadiation(solarRad), m_temperature(temp)
{
}

Date WeatherRecord::GetDate() const
{
    return m_date;
}

Time WeatherRecord::GetTime() const
{
    return m_time;
}

float WeatherRecord::GetWindSpeed() const
{
    return m_windSpeed;
}

float WeatherRecord::GetSolarRadiation() const
{
    return m_solarRadiation;
}

float WeatherRecord::GetTemperature() const
{
    return m_temperature;
}

void WeatherRecord::SetDate(const Date& d)
{
    m_date = d;
}

void WeatherRecord::SetTime(const Time& t)
{
    m_time = t;
}

void WeatherRecord::SetWindSpeed(float speed)
{
    // Basic validation: Wind speed shouldn't be negative
    if (speed >= 0.0f) {
        m_windSpeed = speed;
    }
}

void WeatherRecord::SetSolarRadiation(float rad)
{
    // Basic validation: Solar radiation shouldn't be negative
    if (rad >= 0.0f) {
        m_solarRadiation = rad;
    }
}

void WeatherRecord::SetTemperature(float temp)
{
    m_temperature = temp;
}
