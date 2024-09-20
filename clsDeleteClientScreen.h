#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;
class clsDeleteClientScreen : protected clsScreen
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

	static void ShowDeleteClientScreen()
	{

		if (!CheckPermissionRights(clsUser::pDeleteClient))
			return;

		_DrawScreenHeader("\tDelete Client Screen");

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
		cout << "\n\nAre You Sure Do You Want To Delete This Client (y/n): ";
		char sure;
		cin >> sure;
		if (sure == 'y' || sure == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\n\nAccount Deleted Successfully!";
				_PrintClientCard(Client);
			}
			else
				cout << "\n\nError, Account Was Not Deleted";
		}else
		cout << "\n\nAccount Was Not Deleted";
	}


};

