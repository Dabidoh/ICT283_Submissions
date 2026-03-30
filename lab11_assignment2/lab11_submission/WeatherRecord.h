// WeatherRecord.h

//---------------------------------------------------------------------------------

#ifndef WEATHER_RECORD_H
#define WEATHER_RECORD_H

//---------------------------------------------------------------------------------

#include "Date.h"
#include "Time.h"

//----------------------FOLLOW THE INDENTATION USED---

    /**
     * @class WeatherRecord
     * @brief  Stores weather sensor data for a specific date and time.
     * * This class encapsulates environmental readings including ambient
     * air temperature, solar radiation, and wind speed. It ensures data
     * integrity by providing controlled access through getters and setters.
     * * @author David Chew (35655813)
     * @version 01
     * @date 26/02/2026 David Chew, Started
     */
class WeatherRecord
{
public:
		/**
		 * @brief  Default constructor.
		 * * Initializes numeric values to 0.0f and uses default
		 * constructors for Date and Time.
		 */
	WeatherRecord();

        /**
         * @brief Parameterized constructor to initialize a fully formed WeatherRecord.
         * @param d The Date of the reading.
         * @param t The Time of the reading.
         * @param windSpeed The wind speed in km/h.
         * @param solarRad The solar radiation in W/m2.
         * @param temp The ambient air temperature in degrees Celsius.
         */
	WeatherRecord(const Date& d, const Time& t, float windSpeed, float solarRad, float temp);

		/**
		 * @brief  Retrieves the Date of the record.
		 * @return Date - The stored date.
		 */
	Date GetDate() const;

		/**
		 * @brief  Retrieves the Time of the record.
		 * @return Time - The stored time.
		 */
	Time GetTime() const;

		/**
		 * @brief  Retrieves the wind speed in km/h.
		 * @return float - The wind speed.
		 */
	float GetWindSpeed() const;

		/**
		 * @brief  Retrieves the solar radiation in W/m2.
		 * @return float - The solar radiation.
		 */
	float GetSolarRadiation() const;

		/**
		 * @brief  Retrieves the ambient air temperature in degrees Celsius.
		 * @return float - The temperature.
		 */
	float GetTemperature() const;

		/**
		 * @brief  Sets the date.
		 * @param  d - The Date object to set.
		 * @return void
		 */
	void SetDate(const Date& d);

		/**
		 * @brief  Sets the time.
		 * @param  t - The Time object to set.
		 * @return void
		 */
	void SetTime(const Time& t);

		/**
		 * @brief  Sets the wind speed.
		 * * @param  speed - The wind speed in km/h.
		 * @return void
		 */
	void SetWindSpeed(float speed);

		/**
		 * @brief  Sets the solar radiation.
		 * * @param  rad - The solar radiation in W/m2.
		 * @return void
		 */
	void SetSolarRadiation(float rad);

		/**
		 * @brief  Sets the ambient air temperature.
		 * * @param  temp - The temperature in degrees Celsius.
		 * @return void
		 */
	void SetTemperature(float temp);

private:
		/// The date of the reading
	Date m_date;
		/// The time of the reading
	Time m_time;
		/// Wind speed measured in km/h
	float m_windSpeed;
		/// Solar radiation measured in W/m2
	float m_solarRadiation;
		/// Ambient air temperature measured in degrees C
	float m_temperature;
};

#endif // WEATHER_RECORD_H
