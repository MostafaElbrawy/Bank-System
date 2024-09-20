#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;
class clsUpdateClientScreen : protected clsScreen
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

	static void _ReadClientInfo(clsBankClient& Client)
	{

		cout << "\nEnter Frist Name: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone Number: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Pincode: ";
		Client.Pincode = clsInputValidate::ReadString();

		cout << "\nEnter Balance: ";
		Client.Balance = clsInputValidate::ReadPositiveNumber<double>();

	}


public:

	static void ShowUpdateClientScreen()
	{

		if (!CheckPermissionRights(clsUser::pUpdateClients))
			return;

		_DrawScreenHeader("\tUpdate Client Screen");

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
		cout << "\nUpdate Client Info: ";
		cout << "\n\n____________________________\n";
		_ReadClientInfo(Client);
		
		switch (Client.Save())
		{
		case clsBankClient::svSucceeded:

			cout << "\n\nAccount Updated Successfully!";
			_PrintClientCard(Client);
			break;

		case clsBankClient::svFaildEmptyObject:

			cout << "\n\nError, Account Was Not found";
			break;
		}
			
			
		

	}

};

