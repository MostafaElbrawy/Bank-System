#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
class clsLoginScreen : protected clsScreen
{
	static void _Login()
	{
		bool FailedLogin = false; short Counter = 3;
		string UserName, Password;
		do
		{
			if (FailedLogin)
			{
				Counter--;
				cout << "\n\nInvalid UserName/Password!";
				cout << "\nYou Have " << Counter << " Trial(s) Left\n";
			}
		
			if (Counter == 0)
			{
				cout << "\nYou Are Locked!";
				exit(0);
			}

			cout << "\nEnter User Name: ";
			UserName = clsInputValidate::ReadString();
			cout << "\nEnter Password: ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);

		} while (FailedLogin = CurrentUser.IsEmpty());
		CurrentUser.LoginRegister();
	}

public:

	static void ShowLoginScreen()
	{
		_DrawScreenHeader("\t  Login Screen");
		_Login();
		clsMainScreen::ShowMainMenuScreen();
	}
};

