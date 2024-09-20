#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsFindUserScreen :protected clsScreen
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

	static void _ShowFindUserScreen()
	{

		_DrawScreenHeader("\t Find User Screen");

		cout << "Enter User Name: ";
		string UserName = clsInputValidate::ReadString();
		clsUser User = clsUser::Find(UserName);

		while (User.IsEmpty())
		{
			cout << "User Name Was Not Found, Enter Another User Name: ";
			UserName = clsInputValidate::ReadString();
			User = clsUser::Find(UserName);
		}


		cout << "\n\nUser Was Found!";
		_PrintUserCard(User);


	}




};

