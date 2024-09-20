#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;
class clsCurrencyExchangeScreen : protected clsScreen
{
	enum enCurrencyExchangeOptions { ListCurrencies = 1, FindCurrency = 2, UpdateRate = 3, CurrencyCalculator = 4, MainMenu = 5 }; \

	static short ReadMenuOption()
	{
		cout << setw(37) << left << "" << "Choose What do you want to do [1:5]: ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Invalid Choice, Enter between[1:5]: ");
		return Choice;
	}

	static void _ShowListCurrenciesScreen()
	{
		clsListCurrenciesScreen::ShowListCurrenciesScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
		clsUpdateRateScreen::ShowUpdateRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void PerformCurrencyExchangeMenuOptions(enCurrencyExchangeOptions Choice)
	{
		system("cls");

		switch (Choice)
		{
		case ListCurrencies:

			_ShowListCurrenciesScreen();
			break;
		case FindCurrency:

			_ShowFindCurrencyScreen();
			break;

		case UpdateRate:

			_ShowUpdateRateScreen();
			break;

		case CurrencyCalculator:

			_ShowCurrencyCalculatorScreen();
			break;

		case MainMenu:
			return;

		}

		cout << "\n\n" << setw(37) << left << "" << "Press Any Key To Go Back To Currency Exchange Main Menu....";
		system("pause>0");
		system("cls");
		ShowCurrencyExchangeMainMenu();

	}

public:


	static void ShowCurrencyExchangeMainMenu()
	{


		_DrawScreenHeader("   Currency Exchange Main Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currecies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		PerformCurrencyExchangeMenuOptions(enCurrencyExchangeOptions(ReadMenuOption()));


	}



};

