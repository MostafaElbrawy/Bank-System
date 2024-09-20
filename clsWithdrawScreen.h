#pragma once
#include "clsScreen.h"
#include"clsInputValidate.h"
#include <iostream>
#include "clsBankClient.h"
using namespace std;
class clsWithdrawScreen : protected clsScreen
{

	static void _PrintClientCard(clsBankClient& Client)
	{
		cout << "\n\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName     : " << Client.FirstName;
		cout << "\nLastName      : " << Client.LastName;
		cout << "\nFull Name     : " << Client.FullName();
		cout << "\nEmail         : " << Client.Email;
		cout << "\nPhone         : " << Client.Phone;
		cout << "\nAccount Number: " << Client.AccountNumber;
		cout << "\nPassword      : " << Client.Pincode;
		cout << "\nBalance       : " << Client.Balance;
		cout << "\n___________________\n";

	}

public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t  Withdraw Screen");

		cout << "\nEnter Account Number: ";
		string AccountNumber = clsInputValidate::ReadString();
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		while (Client.IsEmpty())
		{
			cout << "\nAccount Number Was Not Found, Enter Another One: ";
			AccountNumber = clsInputValidate::ReadString();
			Client = clsBankClient::Find(AccountNumber);
		}

		_PrintClientCard(Client);

		cout << "\nEnter Amount To Withdraw: ";
		double Amount = clsInputValidate::ReadNumberBetween<double>(1, Client.Balance, "Invalid Amount, Enter Another Amount: ");

		cout << "\n\nAre You Sure Do You Want To Perform This withdraw (y/n): ";
		char sure;
		cin >> sure;

		if (sure == 'y' || sure == 'Y')
		{
			if (Client.Withdraw(Amount))
			{
				cout << "\n\nWithdraw Done Succefully!";
				cout << "\nNew Balance = " << Client.Balance;
			}
			else
				cout << "\n\nWithdraw Failed";
		}
		else
			cout << "\n\nWithdraw Was Cancelled";

	}
};

