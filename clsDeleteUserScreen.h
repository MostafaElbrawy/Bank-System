#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;
class clsDeleteUserScreen : protected clsScreen
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


public:

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\tDelete User Screen");

		cout << "Enter User Name: ";
		string UserName = clsInputValidate::ReadString();
		clsUser User = clsUser::Find(UserName);
		while (User.IsEmpty())
		{
			cout << "User Name Was Not Found, Enter Another User Name: ";
			UserName = clsInputValidate::ReadString();
			User = clsUser::Find(UserName);
		}

		_PrintUserCard(User);

		cout << "\n\nAre You Sure Do You Want To Delete This User (y/n): ";
		char sure;
		cin >> sure;
		if (sure == 'y' || sure == 'Y')
		{
			if (User.Delete())
			{
				cout << "\n\nUser Deleted Successfully!";
				_PrintUserCard(User);
			}
			else
				cout << "\n\nError, User Was Not Deleted";
		}
		else
			cout << "\n\nOperation Cancelled";

	}

};

