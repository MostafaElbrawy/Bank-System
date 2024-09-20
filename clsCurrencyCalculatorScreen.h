#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen :protected clsScreen
{

    static clsCurrency _GetValidCurrency(string Masseage = "\nEnter Currency Code: ")
    {
		cout << Masseage;
		string Code = clsInputValidate::ReadString();
		clsCurrency Currency = clsCurrency::FindByCode(Code);
		while (Currency.IsEmpty())
		{
			cout << "\nCode Does Not Exist, Enter Another Code:  ";
			Code = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCode(Code);
		}
		return Currency;
    }

	static void _PrintCurrency(clsCurrency& Currency ,string Massage = "\n\nCurrency Card:\n")
	{
		cout << Massage;
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country;
		cout << "\nCode       : " << Currency.CurrencyCode;
		cout << "\nName       : " << Currency.CurrencyName;
		cout << "\nRate(1$) = : " << Currency.Rate;
		cout << "\n_____________________________\n";

	}

	static void _Calculator()
	{
		clsCurrency CurrencyFrom = _GetValidCurrency("\nEnter Currency1 Code: ");
		clsCurrency CurrencyTo = _GetValidCurrency("\nEnter Currency2 Code : ");
		cout << "\nEnter Amount to Exchange: ";
		float Amount = clsInputValidate::ReadPositiveNumber<float>("Invalid Amount, Enter Another Amount: ");

		_PrintCurrency(CurrencyFrom , "\n\nCoverting From: \n");

		cout<<"\n" << Amount << " " << CurrencyFrom.CurrencyCode << " = " << CurrencyFrom.ConvertToUSD(Amount) << " USD";

		if (CurrencyTo.CurrencyCode == "USD")
			return;
		cout << "\n\nConverting From USD To";
		_PrintCurrency(CurrencyTo, "\n\nCoverting To: \n");

		 cout << "\n" << Amount << " " << CurrencyFrom.CurrencyCode << " = " << CurrencyFrom.ConvertToAnyCurrency(CurrencyTo,Amount) << " "<<CurrencyTo.CurrencyCode;



	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		char again = 'n';
		do 
		{
			system("cls");
			_DrawScreenHeader("    Currency Calculator Screen");
			_Calculator();
			cout << "\n\nDo You Want To Do Another Calculation (y/n): ";
			cin >> again;
		
		} while (again == 'y' || again == 'Y');
	}



};

