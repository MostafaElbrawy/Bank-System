#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsListClientsScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUserScreen.h"
#include "clsCurrencyExchangeScreen.h"
#include"clsListLoginRegisterScreen.h"
using namespace std;
class clsMainScreen : protected clsScreen
{

	enum enMainMenuList {
		ShowClient = 1, AddCLient = 2, DeleteClient = 3, UpdateClient = 4,
		FindClient = 5, Transactions = 6, ManageUser = 7, LoginRegister = 8, CurrencyExchange = 9, LogOut = 10
	};

	static short _ReadMainMenuOption()
	{
		cout << setw(37) << left << "" << "Choose What Do You Want to Do [1:10]: ";
		short Choice = clsInputValidate::ReadNumberBetween(1, 10, "\nInvalid Choice, Enter Number Between [1:10]: ");
		return Choice;
	}

	static void _ShowListClientScreen()
	{
		clsListClientsScreen::ShowListClientsScreen();
	}

	static void _ShowAddClientScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionScreen()
	{
		clsTransactionsScreen::ShowTransactionMenuScreen();
	}

	static void _ShowManageUserScreen()

	{
		clsManageUserScreen::ShowManageUserScreen();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsListLoginRegisterScreen::ShowListLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeScreen()
	{
		clsCurrencyExchangeScreen::ShowCurrencyExchangeMainMenu();
	}

	static void _PerformMainMenuOption(enMainMenuList Choice)
	{
		system("cls");

		switch (Choice)
		{
		case clsMainScreen::ShowClient:

			_ShowListClientScreen();
			break;

		case clsMainScreen::AddCLient:

			_ShowAddClientScreen();
			break;

		case clsMainScreen::DeleteClient:

			_ShowDeleteClientScreen();
			break;

		case clsMainScreen::UpdateClient:

			_ShowUpdateClientScreen();
			break;

		case clsMainScreen::FindClient:

			_ShowFindClientScreen();
			break;

		case clsMainScreen::Transactions:

			_ShowTransactionScreen();
			break;

		case clsMainScreen::ManageUser:

			_ShowManageUserScreen();
			break;

		case clsMainScreen::LoginRegister:

			_ShowLoginRegisterScreen();
			break;

		case clsMainScreen::CurrencyExchange:

			_ShowCurrencyExchangeScreen();
			break;

		case clsMainScreen::LogOut:

			return;
			break;
	
		}
		cout << "\n\n" << setw(37) << left << "" << "Press Any Key To Go Back To Main Menu....";
		system("pause>0");
		system("cls");
		ShowMainMenuScreen();

	}

public:
	static void ShowMainMenuScreen()
	{
		system("cls");
		_DrawScreenHeader("\t    Main Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t    Main Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformMainMenuOption(enMainMenuList(_ReadMainMenuOption()));

	}

};


