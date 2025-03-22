#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include <iomanip>
using namespace std;

class clsMainScreen:protected clsScreen
{
private:
	enum enMainMenueOptions {
		eListClients = 1, eAddNewClient = 2, eDeleteClient =3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7, eExist = 8
	};
	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "choose what do you want to do ? [1 to 8]?";
		short Choice = clsInputValidate::ReadDblNumberBetween(1, 8, "Enter Number between 1 to 8?");
		return Choice;

	}
	static void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to main menue...\n";
		system("pause>0");
		ShowMainMenue();
	}
	static void _ShowAllClientList()
	{
		clsClientListScreen::ShowClientList();
	}
	static void _ShowAddNewClient()
	{}
	static void _ShowDeleteClientScreen()
	{}
	static void _ShowUpDateClientScreen()
	{}
	static void _ShowFindClientScreen()
	{}
	static void _ShowTransactionMenue()
	{}
	static void _ShowManageUserMenue()
	{}
	static void _ShowEndScreen()
	{}
	static void _PerformMainMenueOption(enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enMainMenueOptions::eListClients:
		{
			system("cls");
			_ShowAllClientList();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eAddNewClient:
			system("cls");
			_ShowAddNewClient();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eUpdateClient:
			system("cls");
			_ShowUpDateClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eShowTransactionsMenue:
			system("cls");
			_ShowTransactionMenue();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eManageUsers:
			system("cls");
			_ShowManageUserMenue();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eExist:
			system("cls");
			_ShowEndScreen();
			break;

		}
	}
public:
	static void ShowMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\n\t\t\t\t\t\tMain Meneue");

		cout << setw(37) << left << "" << "====================================\n";
		cout << setw(37) << left << "" << "\t\tMain Screen.\n";
		cout << setw(37) << left << "" << "====================================\n";

		cout << setw(37) << left << "" << "\tAll List CLient.\n";
		cout << setw(37) << left << "" << "\tAdd New Client.\n";
		cout << setw(37) << left << "" << "\tDelete Client.\n";
		cout << setw(37) << left << "" << "\tUpDate CLient Info.\n";
		cout << setw(37) << left << "" << "\tFind Client.\n";
		cout << setw(37) << left << "" << "\tTransacion.\n";
		cout << setw(37) << left << "" << "\tMange User.\n";
		cout << setw(37) << left << "" << "\tLogout.\n";
		cout << setw(37) << left << "" << "====================================\n";

		_PerformMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
	}
};

