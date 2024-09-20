#pragma once
#include "clsScreen.h"
#include"clsInputValidate.h"
#include <iostream>
#include "clsBankClient.h"
using namespace std;
class clsDepositScreen : protected clsScreen
{
private:

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

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t   Deposit Screen");

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
		cout << "\nEnter Amount to Deposit: ";
		double Amount = clsInputValidate::ReadNumber<double>("Invalid  Amount, Enter Another Amonut: ");

		cout << "\n\nAre You Sure Do You Want To Perform This Deposit (y/n): ";
		char sure;
		cin >> sure;

		if (sure == 'y' || sure == 'Y')
		{
			Client.Deposit(Amount);
			cout << "\n\nDeposit Done Succefully!";
			cout << "\nNew Balance = " << Client.Balance;
		}
		else
			cout << "\n\nDeposit Was Cancelled";
	}


};

