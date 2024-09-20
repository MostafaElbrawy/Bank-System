#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsPeriod.h"

using namespace std;

class clsInputValidate
{
public:

	template<typename T>
	static bool IsNumberBetween(T number, T from, T to)
	{
		return (number >= from && number <= to);
	}

	static bool IsDateBetween(clsDate date , clsDate dateFrom , clsDate dateTo)
	{
		if (dateFrom.IsDateAfterDate2(dateTo))
			return IsDateBetween(date,dateTo, dateFrom);

		return clsPeriod::isDateInPeriod(clsPeriod(dateFrom, dateTo), date);

	}
	
	template<typename T>
	static T ReadNumber(string Massage = "Invalid Number, Enter again : ")
	{
		T Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << Massage;
			
		}

		return Number;
	}
	
	template<typename T>
	static T ReadNumberBetween(T From, T To, string Massage)
	{
		T Number = ReadNumber<T>();
		while (!IsNumberBetween<T>(Number, From, To))
		{
			cout << Massage;
			Number = ReadNumber<T>();	
		}
		return Number;

	}

	template<typename T>
	static T ReadPositiveNumber(string Massage = "Invalid Number, Enter again: ")
	{
		T Number = ReadNumber<T>();
		while (Number < 1)
		{
			cout << Massage;
			Number = ReadNumber<T>();
		}
		return Number;

	}

	static string ReadString()
	{
		string s;
		getline(cin >> ws, s);
		return s;
	}

	static bool IsValidDate(clsDate date)
	{
		return clsDate::IsValidDate(date);
	}

};

