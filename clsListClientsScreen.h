#pragma once
#include "clsScreen.h"
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"

using namespace std;

class clsListClientsScreen : protected clsScreen
{

	static void _PrintClientRecord(clsBankClient& Client)
	{
        cout << '\t' << "| " << left << setw(15) << Client.AccountNumber;
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.Phone;
        cout << "| " << left << setw(20) << Client.Email;
        cout << "| " << left << setw(10) << Client.Pincode;
        cout << "| " << left << setw(12) << Client.Balance;
	}

public:

    static void ShowListClientsScreen()
    {
        if (!CheckPermissionRights(clsUser::pListClients))
            return;

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\tList Clients Screen";
        string SubTitle = "\t (" + to_string(vClients.size()) + ") Client(s)";

        _DrawScreenHeader(Title ,SubTitle);

        cout << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << '\t' << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\t\tThere Is No Clients In The System!";

        for (clsBankClient& Client : vClients)
        {
            _PrintClientRecord(Client);
            cout << '\n';
        }

        cout << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }



};

