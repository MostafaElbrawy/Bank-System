#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;
class clsAddNewUserScreen : protected clsScreen
{
	static void _PrintUserCard(clsUser& User)
	{
		cout << "\n\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";
	}

	static short _ReadPermissions()
	{
		char choice = 'n';
		cout << "\nDo you want to give the user full access (y/n): ";
		cin >> choice;

		if (tolower(choice) == 'y')
			return -1;

		short permissions = 0;

		cout << "\nDo you wan to give access to: \n\n";

		cout << "Show Client List (y/n): ";
		cin >> choice;

		if (tolower(choice) == 'y')
			permissions += clsUser::pListClients;

		cout << "Add New Client (y/n): ";
		cin >> choice;

		if (tolower(choice) == 'y')
			permissions += clsUser::pAddNewClient;

		cout << "Delete Client (y/n): ";
		cin >> choice;

		if (tolower(choice) == 'y')
			permissions += clsUser::pDeleteClient;

		cout << "Update Client (y/n): ";
		cin >> choice;

		if (tolower(choice) == 'y')
			permissions += clsUser::pUpdateClients;

		cout << "Find Client (y/n): ";
		cin >> choice;

		if (tolower(choice) == 'y')
			permissions += clsUser::pFindClient;

		cout << "Transactions (y/n): ";
		cin >> choice;

		if (tolower(choice) == 'y')
			permissions += clsUser::pTranactions;

		cout << "Manage Users (y/n): ";
		cin >> choice;

		if (tolower(choice) == 'y')
			permissions += clsUser::pManageUsers;

		cout << "Login Register (y/n): ";
		cin >> choice;

		if (tolower(choice) == 'y')
			permissions += clsUser::pLoginRegister;

		return permissions;

	}

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter Frist Name: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone Number: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		User.Permissions = _ReadPermissions();

	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\tAdd New User Screen");
		cout << "\nEnter User Name: ";
		string UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExists(UserName))
		{
			cout << "This User Name Is Taken, Enter Another User Name: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::GetNewUser(UserName);

		cout << "\nNew User Info: ";
		cout << "\n\n_________________________\n";
		_ReadUserInfo(User);

		switch (User.Save())
		{
		case clsUser::svSucceeded:
				
			cout << "\n\nUser Added Successfully!";	
			_PrintUserCard(User);
			break;

		case clsUser::svFaildUserNameExists:
			cout << "\n\nUser Was Not Added Because User Name Already Exists";
			break;

		case clsUser::svFaildEmptyObject:
		
			cout << "\nError, User Was Not Saved Because It's Empty";
			break;

		}



	}


};

