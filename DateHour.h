#ifndef DATE_HOUR_H
#define DATE_HOUR_H

#include <string>
#include "DateHourFormat.h"

namespace TransactionReader
{
	const DateHourFormat APP_DATE_HOUR_FORMAT = DateHourFormat::UnitedStates;

	class DateHour
	{
	public:
		int day{ 0 }, month{ 0 }, year{ 0 }, hour{ 0 }, minute{ 0 };

		DateHour();
		DateHour(int t_day, int t_month, int t_year, int t_hour, int t_minute);
		std::string toString();
		static DateHour parseToDateHour(std::string t_contentToParse);
	};
}

#endif
