#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

#include "Encryption.h"
// ATM System using C++

using namespace std;

// ANSI escape codes for text colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

const string ClientDataBasePath = "Bank_Clients.database";
struct stClients
{
	string Account_number;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};

string Separator = "------------------------------------------------------------------------------------------------------------------------";

bool Continue_Processe(string Message)
{
	bool C;
	cout << Message;
	cin >> C;
	return C;
}

string ReadString(string Message)
{
	string str;
	cout << Message;
	cin.clear();
	getline(cin, str);
	return str;
}

void EndScreen()
{
	cout << "Press Any Key To Continue . . .";
	system("pause>0");
}


vector<string> SplitVector(string Line, string Delim)
{
	vector<string>vString;
	short pos = 0;
	string sWord;
	while ((pos = Line.find(Delim)) != std::string::npos)
	{
		sWord = Line.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		Line.erase(0, pos + Delim.length());
	}
	if (Line != "")
	{
		vString.push_back(Line);
	}

	return vString;
}

void LoadLinesToUersStruct(vector<string>& vLines)
{
	fstream Myfile;
	clsEncryption Encryptor;
	Myfile.open(ClientDataBasePath, ios::in);
	if (Myfile.is_open())
	{
		string Line;
		while (getline(Myfile, Line))
		{
			vLines.push_back(Encryptor.Denc(Line));
		}
		Myfile.close();
	}
}

void LoadDataToVector(vector<stClients>& vClients)
{
	vector<string> vLines;
	vector<string> vSplitedVector;
	LoadLinesToUersStruct(vLines);
	for (int i = 0; i < vLines.size(); i++)
	{
		vSplitedVector = SplitVector(vLines.at(i), "#//#");
		vClients.push_back({ vSplitedVector.at(0), vSplitedVector.at(1), vSplitedVector.at(2), vSplitedVector.at(3), stod(vSplitedVector.at(4)) });
	}
}

string ExportDataToLine(stClients Data, string Delim = "#//#")
{
	clsEncryption Encryptor;
	string Line = "";
	Line += Data.Account_number + Delim + Data.PinCode + Delim
		+ Data.Name + Delim + Data.Phone + Delim + to_string(Data.AccountBalance) + Delim;
	return Encryptor.Enc(Line);
}


void UpdateVector(vector<stClients>& vClients) // Clear the vector an push the Clients from file
{
	vClients.clear();
	LoadDataToVector(vClients);
}

void UploadDataToFile(vector<stClients> vClients)
{
	fstream Myfile;
	Myfile.open(ClientDataBasePath, ios::out);
	if (Myfile.is_open())
	{
		for (stClients& C : vClients)
		{
			Myfile << ExportDataToLine(C) << endl;
		}
		Myfile.close();
	}
}

bool CheckClientName(vector<stClients> vClients, string Accnumber)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients.at(i).Account_number == Accnumber)
		{
			return true;
		}
	}
	return false;
}


bool CheckPinCode(vector<stClients> vClients, string PIN_Code)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients.at(i).PinCode == PIN_Code)
		{
			return true;
		}
	}

	return false;
}

void DisplayBalance(stClients Client)
{
	cout << GREEN;
	cout << "Your Actual Balance is : " << endl;
	cout << setw(45 + 2) << " " << "Your Account Balance : " << endl;
	cout << setw(45 - 2 + 2) << " " << "---------------------------" << endl;
	cout << setw(45 - 2 + 2) << " " << "|" << setw(16) << Client.AccountBalance << setw(9) << " " << "|" << endl;
	cout << setw(45 - 2 + 2) << " " << "---------------------------" << endl;
	cout << RESET;
}

void CheckBalance(stClients Client)
{
	cout << Separator << endl;
	cout << setw(50) << " " << "Check Balance Screen" << endl;
	cout << Separator << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << setw(45) << " " << "Your Account Balance : " << endl;
	cout << setw(45 - 2) << " " << "---------------------------" << endl;
	cout << setw(45 - 2) << " " << "|" << setw(16) << Client.AccountBalance << setw(9) << " " << "|" << endl;
	cout << setw(45 - 2) << " " << "---------------------------" << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	EndScreen();
}

void WithDarw(stClients& Client, double withdrawedAmount)
{
	if (Client.AccountBalance >= withdrawedAmount)
	{
		if (Continue_Processe("Are you Sure you want to perfrom this Action ? [1 = tes][0 = no] : "))
		{
			Client.AccountBalance -= withdrawedAmount;
			cout << "Amount wathdrawed Seccussfuly !" << endl;
			DisplayBalance(Client);
		}
	}
	else {
		cout << RED << "Sorry ! You Dont Have enought Money To do This Action !" << RESET << endl;
	}
}

