#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
class clsListCurrenciesScreen : protected clsScreen
{
private:

	static void _PrintCurrencyRecord(clsCurrency& Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country;
		cout << "| " << setw(10) << left << Currency.CurrencyCode;
		cout << "| " << setw(40) << left << Currency.CurrencyName;
		cout << "| " << setw(8) << left << Currency.Rate;

	}


public:

	static void ShowListCurrenciesScreen()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		string Title = "\tList Currency Screen";
		string SubTitle = "\t  (" + to_string(vCurrencies.size()) + ") Currrency";
		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << setw(30) << left << "Country";
		cout << "| " << setw(10) << left << "Code";
		cout << "| " << setw(40) << left << "Name";
		cout << "| " << setw(8) << left << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		for (clsCurrency Currency : vCurrencies)
		{

			_PrintCurrencyRecord(Currency);
			cout << endl;
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;
	}






};
