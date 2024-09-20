#pragma once
#include "clsScreen.h"
#include<iostream>
#include <iomanip>
#include "clsBankClient.h"
using namespace std;
class clsTransferLogScreen : protected clsScreen
{

	static void _PrintTransferLogRecord(clsBankClient::stTransferLog& Transfer)
	{
		cout << setw(8) << left << "" << "| " << setw(20) << left << Transfer.Date;
		cout << "| " << setw(10) << left << Transfer.SourceAccountNumber;
		cout << "| " << setw(10) << left << Transfer.DestinationAccountNumber;
		cout << "| " << setw(14) << left << Transfer.SourceBalance;
		cout << "| " << setw(14) << left << Transfer.DestinationBalance;
		cout << "| " << setw(14) << left << Transfer.Amount;
		cout << "| " << setw(10) << left << Transfer.UserName;
	}

public:

	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLog> vTransfersLogs = clsBankClient::GetTransferLogList();


		string Title = "\tTransfer Log Screen";
		string SubTitle = "\t(" + to_string(vTransfersLogs.size()) + ") Records(s)";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << setw(20) << left << "Date/Time";
		cout << "| " << setw(10) << left << "S.Acc.Num";
		cout << "| " << setw(10) << left << "D.Acc.Num";
		cout << "| " << setw(14) << left << "S.Balance";
		cout << "| " << setw(14) << left << "D.Balance";
		cout << "| " << setw(14) << left << "Amount";
		cout << "| " << setw(10) << left << "User";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;


		if (vTransfersLogs.size() == 0)
			cout << "\t\t\t\tNo Transfers Available In the System!";
		else

			for (clsBankClient::stTransferLog Transfer : vTransfersLogs)
			{

				_PrintTransferLogRecord(Transfer);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;
	}



};

