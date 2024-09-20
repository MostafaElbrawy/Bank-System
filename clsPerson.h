#pragma once
#include <iostream>

using namespace std;
class clsPerson
{
protected:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:

	clsPerson(string FirstName, string LastName, string Email, string Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	void setFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}

	string getFirstName()
	{
		return _FirstName;
	}
	__declspec(property(put = setFirstName, get = getFirstName))string FirstName;

	void setLastName(string LastName)
	{
		_LastName = LastName;
	}

	string getLastName()
	{
		return _LastName;
	}
	__declspec(property(put = setLastName, get = getLastName))string LastName;


	void setEmail(string Email)
	{
		_Email = Email;
	}

	string getEmail()
	{
		return _Email;
	}
	__declspec(property(put = setEmail, get = getEmail))string Email;

	void setPhone(string Phone)
	{
		_Phone = Phone;
	}

	string getPhone()
	{
		return _Phone;
	}
	__declspec(property(put = setPhone, get = getPhone))string Phone;

	string FullName()
	{
		return _FirstName + " " + _LastName;
	}
};

