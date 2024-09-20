#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
class clsListLoginRegisterScreen : protected clsScreen
{
    static void PrintLoginRegisterRecord(clsUser::stLoginRegister LoginRegister)
    {
        cout << setw(8) << left << "" << "| " << setw(25) << left << LoginRegister.Date;
        cout << "| " << setw(25) << left << LoginRegister.UserName;
        cout << "| " << setw(25) << left << LoginRegister.Password;
        cout << "| " << setw(25) << left << LoginRegister.Permissions;
    }

public:

    static void ShowListLoginRegisterScreen()
    {
        if (!CheckPermissionRights(clsUser::pLoginRegister))
            return;

        vector<clsUser::stLoginRegister> vLoginRegisters = clsUser::GetLoginRegisterList();
        string Title = "    List Login Register Screen";
        string SubTitle = "        (" + to_string(vLoginRegisters.size()) + ") Records(s)";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(25) << "User Name";
        cout << "| " << left << setw(25) << "Password";
        cout << "| " << left << setw(25) << "Permissions";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vLoginRegisters.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsUser::stLoginRegister Login : vLoginRegisters)
            {

                PrintLoginRegisterRecord(Login);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;


    }






};

