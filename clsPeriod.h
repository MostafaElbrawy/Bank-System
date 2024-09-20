#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsString.h"


class clsPeriod
{

private :
	clsDate _StartDate , _EndDate;

public:
	clsPeriod(clsDate startDate, clsDate endDate)
	{
		_StartDate = startDate;
		_EndDate = endDate;
	}

	void setStartDate(clsDate startDate)
	{
		_StartDate = startDate;
	}

	clsDate getStartDate()
	{
		return _StartDate;
	}

	void setEndDate(clsDate endDate)
	{
		_EndDate = endDate;
	}

	clsDate getEndDate()
	{
		return _EndDate;
	}

	void Print()
	{
		cout << "\nPeriod Starts: \n";
		_StartDate.Print();

		cout << "\nPeriod Ends: \n";
		_EndDate.Print();

	}

	static bool IsPeriod1OverlapsPeriod2(clsPeriod period1, clsPeriod period2)
	{
		return !(clsDate::IsDate1BeforeDate2(period1._EndDate, period2._StartDate) || clsDate::IsDate1BeforeDate2(period2._EndDate, period1._StartDate));
	}

	bool IsPeriodOverlapsPeriod2(clsPeriod period2)
	{
		return IsPeriod1OverlapsPeriod2(*this, period2);
	}

	static int PeriodLengthInDays(clsPeriod period, bool IncludeEndDay = false)
	{
		return clsDate::GetDifferenceInDays(period._StartDate, period._EndDate, IncludeEndDay);
	}

	int LengthInDays( bool IncludeEndDay = false)
	{
		return PeriodLengthInDays(*this, IncludeEndDay);
	}

	static bool isDateInPeriod(clsPeriod period, clsDate date)
	{
		return !(clsDate::IsDate1BeforeDate2(date, period._StartDate) || clsDate::IsDate1AfterDate2(date, period._EndDate));
	}

	bool isDateInPeriod(clsDate date)
	{
		return isDateInPeriod(*this, date);
	}

	static short CountOverlapDays(clsPeriod period1, clsPeriod period2)
	{
		if (!IsPeriod1OverlapsPeriod2(period1, period2))
			return 0;

		if ((clsDate::IsDate1EqualDate2(period1._EndDate, period2._StartDate)) || (clsDate::IsDate1EqualDate2(period2._EndDate, period1._StartDate)))
			return 1;

		clsDate overlapStart = clsDate::IsDate1AfterDate2(period1._StartDate, period2._StartDate) ? period1._StartDate : period2._StartDate;
		clsDate overlapEnd = clsDate::IsDate1BeforeDate2(period1._EndDate, period2._EndDate) ? period1._EndDate : period2._EndDate;

		return clsDate::GetDifferenceInDays(overlapStart, overlapEnd);



	}

	short CountOverlapDays(clsPeriod period2)
	{
		return CountOverlapDays(*this, period2);
	}



};

