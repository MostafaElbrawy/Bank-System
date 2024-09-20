#pragma once
#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include"clsString.h"
#include <string>
#include "clsUtil.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:	
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewNode = 2 };

	

	string _AccountNumber;
	string _Pincode;
	double _Balance;
	enMode _Mode;
	bool _MarkedForDelete = false;
	const static short _Key = 2;

	static clsBankClient _GetEmptyClient()
	{
		return clsBankClient(EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsBankClient _ConvertDataLineToClientObject(string Line, string separator = "#//#")
	{
		vector <string> vClientData = clsString::Split(Line, separator);

		return clsBankClient(UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], clsUtil::DecryptText(vClientData[5], _Key), stod(vClientData[6]));
	}

	string _ConvertClientObjectToDataLine(clsBankClient Client, string separator = "#//#")
	{
		return Client._FirstName + separator + Client._LastName + separator + Client._Email + separator + Client._Phone + separator +
			Client._AccountNumber + separator + clsUtil::EncryptText(Client._Pincode, _Key) + separator + to_string(Client._Balance);
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;
		fstream file;
		file.open("Clients.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				if (line != "")
					vClients.push_back(_ConvertDataLineToClientObject(line));
			}

			file.close();

		}
		return vClients;
	}

	void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream file;
		file.open("Clients.txt", ios::out);

		if (file.is_open())
		{
			for (const clsBankClient& Client : vClients)
			{
				if (!Client._MarkedForDelete)
					file << _ConvertClientObjectToDataLine(Client) << '\n';
			}
			file.close();
		}


	}

	void _SaveDataLineToFile(string Line)
	{
		fstream file;
		file.open("Clients.txt", ios::out | ios::app);

		if (file.is_open())
		{
			file << Line << '\n';
			file.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient& Client : vClients)
		{
			if (Client._AccountNumber == this->_AccountNumber)
			{
				Client = *this;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
	}

	void _AddNew()
	{
		_SaveDataLineToFile(_ConvertClientObjectToDataLine(*this));
	}

public:
		struct stTransferLog
		{
			string Date;
			string SourceAccountNumber;
			string DestinationAccountNumber;
			double SourceBalance;
			double DestinationBalance;
			double Amount;
			string UserName;
		};
private:

	

	static stTransferLog _ConvertDataLineToTransferLog(string Line, string separator = "#//#")
	{
		vector <string> vTransferData = clsString::Split(Line, separator);
		stTransferLog Transfer;
		Transfer.Date = vTransferData[0];
		Transfer.SourceAccountNumber = vTransferData[1];
		Transfer.DestinationAccountNumber = vTransferData[2];
		Transfer.SourceBalance = stod(vTransferData[3]);
		Transfer.DestinationBalance = stod(vTransferData[4]);
		Transfer.Amount = stod(vTransferData[5]);
		Transfer.UserName = vTransferData[6];

		return Transfer;

	}

	static vector <stTransferLog> _LoadTransferLogDataFromFile()
	{
		vector <stTransferLog> vTransfers;
		fstream file;
		file.open("Transfer Log.txt", ios::in);

		if (file.is_open())
		{
			string Line;
			while (getline(file, Line))
			{
				if (Line != "")
					vTransfers.push_back(_ConvertDataLineToTransferLog(Line));
			}

			file.close();
		}
		return vTransfers;

	}

	string _ConverTransferLogToDataLine(stTransferLog Transfer, string separator = "#//#")
	{
		return Transfer.Date + separator + Transfer.SourceAccountNumber + separator + Transfer.DestinationAccountNumber + separator +
			to_string(Transfer.SourceBalance) + separator + to_string(Transfer.DestinationBalance) + separator + to_string(Transfer.Amount) + separator + Transfer.UserName;
	}

	string _PrepareTransferLogLine(clsBankClient DestinationClient, double Amount,  string seprator = "#//#")
	{
		return clsDate::GetSystemDateTimeString() + seprator + _AccountNumber + seprator + DestinationClient.AccountNumber + seprator + to_string(_Balance)
			+ seprator + to_string(DestinationClient.Balance) + seprator + to_string(Amount) + seprator + CurrentUser.UserName;
	}

	void _SaveTransferLogDataLineToFile(string Line)
	{
		fstream file;
		file.open("Transfer Log.txt", ios::out | ios::app);

		if (file.is_open())
		{
			file << Line << '\n';
			file.close();
		}
	}

	

public:
	

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string Pincode, double Balance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_Pincode = Pincode;
		_Balance = Balance;
	}

	bool IsEmpty()
	{
		return (_Mode == EmptyMode);
	}

	string getAccountNumber()
	{
		return _AccountNumber;
	}

	__declspec(property(get = getAccountNumber))string AccountNumber;

	void setPincode(string Pincode)
	{
		_Pincode = Pincode;
		_Update();
	}

	string getPincode()
	{
		return _Pincode;
	}

	_declspec (property(put = setPincode, get = getPincode))string Pincode;

	void setBalance(double Balance)
	{
		_Balance = Balance;
	}

	double getBalance()
	{
		return _Balance;
	}

	__declspec(property(put = setBalance, get = getBalance))double Balance;

	static clsBankClient Find(string AccountNumber)
	{
		fstream file;
		file.open("Clients.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsBankClient Client = _ConvertDataLineToClientObject(line);
				if (Client._AccountNumber == AccountNumber)
				{
					file.close();
					return Client;
				}
			}
			file.close();
			return _GetEmptyClient();

		} 

	}

	static clsBankClient Find(string AccountNumber ,string Pincode)
	{
		fstream file;
		file.open("Clients.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsBankClient Client = _ConvertDataLineToClientObject(line);
				if (Client._AccountNumber == AccountNumber && Client._Pincode == Pincode)
				{
					file.close();
					return Client;
				}
			}
			file.close();
			return _GetEmptyClient();

		}

	}

	static bool IsClientExists(string AccountNumber)
	{
		return !Find(AccountNumber).IsEmpty();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _Balance || Amount < 1)
			return false;

		_Balance -= Amount;
		_Update();
		return true;
	}

	void Deposit(double Amount)
	{
		_Balance += Amount;
		_Update();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			return svFaildEmptyObject;

		case clsBankClient::UpdateMode:
			_Update();
			return svSucceeded;

		case clsBankClient::AddNewNode:
			if (IsClientExists(_AccountNumber))
				return svFaildAccountNumberExists;
			else
			{
				_AddNew();
				_Mode = UpdateMode;
				return svSucceeded;
			}
		}
	}

	bool Delete()
	{
		_MarkedForDelete = true;
		_Update();
		*this = _GetEmptyClient();
		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static clsBankClient GetNewClient(string AccountNumber)
	{
		return clsBankClient(AddNewNode, "", "", "", "", AccountNumber, "",  0);
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		double TotalBalances = 0;

		for (const clsBankClient& Client : vClients)
			TotalBalances += Client._Balance;

		return TotalBalances;
	}

	bool Transfer(clsBankClient &DestinationClient, double Amount)
	{
		if (Amount > _Balance)
			return false;

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_SaveTransferLogDataLineToFile(_PrepareTransferLogLine(DestinationClient, Amount));
		return true;
	}

	static vector <stTransferLog> GetTransferLogList()
	{
		return _LoadTransferLogDataFromFile();
	}

};

