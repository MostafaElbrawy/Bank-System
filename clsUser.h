#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include <vector>
#include "clsString.h"
#include "clsUtil.h"
using namespace std;

class clsUser : public clsPerson
{

private:

	static clsUser _ConvertDataLineToUserObject(string Line , string separator = "#//#")
	{
		vector <string> vUserData = clsString::Split(Line, separator);

		return clsUser(UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
			vUserData[4], clsUtil::DecryptText(vUserData[5] , _Key), stoi(vUserData[6]));
	}

	static string _ConvertUserObjectToDataLine(clsUser User , string separator = "#//#")
	{
		return User._FirstName + separator + User._LastName + separator + User._Email + separator + User._Phone + separator +
			User._UserName + separator + clsUtil::EncryptText(User._Password, _Key) + separator + to_string(User._Permissions);
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		fstream file; vector <clsUser> vUsers;

		file.open("Users.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				if (line != "")
					vUsers.push_back(_ConvertDataLineToUserObject(line));
			}
			file.close();

		}
		return vUsers;

	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream file;
		file.open("Users.txt", ios::out);

		if (file.is_open())
		{
			for (clsUser& User : vUsers)
			{
				if (!User._MarkedForDelete )
					file << _ConvertUserObjectToDataLine(User) << '\n';
			}
			file.close();
		}

	}

	static void _SaveUserDataLineToFile(string Line)
	{

		fstream file;
		file.open("Users.txt", ios::in | ios::app);

		if (file.is_open())
		{
			file << Line << '\n';
			file.close();
		}

	}

	static clsUser _GetEmptyUser()
	{
		return clsUser(EmptyMode, "", "", "", "", "", "", 0);
	}

	void _Update()
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (_UserName == User._UserName)
			{
				User = *this;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew()
	{
		_SaveUserDataLineToFile(_ConvertUserObjectToDataLine(*this));
	}

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewNode = 2 };
	string _UserName;
	string _Password;
	int _Permissions;
	enMode _Mode;
	bool _MarkedForDelete = false;
	const static short _Key = 2;
	
public:

	struct stLoginRegister
	{
		string Date;
		string UserName;
		string Password;
		int Permissions;
	};


private:


	string PrepareLoginRegisterDataLine(string separator = "#//#")
	{
		return clsDate::GetSystemDateTimeString() + separator + _UserName + separator + _Password + separator + to_string(_Permissions);
	}

	void _SaveLoginRegisterDataLine(string Line)
	{
		fstream file;
		file.open("Login Register.txt", ios::out | ios::app);

		if (file.is_open())
		{
			file << Line << '\n';
			file.close();
		}
	}

	static stLoginRegister _ConvertDataLineToLoginRegister(string Line, string separator = "#//#")
	{
		vector <string> vLoginData = clsString::Split(Line ,separator);
		stLoginRegister LoginRegister;
		LoginRegister.Date = vLoginData[0];
		LoginRegister.UserName = vLoginData[1];
		LoginRegister.Password = vLoginData[2];
		LoginRegister.Permissions = stoi(vLoginData[3]);

		return LoginRegister;
	}
	
	static vector <stLoginRegister> _LoadLoginRegisterDataFromFile()
	{
		vector <stLoginRegister> vLoginRegisters;
		fstream file;
		file.open("Login Register.txt", ios::in);

		if (file.is_open())
		{
			string Line;
			while(getline(file,Line))
			{
				if (Line != "")
					vLoginRegisters.push_back(_ConvertDataLineToLoginRegister(Line));
			}
			file.close();
		}
		return vLoginRegisters;
	}

public:

	enum enMainMenuePermissions { eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClients = 8, 
		pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 128 };

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return (_Mode == EmptyMode);
	}

	void setUserName(string UserName)
	{
		_UserName = UserName;
	}

	string getUserName()
	{
		return _UserName;
	}

	__declspec(property(get = getUserName, put = setUserName)) string UserName;

	void setPassword(string Password)
	{
		_Password = Password;
	}

	string getPassword()
	{
		return _Password;
	}

	__declspec(property(get = getPassword, put = setPassword)) string Password;

	void setPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int getPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = getPermissions, put = setPermissions))int Permissions;

	static clsUser Find(string UserName)
	{
		fstream file;
		file.open("Users.txt", ios::in);

		if (file.is_open())
		{
			string Line;
			while (getline(file, Line))
			{
				clsUser User = _ConvertDataLineToUserObject(Line);
				if (User._UserName == UserName)
				{
					file.close();
					return User;
				}

			}
			file.close();
			return _GetEmptyUser();

		}



	}

	static clsUser Find(string UserName , string Password)
	{
		fstream file;
		file.open("Users.txt", ios::in);

		if (file.is_open())
		{
			string Line;
			while (getline(file, Line))
			{
				clsUser User = _ConvertDataLineToUserObject(Line);
				if (User._UserName == UserName && User._Password == Password)
				{
					file.close();
					return User;
				}

			}
			file.close();
			return _GetEmptyUser();

		}



	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			return svFaildEmptyObject;

		case clsUser::UpdateMode:
			_Update();
			return svSucceeded;

		case clsUser::AddNewNode:
			if (IsUserExists(_UserName))
				return svFaildUserNameExists;
			else
			{
				_AddNew();
				_Mode = UpdateMode;
				return svSucceeded;
			}
		}
	}

	static bool IsUserExists(string UserName)
	{
		return !Find(UserName).IsEmpty();
	}

	bool Delete()
	{
		_MarkedForDelete = true;
		_Update();
		*this = _GetEmptyUser();
		return true;
	}

	static vector <clsUser> GetListUsers()
	{
		return _LoadUsersDataFromFile();
	}

	static clsUser GetNewUser(string UserName)
	{
		return clsUser(AddNewNode, "", "", "", "", UserName, "", 0);
	}

	void LoginRegister()
	{
		_SaveLoginRegisterDataLine(PrepareLoginRegisterDataLine());
	}

	static vector <stLoginRegister> GetLoginRegisterList()
	{
		return _LoadLoginRegisterDataFromFile();
	}

	bool CheckPermission(enMainMenuePermissions Permission)
	{
		if (Permission == -1)
			return true;
		if ((Permission & _Permissions) == Permission)
			return true;
		return false;
	}

};

