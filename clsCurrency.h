#pragma once
#include <iostream>
#include "clsString.h"
#include <fstream>
#include <string>
using namespace std;
class clsCurrency
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string line, string separator = "#//#")
	{
		vector <string> vCurrencyData = clsString::Split(line, separator);

		return clsCurrency(UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));

	}

	string _ConvertCurrencyObjectToLine(clsCurrency Currency, string separator = "#//#")
	{
		return Currency._Country + separator + Currency._CurrencyCode + separator + Currency._CurrencyName
			+ separator + to_string(Currency._Rate);
	}

	static vector <clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector <clsCurrency> vCurrencies;

		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				if (line != "")
					vCurrencies.push_back(_ConvertLineToCurrencyObject(line));

			}
			file.close();
		}

		return vCurrencies;

	}

	void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrencies)
	{
		fstream file;
		file.open("Currencies.txt", ios::out);

		if (file.is_open())
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				file << _ConvertCurrencyObjectToLine(Currency) << '\n';
			}
			file.close();
		}

	}

	static clsCurrency _GetEmptyCurrency()
	{
		return clsCurrency(EmptyMode, "", "", "", 0);
	}

	void _Update()
	{
		vector <clsCurrency> vCurrencies = _LoadCurrencyDataFromFile();

		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency._CurrencyCode == _CurrencyCode)
			{
				Currency = *this;
				break;
			}
		}
		_SaveCurrenciesDataToFile(vCurrencies);

	}


public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}


	bool IsEmpty()
	{
		return (_Mode == EmptyMode);
	}

	string getCountry()
	{
		return _Country;
	}
	__declspec(property(get = getCountry)) string Country;

	string getCurrencyCode()
	{
		return _CurrencyCode;
	}
	__declspec (property(get = getCurrencyCode)) string CurrencyCode;

	string getCurrencyName()
	{
		return _CurrencyName;
	}
	__declspec (property(get = getCurrencyName)) string CurrencyName;


	float getRate()
	{
		return _Rate;
	}
	__declspec (property(get = getRate)) float Rate;

	void UpdateRate(float Rate)
	{
		_Rate = Rate;
		_Update();
	}

	static clsCurrency FindByCode(string Code)
	{
		Code = clsString::UpperAll(Code);

		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open())
		{
			string line; 
			while (getline(file, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);
				if (Currency._CurrencyCode == Code)
				{
					file.close();
					return Currency;
				}
			}
			file.close();
			return _GetEmptyCurrency();
		}

	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAll(Country);

		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);
				if (clsString::UpperAll(Currency._Country) == Country)
				{
					file.close();
					return Currency;
				}
			}
			file.close();
			return _GetEmptyCurrency();
		}

	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return Amount / _Rate;
	}

	float ConvertToAnyCurrency(clsCurrency CurrencytTo, float Amount)
	{
		return ConvertToUSD(Amount) * CurrencytTo._Rate;
	}
};