void QuickWithDrawScreen(stClients& Client)
{
	cout << Separator << endl;
	cout << setw(50) << " " << "Quick Withdraw" << endl;
	cout << Separator << endl;
	cout << setw(45) << " " << "[1] 20   $       [2] 50   $" << endl;
	cout << setw(45) << " " << "[3] 100  $       [4] 200  $" << endl;
	cout << setw(45) << " " << "[5] 500  $       [6] 1000 $" << endl;
	cout << setw(45) << " " << "[6] 2000 $       [8] 3000 $" << endl;
	cout << setw(45) << " " << "[9] Exit" << endl;
	cout << "\n";
	DisplayBalance(Client);
	cout << Separator << endl;
	cout << setw(45) << " " << "=> ";
	int userChoice;
	cin >> userChoice;
	cin.ignore();

	switch (userChoice)
	{
	case 1:
		WithDarw(Client, 20);
		break;
	case 2:
		WithDarw(Client, 50);
		break;
	case 3:
		WithDarw(Client, 100);
		break;
	case 4:
		WithDarw(Client, 200);
		break;
	case 5:
		WithDarw(Client, 500);
		break;
	case 6:
		WithDarw(Client, 1000);
		break;
	case 7:
		WithDarw(Client, 2000);
		break;
	case 8:
		WithDarw(Client, 3000);
		break;
	case 9:
		return;
	default:
		cout << "Unvalid Choice !" << endl;
		break;

	}
	EndScreen();
}

void NormalWithDrawScreen(stClients& Client)
{
	cout << Separator << endl;
	cout << setw(50) << " " << "Normal WithDraw" << endl;
	cout << Separator << endl;
	cout << "\n";
	DisplayBalance(Client);
	int amount = 2;
	while (amount % 5 != 0)
	{
		cout << setw(35) << "Enter an amount multiple of 5 : ";
		cin >> amount;
	}
	
	WithDarw(Client, amount);
	EndScreen();
}
	
void DepositScreen(stClients &Client)
{
	cout << Separator << endl;
	cout << setw(50) << " " << "Deposit Screen" << endl;
	cout << Separator << endl;

	DisplayBalance(Client);
	int DepositAmount;
	cout << setw(50) << " " << "Enter Deposit Amount : ";
	cin >> DepositAmount;
	if (Continue_Processe("Are you Sure you want to perfrom this Action ? [1 = tes][0 = no] : "))
	{
		Client.AccountBalance += DepositAmount;
		cout << "Amount Deposit Seccussfuly !" << endl;
		DisplayBalance(Client);
	}

	EndScreen();
}

void MainmenuScreen(vector<stClients>& vClients, stClients &Client)
{
	while (true)
	{
		UpdateVector(vClients);
		system("cls");
		cout << Separator << endl;
		cout << setw(45) << " " << "ATM Main Menu Screen" << endl;
		cout << Separator << endl;
		cout << setw(45) << " " << GREEN << "Hello " << Client.Name << " !" << RESET << endl;

		cout << setw(50) << " " << "[1] Quick withdarw." << endl;
		cout << setw(50) << " " << "[2] Normal withDarw." << endl;
		cout << setw(50) << " " << "[3] Deposit." << endl;
		cout << setw(50) << " " << "[4] Check Balance." << endl;
		cout << setw(50) << " " << "[5] Log out." << endl;
		cout << setw(50) << " " << "[6] Close and Exit." << endl;
		cout << Separator << endl;
		cout << setw(50) << " " << "=> ";
		short UserChoice;
		cin >> UserChoice;

		switch (UserChoice)
		{
		case 1:
			system("cls");
			QuickWithDrawScreen(Client);
			UploadDataToFile(vClients);
			break;
		case 2:
			system("cls");
			NormalWithDrawScreen(Client);
			UploadDataToFile(vClients);
			break;
		case 3:
			system("cls");
			DepositScreen(Client);
			UploadDataToFile(vClients);
			break;
		case 4:
			system("cls");
			CheckBalance(Client);
			break;
		case 5:
			return;
			break;
		case 6:
			exit(0);
			break;
		default:
			cout << "Unvalid User Choice !" << endl;
			break;
		}
	}
}

stClients Get_Client_By_Client_Accnumber(vector<stClients> vClients, string Accnumber)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients.at(i).Account_number == Accnumber) return vClients.at(i);
	}
}

int GetClientIndex(vector<stClients> vClients, string Account_number)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients.at(i).Account_number == Account_number) return i;
	}
	return -1;
}

int Login(vector<stClients> vClients)
{
	while (true)
	{
		cout << Separator << endl;
		cout << setw(50) << " " << "Log In" << endl;
		cout << Separator << endl;

		string Accnumber = ReadString("Enter account number : ");;
		string CodePin = ReadString("Enter Code Pin : ");
		if (CheckClientName(vClients, Accnumber), CheckPinCode(vClients, CodePin))
		{
			return GetClientIndex(vClients, Accnumber);
		}
		else {
			system("cls");
			cout << "Invalid Account number / Pin Code !" << endl;
		}
	}
	return -1;
}


int main()
{
	vector<stClients> vClients;
	LoadDataToVector(vClients);
	
	while (true)
	{
		system("cls");
		MainmenuScreen(vClients, vClients.at(Login(vClients)));
	}
	

	return 0;
}