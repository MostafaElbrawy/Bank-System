#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
class clsUpdateRateScreen : protected clsScreen
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

	static void ShowUpdateRateScreen()
	{
		_DrawScreenHeader("\tUpdate Rate Screen");

		cout << "\nEnter Currency Code: ";
		string Code = clsInputValidate::ReadString();
		clsCurrency Currency = clsCurrency::FindByCode(Code);
		while (Currency.IsEmpty())
		{
			cout << "\nCode Does Not Exist, Enter Another Code:  ";
			Code = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCode(Code);
		}

		_PrintCurrency(Currency);

		cout << "\n\nAre You Sure Do You Want To Update This Currency's Rate (y/n): ";
		char sure;
		cin >> sure;
		if (sure == 'y' || sure == 'Y')
		{
			cout << "\nUpdate Currency's Rate: ";
			cout << "\n\n____________________________\n";
			cout << "Enter New Rate: ";
			float NewRate = clsInputValidate::ReadNumber<float>();
			Currency.UpdateRate(NewRate);
			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);
		}
		else
			cout << "\n\nOperation Cancelled";
	
	
	
	
	}






};

