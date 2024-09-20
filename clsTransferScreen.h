#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iostream>
#include "clsInputValidate.h"

using namespace std;
class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClientCard(clsBankClient& Client)
	{
		cout << "\n\nClient Card:";
		cout << "\n_______________________";
		cout << "\nFull Name     : " << Client.FullName();
		cout << "\nAccount Number: " << Client.AccountNumber;
		cout << "\nBalance       : " << Client.Balance;
		cout << "\n_______________________\n";
	}

	static clsBankClient _GetValidAccount(string Massage)
	{
		cout <<Massage ;
		string AccountNumber = clsInputValidate::ReadString();
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		while (Client.IsEmpty())
		{
			cout << "\nAccount Number Was Not Found, Enter Another One: ";
			AccountNumber = clsInputValidate::ReadString();
			Client = clsBankClient::Find(AccountNumber);
		}
		return Client;

	}

	static double _ReadAmount(clsBankClient& Client)
	{
		cout << "\nEnter Amount To Transfer: ";
		double Amount = clsInputValidate::ReadPositiveNumber<double>("Invalid Amount, Enter Another Amount: ");
		while (Amount > Client.Balance)
		{
			cout << "Amount Exceeds Available Amount, Enter Antoher Amount: ";
			Amount = clsInputValidate::ReadPositiveNumber<double>("Invalid Amount, Enter Another Amount: ");
		}

		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t  Transfer Screen");

		clsBankClient SourceClient = _GetValidAccount("\nEnter Account Number To Transfer From: ");
		_PrintClientCard(SourceClient);
		clsBankClient DestinationClient = _GetValidAccount("\nEnter Account Number To Transfer To: ");
		_PrintClientCard(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		cout << "\n\nAre You Do You Want To Do This Transfer (y/n): ";
		char sure;
		cin >> sure;
	
		if (sure == 'y' || sure == 'Y')
		{
			if (SourceClient.Transfer(DestinationClient, Amount))
			{
				cout << "\n\nTransfer Done Successfully!";
				_PrintClientCard(SourceClient);
				_PrintClientCard(DestinationClient);
			}
			else
				cout << "\n\nError, Transfer Failed!";

		}
		else
			cout << "\n\nTransfer Was Cancelled";


	}

};

