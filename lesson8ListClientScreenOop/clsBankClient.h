#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode{EmptyMode = 1, UpDateMode = 2, AddNewMode = 3};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;
	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector< string > vClientData;
		vClientData = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpDateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}
	static vector<clsBankClient> _LoadClientObjectToFile()
	{
		vector<clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}
	static void _SaveClientObjectToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;
		string DataLine;
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsBankClient c : vClients)
			{

				DataLine = _ConvertClientObjectToLine(c); 
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}
	 void _UpDate()
	{
		vector<clsBankClient> _Vclients;
		_Vclients = _LoadClientObjectToFile();
		for (clsBankClient& C : _Vclients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
		}

		}
		_SaveClientObjectToFile(_Vclients);
	}
	 void _AddDataLineToFile(string stDataLine)
	 {
		 fstream MyFile;
		 MyFile.open("Clients.txt", ios::out | ios::app);
		 if (MyFile.is_open())
		 {
			 MyFile << stDataLine << endl;
			 MyFile.close();
		 }
	}


	 void _AddNew()
	 {
		 _AddDataLineToFile(_ConvertClientObjectToLine(*this));
	 }










	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stRecordData = "";
		stRecordData += Client.FirstName + Seperator;
		stRecordData += Client.LastName + Seperator;
		stRecordData += Client.Email + Seperator;
		stRecordData += Client.Phone + Seperator;
		stRecordData += Client.AccountNumber() + Seperator;
		stRecordData += Client.PinCode + Seperator;
		stRecordData += to_string(Client.AccountBalance);
		return stRecordData;
	}



	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}




public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;

		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode = enMode::EmptyMode);
	}
	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}
	string AccountNumber()
	{
		return _AccountNumber;
	}
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;

	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient > vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Client.Find(AccountNumber);
		return (!Client.IsEmpty());
	}
	bool Deleted()
	{
		vector <clsBankClient> vClients;
		vClients = _LoadClientObjectToFile();
		for (clsBankClient& c : vClients)
		{
			if (c.AccountNumber() == AccountNumber())
			{
				c._MarkedForDelete = true;
				break;
			}
		}
		_SaveClientObjectToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}
	static clsBankClient GetAddNewClient(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	static vector<clsBankClient> GetClientList()
	{
		return _LoadClientObjectToFile();
	}

};

