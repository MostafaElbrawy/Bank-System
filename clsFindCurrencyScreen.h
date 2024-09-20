#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen :protected clsScreen
{

	static void _PrintCurrency(clsCurrency& Currency)
	{
		cout << "\n\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country;
		cout << "\nCode       : " << Currency.CurrencyCode;
		cout << "\nName       : " << Currency.CurrencyName;
		cout << "\nRate(1$) = : " << Currency.Rate;
		cout << "\n_____________________________\n";

	}


public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\tFind Currency Screen");
		clsCurrency Currency = clsCurrency::FindByCode("USD");

		cout << "\nDo Want To Find By [1]Code  [2]Country: ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 2, "Invalid Choice, Enter 1 Or 2: ");
		if (Choice == 1)
		{
			cout << "\nEnter Currency Code: ";
			string Code = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCode(Code);
			while (Currency.IsEmpty())
			{
				cout << "\nCode Does Not Exist, Enter Another Code:  ";
				Code = clsInputValidate::ReadString();
				Currency = clsCurrency::FindByCode(Code);
			}
		}
		else
		{

			cout << "\nEnter Country Name: ";
			string Country = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCode(Country);
			while (Currency.IsEmpty())
			{
				cout << "\nCountry Does Not Exist, Enter Another Code:  ";
				Country = clsInputValidate::ReadString();
				Currency = clsCurrency::FindByCountry(Country);
			}

		}

		cout << "\n\nCurrency Found!";
		_PrintCurrency(Currency);
		
	}

};

