#pragma once
#include "clsScreen.h"
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include"clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{

	enum enTransactionsList { Deposit = 1, Withdraw = 2, TotalBalances = 3, Transfer = 4, TransferLog = 5, MainMenuScreen = 6 };

	static short _ReadTransactionsMenuOption()
	{
		cout << setw(37) << left << "" << "Choose What Do You Want to Do [1:6]: ";
		short Choice = clsInputValidate::ReadNumberBetween(1, 6, "\nInvalid Choice, Enter Number Between [1:6]: ");
		return Choice;
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalancesList();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PerformTransactionsMenuOptions(enTransactionsList Choice)
	{
		system("cls");

		switch (Choice)
		{
		case clsTransactionsScreen::Deposit:
			
			_ShowDepositScreen();
			break;

		case clsTransactionsScreen::Withdraw:
			
			_ShowWithdrawScreen();
			break;

		case clsTransactionsScreen::TotalBalances:
			
			_ShowTotalBalancesScreen();
			break;

		case clsTransactionsScreen::Transfer:
			
			_ShowTransferScreen();
			break;

		case clsTransactionsScreen::TransferLog:
			
			_ShowTransferLogScreen();
			break;

		case clsTransactionsScreen::MainMenuScreen:
			
			return;

		}
		cout<<"\n\n" << setw(37) << left << "" << "Press Any Key To Go Back To Transactions Menu...";
		system("pause>0");
		system("cls");
		ShowTransactionMenuScreen();

	}

public:

	static void ShowTransactionMenuScreen()
	{
		if (!CheckPermissionRights(clsUser::pTranactions))
			return;

		_DrawScreenHeader("\t  Transactions Menu");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformTransactionsMenuOptions(enTransactionsList(_ReadTransactionsMenuOption()));
	}
};

