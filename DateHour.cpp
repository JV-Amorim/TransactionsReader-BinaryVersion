#include <iostream>
#include "DateHour.h"

using namespace std;

namespace TransactionReader
{
	DateHour::DateHour()
	{
	}

	DateHour::DateHour(int t_day, int t_month, int t_year, int t_hour, int t_minute)
	{
		day = t_day;
		month = t_month;
		year = t_year;
		hour = t_hour;
		minute = t_minute;
	}

	string DateHour::toString()
	{
		string resultDateHour = "";

		string resultDay = to_string(day);
		string resultMonth = to_string(month);
		string resultHour = to_string(hour);
		string resultMinute = to_string(minute);

		if (resultDay.size() == 1)
		{
			resultDay = "0" + resultDay;
		}
		if (resultMonth.size() == 1)
		{
			resultMonth = "0" + resultMonth;
		}
		if (resultHour.size() == 1)
		{
			resultHour = "0" + resultHour;
		}
		if (resultMinute.size() == 1)
		{
			resultMinute = "0" + resultMinute;
		}

		if (APP_DATE_HOUR_FORMAT == DateHourFormat::Brazil)
		{
			resultDateHour = resultDay + "/" + resultMonth + "/" + to_string(year) + " " + resultHour + ":" + resultMinute;
		}
		else if (APP_DATE_HOUR_FORMAT == DateHourFormat::UnitedStates)
		{
			resultDateHour = resultMonth + "/" + resultDay + "/" + to_string(year) + " " + resultHour + ":" + resultMinute;
		}
		else
		{
			cout << "O formato de data e hora nao foi definido na aplicacao. Nao sera possivel continuar." << endl;
			abort();
		}

		return resultDateHour;
	}

	DateHour DateHour::parseToDateHour(string t_contentToParse)
	{
		DateHour dateHour;

		char* contentCopy = _strdup(t_contentToParse.c_str());
		char* context = NULL;

		if (APP_DATE_HOUR_FORMAT == DateHourFormat::Brazil)
		{
			dateHour.day = stoi(strtok_s(contentCopy, "/", &context));
			dateHour.month = stoi(strtok_s(NULL, "/", &context));
			dateHour.year = stoi(strtok_s(NULL, " ", &context));
			dateHour.hour = stoi(strtok_s(NULL, ":", &context));
			dateHour.minute = stoi(strtok_s(NULL, "\0", &context));
		}
		else if (APP_DATE_HOUR_FORMAT == DateHourFormat::UnitedStates)
		{
			dateHour.month = stoi(strtok_s(contentCopy, "/", &context));
			dateHour.day = stoi(strtok_s(NULL, "/", &context));
			dateHour.year = stoi(strtok_s(NULL, " ", &context));
			dateHour.hour = stoi(strtok_s(NULL, ":", &context));
			dateHour.minute = stoi(strtok_s(NULL, "\0", &context));
		}
		else
		{
			cout << "O formato de data e hora nao foi definido na aplicacao. Nao sera possivel continuar." << endl;
			abort();
		}

		free(contentCopy);

		return dateHour;
	}
}
