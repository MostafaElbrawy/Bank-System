#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;
class clsAddNewClientScreen : protected clsScreen
{

	static void _PrintClientCard(clsBankClient &Client)
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

	static void ShowAddNewClientScreen()
	{
		if (!CheckPermissionRights(clsUser::pAddNewClient))
			return;



		_DrawScreenHeader("\tAdd New Client Screen");

		cout << "\nEnter Account Number: ";
		string AccountNumber = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExists(AccountNumber))
		{
			cout << "\nThis Accout Number Is Taken, Enter Another One: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::GetNewClient(AccountNumber);

		cout << "\nAdd Client Info: ";
		cout << "\n\n____________________________\n";
		_ReadClientInfo(Client);
		_PrintClientCard(Client);

		switch (Client.Save())
		{
		case clsBankClient::svSucceeded:
			cout << "\n\nClient Added Successfully!";
			break;

		case clsBankClient::svFaildEmptyObject:
			cout << "\n\nAccount Was Not Saved Because It Is Empty";
			break;

		case clsBankClient::svFaildAccountNumberExists:
			cout << "\n\nAccount Was Not Saved Because Account Number Alraedy Exists" ;
			break;

		}
	}



		

};

