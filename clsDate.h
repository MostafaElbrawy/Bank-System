#pragma once
#pragma warning(disable : 4996)

#include <iomanip>
#include <string>
#include <ctime>
#include <vector>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
	short _Day;
	short _Month;
	short _Year;

	static clsDate _GetSystemDate()
	{
		short day, month, year;
		time_t t = time(0);
		tm* now = localtime(&t);


		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		day = now->tm_mday;

		return clsDate(day, month, year);
	}


	void _StringToDate(clsDate &date ,string sDate)
	{
		vector <string> vDate = clsString::Split(sDate, "/");
		
		date._Day = stoi(vDate[0]);
		date._Month = stoi(vDate[1]);
		date._Year = stoi(vDate[2]);

	}
	
	void _GetDateFromDayOrderInYear(clsDate &date , short dayOrderInYear, short year)
	{
		
		date._Year = year;
		short numberOfDaysInAMonth;
		short i = 1;
		for (i; i <= 12; i++)
		{
			if ((numberOfDaysInAMonth = NumberOfDaysInAMonth(year, i)) >= dayOrderInYear)
				break;

			dayOrderInYear -= numberOfDaysInAMonth;

		}
		date._Month = i;
		date._Day = dayOrderInYear;

	}

public:

	clsDate()
	{
		*this = _GetSystemDate();
	}

	clsDate(short day ,short month ,short year)
	{
		this->_Day = day;
		this->_Month= month;
		this->_Year = year;
	}

	clsDate(string sDate)
	{
		 _StringToDate(*this,sDate);
	}

	clsDate(short dayOrderInYear ,short year)
	{
		 _GetDateFromDayOrderInYear(*this,dayOrderInYear , year);
	}

	void setDay(short day)
	{
		this->_Day = day;
	}

	void setMonth(short month)
	{
		this->_Month = month;
	}

	void setYear(short year)
	{
		this->_Year = year;
	}

	short getDay()
	{
		return _Day;
	}

	short getMonth()
	{
		return _Month;
	}

	short getYear()
	{
		return _Year;
	}

	__declspec(property(put = setDay, get = getDay))short Day;

	__declspec(property(put = setMonth, get = getMonth))short Month;

	__declspec(property(put = setYear, get = getYear))short Year;

	static string GetSystemDateTimeString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		return to_string(now->tm_mday) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_year + 1900) + " - "
			+ to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);

	}

	static string DateToString(clsDate date)
	{
		return to_string(date._Day) + "/" + to_string(date._Month) + "/" + to_string(date._Year);
	}

	string ToString()
	{
		return DateToString(*this);
    }

	void Print()
	{
		cout << this->ToString() << '\n';
	}

	static bool IsLeapYear(short year)
	{
		return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
	}

	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInAMonth(short year, short month)
	{
		short arr[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return month == 2 ? (IsLeapYear(year) ? 29 : 28) : arr[month - 1];
	}

	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInAMonth(_Year, _Month);
	}

	static short HowManyDaysInAYear(short year)
	{
		return (IsLeapYear(year)) ? 366 : 365;
	}

	short HowManyDaysInTheYear()
	{
		return HowManyDaysInAYear(_Year);
	}
	
	static short GetDayOrderInWeek(short year, short month, short day)
	{
		short a, y, m;
		a = (14 - month) / 12;
		y = year - a;
		m = month + 12 * a - 2;

		return (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;

	}

	static short GetDayOrderInWeek(clsDate date)
	{
		return GetDayOrderInWeek(date._Year, date._Month, date._Day);

	}

	short DayOrderInWeek()
	{
		return GetDayOrderInWeek(*this);
	}

	static string GetDayName(short dayOrder)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[dayOrder];

	}

	string DayName()
	{
		return GetDayName(DayOrderInWeek());
	}

	static string GetMonthName(short month)
	{

		string months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return months[month - 1];


	}

	string MonthName()
	{
		return GetMonthName(_Month);
	}

	static void PrintMonthCelander(short year, short month)
	{

		short numberOfDays = NumberOfDaysInAMonth(year, month);
		short orderOfDay1 = GetDayOrderInWeek(year, month, 1);
		short counter = 0;

		printf("\n  _______________%s_______________\n\n", GetMonthName(month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");


		int i;

		for (i = 0; i < orderOfDay1; i++)
		{
			cout << "     ";
		}


		for (int j = 1; j <= numberOfDays; j++)
		{
			cout << setw(5) << j;

			if (++i == 7)
			{
				cout << '\n';
				i = 0;

			}


		}


		printf("\n  _________________________________\n");



	}

	void PrintMonthCelander()
	{
		PrintMonthCelander(_Year, _Month);
	}

	static void PrintYearCelander(short year)
	{
		printf("\n  _________________________________\n");
		cout << "\n\t Celander - " << year;
		printf("\n  _________________________________\n");


		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCelander(year, i);

		}

	}

	void PrintYearCelander()
	{
		PrintYearCelander(_Year);
	}

	static short NumberOfDaysFromBeginningOfTheYear(short year, short month, short days)
	{
		short totalDays = 0;

		for (int i = 1; i < month; i++)
			totalDays += NumberOfDaysInAMonth(year, i);

		totalDays += days;

		return totalDays;


	}

	short NumberOfDaysFromBeginningOfTheYear()
	{
		return  NumberOfDaysFromBeginningOfTheYear(_Year, _Month, _Day);
	}

	static clsDate AddDaysToDate(clsDate date, short daysToAdd)
	{
		short numberOfDaysInMonth;

		while (true)
		{
			numberOfDaysInMonth = NumberOfDaysInAMonth(date._Year, date._Month);

			if (daysToAdd > numberOfDaysInMonth - date._Day)
			{

				daysToAdd -= numberOfDaysInMonth - date._Day;
				date._Day = 0;

				if (date._Month == 12)
				{
					date._Year++;
					date._Month = 1;
				}
				else
					date._Month++;


			}
			else
			{
				date._Day += daysToAdd;
				return date;
			}



		}
	}

	void AddDays(short daysToAdd)
	{
		*this = AddDaysToDate(*this,daysToAdd);
	}

	static bool IsDate1BeforeDate2(clsDate date1, clsDate date2)
	{
		return  date1._Year == date2._Year ? (date1._Month == date2._Month ? date1._Day < date2._Day : date1._Month < date2._Month) : date1._Year < date2._Year;
	}

	bool IsDateBeforeDate2(clsDate date2)
	{
		return IsDate1BeforeDate2(*this, date2);
	}

	static bool IsDate1AfterDate2(clsDate date1, clsDate date2)
	{
		return  IsDate1BeforeDate2(date2, date1);
	}

	bool IsDateAfterDate2(clsDate date2)
	{
		return IsDate1BeforeDate2(date2, *this);
	}

	static bool IsDate1EqualDate2(clsDate date1, clsDate date2)
	{
		return (date1._Year == date2._Year && date1._Month == date2._Month && date1._Day == date2._Day);

	}

	bool IsDateEqualDate2(clsDate date2)
	{
		return IsDate1EqualDate2(*this, date2);
	}

	static bool IsLastDayInMonth(clsDate date)
	{
		return (date._Day == NumberOfDaysInAMonth(date._Year, date._Month));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(clsDate date)
	{
		return (date._Month == 12);
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(*this);
	}

	static int GetDifferenceInDays(clsDate date1, clsDate date2, bool IncludeEndDay = false)
	{
		int diff = 0;

		diff = NumberOfDaysFromBeginningOfTheYear(date2._Year, date2._Month, date2._Day) - NumberOfDaysFromBeginningOfTheYear(date1._Year, date1._Month, date1._Day);

		while (date1._Year < date2._Year)
		{

			diff += HowManyDaysInAYear(date1._Year);
			date1._Year++;
		}

		if (IncludeEndDay)
			return ++diff;

		return  diff;

	}

	int GetDifferenceInDays(clsDate date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, date2, IncludeEndDay);
	}

	// Function to increase the date by one day using reference
	static void IncreaseDateByOneDay(clsDate& date)
	{
		if (IsLastDayInMonth(date) && IsLastMonthInYear(date))
		{
			date._Year++;
			date._Month = 1;
			date._Day = 1;
		}
		else if (IsLastDayInMonth(date))
		{
			date._Month++;
			date._Day = 1;
		}
		else
		{
			date._Day++;
		}
	}

	// Member function to increase the current date object by one day
	void IncreaseByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	// Function to increase the date by 'x' days using reference
	static void IncreaseDateByXDays(clsDate& date, short days)
	{
		for (int i = 1; i <= days; i++)
		{
			IncreaseDateByOneDay(date);
		}
	}

	// Member function to increase the current date object by 'x' days
	void IncreaseByXDays(short days)
	{
		IncreaseDateByXDays(*this, days);
	}

	// Function to increase the date by one week using reference
	static void IncreaseDateByOneWeek(clsDate& date)
	{
		IncreaseDateByXDays(date, 7);
	}

	// Member function to increase the current date object by one week
	void IncreaseByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	// Function to increase the date by 'x' weeks using reference
	static void IncreaseDateByXWeeks(clsDate& date, short weeks)
	{
		for (int i = 1; i <= weeks; i++)
		{
			IncreaseDateByOneWeek(date);
		}
	}

	// Member function to increase the current date object by 'x' weeks
	void IncreaseByXWeeks(short weeks)
	{
		IncreaseDateByXWeeks(*this, weeks);
	}

	// Function to increase the date by one month using reference
	static void IncreaseDateByOneMonth(clsDate& date)
	{
		if (date._Month == 12)
		{
			date._Year++;
			date._Month = 1;
		}
		else
		{
			date._Month++;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(date._Year, date._Month);
		if (date._Day > NumberOfDaysInCurrentMonth)
		{
			date._Day = NumberOfDaysInCurrentMonth;
		}
	}

	// Member function to increase the current date object by one month
	void IncreaseByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	// Function to increase the date by 'x' months using reference
	static void IncreaseDateByXMonths(clsDate& date, short months)
	{
		for (int i = 1; i <= months; i++)
		{
			IncreaseDateByOneMonth(date);
		}
	}

	// Member function to increase the current date object by 'x' months
	void IncreaseByXMonths(short months)
	{
		IncreaseDateByXMonths(*this, months);
	}

	// Function to increase the date by one year using reference
	static void IncreaseDateByOneYear(clsDate& date)
	{
		date._Year++;
	}

	// Member function to increase the current date object by one year
	void IncreaseByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	// Function to increase the date by 'x' years using reference
	static void IncreaseDateByXYears(clsDate& date, short years)
	{
		date._Year += years;
	}

	// Member function to increase the current date object by 'x' years
	void IncreaseByXYears(short years)
	{
		IncreaseDateByXYears(*this, years);
	}

	// Function to increase the date by one decade using reference
	static void IncreaseDateByOneDecade(clsDate& date)
	{
		date._Year += 10;
	}

	// Member function to increase the current date object by one decade
	void IncreaseByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	// Function to increase the date by 'x' decades using reference
	static void IncreaseDateByXDecades(clsDate& date, short decades)
	{
		date._Year += (10 * decades);
	}

	// Member function to increase the current date object by 'x' decades
	void IncreaseByXDecades(short decades)
	{
		IncreaseDateByXDecades(*this, decades);
	}

	// Function to increase the date by one century using reference
	static void IncreaseDateByOneCentury(clsDate& date)
	{
		date._Year += 100;
	}

	// Member function to increase the current date object by one century
	void IncreaseByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	// Function to increase the date by one millennium using reference
	static void IncreaseDateByOneMillennium(clsDate& date)
	{
		date._Year += 1000;
	}

	// Member function to increase the current date object by one millennium
	void IncreaseByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	// Function to decrease the date by one day using reference
	static void DecreaseDateByOneDay(clsDate& date)
	{
		if (date._Day == 1)
		{
			if (date._Month == 1)
			{
				date._Month = 12;
				date._Day = 31;
				date._Year--;
			}
			else
			{
				date._Month--;
				date._Day = NumberOfDaysInAMonth(date._Year, date._Month);
			}
		}
		else
		{
			date._Day--;
		}
	}

	// Member function to decrease the current date object by one day
	void DecreaseByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	// Function to decrease the date by 'x' days using reference
	static void DecreaseDateByXDays(clsDate& date, short days)
	{
		for (int i = 1; i <= days; i++)
		{
			DecreaseDateByOneDay(date);
		}
	}

	// Member function to decrease the current date object by 'x' days
	void DecreaseByXDays(short days)
	{
		DecreaseDateByXDays(*this, days);
	}

	// Function to decrease the date by one week using reference
	static void DecreaseDateByOneWeek(clsDate& date)
	{
		DecreaseDateByXDays(date, 7);
	}

	// Member function to decrease the current date object by one week
	void DecreaseByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	// Function to decrease the date by 'x' weeks using reference
	static void DecreaseDateByXWeeks(clsDate& date, short weeks)
	{
		for (int i = 1; i <= weeks; i++)
		{
			DecreaseDateByOneWeek(date);
		}
	}

	// Member function to decrease the current date object by 'x' weeks
	void DecreaseByXWeeks(short weeks)
	{
		DecreaseDateByXWeeks(*this, weeks);
	}

	// Function to decrease the date by one month using reference
	static void DecreaseDateByOneMonth(clsDate& date)
	{
		if (date._Month == 1)
		{
			date._Year--;
			date._Month = 12;
		}
		else
		{
			date._Month--;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(date._Year, date._Month);
		if (date._Day > NumberOfDaysInCurrentMonth)
		{
			date._Day = NumberOfDaysInCurrentMonth;
		}
	}

	// Member function to decrease the current date object by one month
	void DecreaseByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	// Function to decrease the date by 'x' months using reference
	static void DecreaseDateByXMonths(clsDate& date, short months)
	{
		for (int i = 1; i <= months; i++)
		{
			DecreaseDateByOneMonth(date);
		}
	}

	// Member function to decrease the current date object by 'x' months
	void DecreaseByXMonths(short months)
	{
		DecreaseDateByXMonths(*this, months);
	}

	// Function to decrease the date by one year using reference
	static void DecreaseDateByOneYear(clsDate& date)
	{
		date._Year--;
	}

	// Member function to decrease the current date object by one year
	void DecreaseByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	// Function to decrease the date by 'x' years using reference
	static void DecreaseDateByXYears(clsDate& date, short years)
	{
		date._Year -= years;
	}

	// Member function to decrease the current date object by 'x' years
	void DecreaseByXYears(short years)
	{
		DecreaseDateByXYears(*this, years);
	}

	// Function to decrease the date by one decade using reference
	static void DecreaseDateByOneDecade(clsDate& date)
	{
		date._Year -= 10;
	}

	// Member function to decrease the current date object by one decade
	void DecreaseByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	// Function to decrease the date by 'x' decades using reference
	static void DecreaseDateByXDecades(clsDate& date, short decades)
	{
		date._Year -= (10 * decades);
	}

	// Member function to decrease the current date object by 'x' decades
	void DecreaseByXDecades(short decades)
	{
		DecreaseDateByXDecades(*this, decades);
	}

	// Function to decrease the date by one century using reference
	static void DecreaseDateByOneCentury(clsDate& date)
	{
		date._Year -= 100;
	}

	// Member function to decrease the current date object by one century
	void DecreaseByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	// Function to decrease the date by one millennium using reference
	static void DecreaseDateByOneMillennium(clsDate& date)
	{
		date._Year -= 1000;
	}

	// Member function to decrease the current date object by one millennium
	void DecreaseByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	static void SwapDates(clsDate &date1, clsDate &date2)
	{
		clsDate flag = date1;
		date1 = date2;
		date2 = flag;
	}

	void Swap(clsDate& date)
	{
		SwapDates(*this, date);
	}

	static bool IsValidDate(clsDate date)
	{
		return !(date._Month > 12 || date._Month < 1 || date._Day > NumberOfDaysInAMonth(date._Year, date._Month) || date._Day < 1);

	}

	bool IsValid()
	{
		return IsValidDate(*this);

	}

	static bool IsEndOfWeek(clsDate date)
	{
		return (GetDayOrderInWeek(date) == 6);

	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate date)
	{
		short DayIndex = GetDayOrderInWeek(date);
		return (DayIndex == 5 || DayIndex == 6);

	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate date)
	{
		return (!IsWeekEnd(date));
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate date)
	{
		return (6 - GetDayOrderInWeek(date));
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate date)
	{
		return NumberOfDaysInAMonth(date._Year, date._Month) - date._Day;
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate date)
	{
		return HowManyDaysInAYear(date._Year) - NumberOfDaysFromBeginningOfTheYear(date._Year, date._Month, date._Day);

	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateVacationDays(clsDate dateFrom, clsDate dateTo)
	{
		short days = 0;

		while (IsDate1BeforeDate2(dateFrom, dateTo))
		{

			if (IsBusinessDay(dateFrom))
				days++;

			IncreaseDateByOneDay(dateFrom);

		}

		return days;
	}

	short CalculateVacationDays(clsDate dateTo)
	{
		return CalculateVacationDays(*this, dateTo);
	}

	static clsDate CalculateVacationReturnDate(clsDate dateFrom, short vacationDays)
	{


		while (vacationDays > 0)
		{
			if (IsBusinessDay(dateFrom))
				vacationDays--;

			IncreaseDateByOneDay(dateFrom);

		}
		return dateFrom;


	}

};

