#pragma once
#include "clsScreen.h"
#include "iostream"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;
class clsManageUserScreen : protected clsScreen
{
	enum enManageUserList { ListUsers = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, MainMenuScreen = 6 };

	static short _ReadManageUsersMenuOption()
	{
		cout << setw(37) << left << "" << "Choose What Do You Want to Do [1:6]: ";
		short Choice = clsInputValidate::ReadNumberBetween(1, 6, "\nInvalid Choice, Enter Number Between [1:6]: ");
		return Choice;
	}

	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowListUsersScreen();
	}

	static void _ShowAddUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::_ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::_ShowFindUserScreen();
	}

	static void _PerformManageUserMenuOptions(enManageUserList Choice)
	{
		system("cls");

		switch (Choice)
		{
		case clsManageUserScreen::ListUsers:

			_ShowListUsersScreen();
			break;

		case clsManageUserScreen::AddUser:

			_ShowAddUserScreen();
			break;

		case clsManageUserScreen::DeleteUser:

			_ShowDeleteUserScreen();
			break;

		case clsManageUserScreen::UpdateUser:

			_ShowUpdateUserScreen();
			break;

		case clsManageUserScreen::FindUser:
			
			_ShowFindUserScreen();
			break;

		case clsManageUserScreen::MainMenuScreen:
			return;

		}
		cout << "\n\n" << setw(37) << left << "" << "Press Any Key To Go Back To Manage User Menu...";
		system("pause>0");
		system("cls");
		ShowManageUserScreen();
	}

public:

	static void ShowManageUserScreen()
	{

		if (!CheckPermissionRights(clsUser::pManageUsers))
			return;

		_DrawScreenHeader("\tManage Users Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Manage Users Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformManageUserMenuOptions(enManageUserList(_ReadManageUsersMenuOption()));


	}

};

