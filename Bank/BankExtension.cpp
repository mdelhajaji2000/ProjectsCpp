#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
// #xtension Version with Transaction

using namespace std;

const string DataBasePath = "Banck.database";

struct stData
{
	string Account_number;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};

string SeparatorGenerator(int lenght);
void PrintClientCard(stData UserData);
int UserSerchByAccountNumber(vector<stData> vUsers, string account_number);

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
	static int used = 0; // This variable used to know that if cin.ignor was used or not! 
	//if (used < 1) cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any characters left in the input buffer
	getline(cin, str);
	used++;
	return str;
}

int ReadPositifNumber(string Message)
{
	cout << Message;
	int number;
	cin >> number;
	return number;
}

void readDataFromUser(vector<stData> vUsers, stData& Data, bool Isnew = true)// true = new_accont; false = edit_account
{
	bool Continue = false;
	while (!Continue)
	{
		if (Isnew)
		{
			string tempAcccnum = ReadString("Enter Account Number : ");
			if (UserSerchByAccountNumber(vUsers, tempAcccnum) == -1)
			{
				Data.Account_number = tempAcccnum;
				Continue = true;
			}
			else
			{
				cout << "account with tempAccnum alerdy exist !" << endl;
				Continue = false;
			}
		}
		if (Continue)
		{
			Data.PinCode = ReadString("Enter Pin Code : ");
			Data.Name = ReadString("Enter your name : ");
			Data.Phone = ReadString("Enter your PHONE number : ");
			Data.AccountBalance = ReadPositifNumber("Enter your AccBalance : ");
		}
	}

}

vector<string> SplitVector(string Line, string Delim = "#//#")
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
	Myfile.open(DataBasePath, ios::in);
	if (Myfile.is_open())
	{
		string Line;
		while (getline(Myfile, Line))
		{
			vLines.push_back(Line);
		}
		Myfile.close();
	}
}

void LoadDataToVector(vector<stData>& vUsers)
{
	vector<string> vLines;
	vector<string> vSplitedVector;
	LoadLinesToUersStruct(vLines);
	for (int i = 0; i < vLines.size(); i++)
	{
		vSplitedVector = SplitVector(vLines.at(i));
		vUsers.push_back({ vSplitedVector.at(0), vSplitedVector.at(1), vSplitedVector.at(2), vSplitedVector.at(3), stod(vSplitedVector.at(4)) });
	}
}

string ExportDataToLine(stData Data, string Delim = "#//#")
{
	string Line = "";
	Line += Data.Account_number + Delim + Data.PinCode + Delim
		+ Data.Name + Delim + Data.Phone + Delim + to_string(Data.AccountBalance) + Delim;
	return Line;
}

void addClientRow(const stData& Data)
{
	cout << "|" << setw(16) << Data.Account_number << "|" << setw(13) << Data.PinCode << "|" << setw(38 + 5) << Data.Name << "|" << setw(15 + 6) << Data.Phone << "|" << setw(20) << fixed << setprecision(2) << Data.AccountBalance << "|" << endl;
}

void PrintClients(const vector<stData> vUsers)
{
	cout << endl;
	cout << setw(50) << " " << "Clients List (" << vUsers.size() << ") Client(s)" << endl;
	cout << endl;
	cout << left;
	cout << SeparatorGenerator(120);
	cout << "|" << setw(16) << " Account Number" << "|" << setw(13) << " Pin Code " << "|" << setw(38 + 5) << " Client Name" << "|" << setw(15 + 6) << " Phone" << "|" << setw(20) << " Balance" << "|" << endl;
	cout << "|----------------|-------------|-------------------------------------------|---------------------|--------------------|" << endl;
	for (const stData& line : vUsers)
	{
		addClientRow(line);
	}
	cout << "|----------------|-------------|-------------------------------------------|---------------------|--------------------|" << endl;


	cout << "Press any key To Continue..." << endl;
	system("pause>0");
	system("cls");
}

void UploadDataToFile(vector<stData> vUsers)
{
	fstream Myfile;
	Myfile.open(DataBasePath, ios::out);
	if (Myfile.is_open())
	{
		for (stData& C : vUsers)
		{
			Myfile << ExportDataToLine(C) << endl;
		}
		Myfile.close();
	}
}

void AddNewClientScreen(vector<stData> vUsers)
{
	cout << SeparatorGenerator(120) << endl;
	cout << setw(55) << " " << "Add New Client Screen" << endl;
	cout << SeparatorGenerator(120) << endl;
	stData NewClient;
	readDataFromUser(vUsers, NewClient);
	vUsers.push_back(NewClient);
	cout << "New Client Added Succssusfly !" << endl;
	UploadDataToFile(vUsers);
	LoadDataToVector(vUsers);
	cout << endl;
	cout << "Press any key to Continue..." << endl;
	system("pause>0");
	system("cls");
	return;
}

void UpdateVector(vector<stData>& vUsers) // Clear the vector an push the users from file
{
	vUsers.clear();
	LoadDataToVector(vUsers);
}

int UserSerchByAccountNumber(vector<stData> vUsers, string account_number)
{
	for (int i = 0; i < vUsers.size(); i++)
	{
		if (account_number == vUsers.at(i).Account_number) return i;
	}
	return -1;
}

void DeletScreen(vector<stData>& vUsers)
{
	string Accnum;
	cout << SeparatorGenerator(120) << endl;
	cout << setw(50) << " " << "Delet Client Screen" << endl;
	cout << SeparatorGenerator(120) << endl;

	cout << "Enter Account Number : ";
	cin >> Accnum;
	int Account_index = UserSerchByAccountNumber(vUsers, Accnum);
	if (Account_index >= 0)
	{
		cout << "Account : " << Accnum << " Was found!" << endl;
		cout << "Client Data : " << endl;
		PrintClientCard(vUsers.at(Account_index));
		bool IsDelet;
		cout << "Are you Sure To Delet This Client ? [1 = true][0 = false] : ";
		cin >> IsDelet;

		if (IsDelet)
		{
			vUsers.erase(vUsers.begin() + Account_index);
			cout << "Account Seccussfuly Deleted ...!" << endl;
		}
		UploadDataToFile(vUsers);
	}
	else {
		cout << "Account : " << Accnum << " was not Found !" << endl;
	}



	cout << "Press any key To continue..." << endl;
	system("pause>0");
	system("cls");
}

void PrintClientCard(stData UserData)
{
	cout << endl;
	cout << "Account Number       : " << UserData.Account_number << endl;
	cout << "Account PIN Code     : " << UserData.PinCode << endl;
	cout << "Client name          : " << UserData.Name << endl;
	cout << "Client Phone Number  : " << UserData.Phone << endl;
	cout << "Account Balance      : " << UserData.AccountBalance << endl;
	cout << endl;
}

void UpdateClientInfoScreen(vector<stData>& vUsers)
{
	cout << SeparatorGenerator(120) << endl;
	cout << setw(50) << " " << "Update Client Info Screen" << endl;
	cout << SeparatorGenerator(120) << endl;
	cout << "Enter Account Number : ";
	string Accnum;
	cin >> Accnum;
	cin.ignore();
	int Acc_index = UserSerchByAccountNumber(vUsers, Accnum);
	if (Acc_index >= 0)
	{
		cout << "Account : " << Accnum << " was Found !" << endl;
		cout << "Client Info : " << endl;
		PrintClientCard(vUsers.at(Acc_index));

		readDataFromUser(vUsers, vUsers.at(Acc_index), false);

		cout << "Do you Want To save Changes [1 = yes][0 = no] : " << endl;
		int Issave;
		cin >> Issave;
		if (Issave)	UploadDataToFile(vUsers);
	}
	else {
		cout << "Account : " << Accnum << " Not Found !" << endl;
	}

	cout << "Enter Any key To continue...";
	system("pause>0");
	system("cls");
}

void FindClientScreen(vector<stData> vUsers)
{
	cout << SeparatorGenerator(120) << endl;
	cout << setw(55) << " " << "Find Client Screen" << endl;
	cout << SeparatorGenerator(120) << endl;
	cout << "Enter Account Number : ";
	string Accnum;
	cin >> Accnum;
	int accindex = UserSerchByAccountNumber(vUsers, Accnum);
	if (accindex >= 0)
	{
		cout << "Account : " << Accnum << " was Found !" << endl;
		cout << "Client Info : " << endl;
		PrintClientCard(vUsers.at(accindex));

	}
	else (cout << "Account " << Accnum << " was not found ..!" << endl);

	cout << "Presse Any Key To Continue...";
	system("pause>0");
	system("cls");
}

void EndScreen()
{
	cout << "Presse Any Key To Continue..." << endl;
	system("pause>0");
	system("cls");
}

// Transection Extention Functions :
void DepositScreen(vector<stData>& vUsers);
void WithdrawScreen(vector<stData>& vUsers);

double TotaleCalculator(vector<stData> vUsers)
{
	double Totale = 0;
	for (stData& C : vUsers)
	{
		Totale += C.AccountBalance;
	}
	return Totale;
}

void BalancesScreen(vector<stData> vUsers)
{
	cout << endl;
	cout << left;
	cout << setw(50) << " " << "Balances List " << vUsers.size() << " Client(s)" << endl;
	cout << endl;
	cout << SeparatorGenerator(120) << endl;

	cout << "|" << setw(20) << "Account Balance" << "|" << setw(60) << "Client Name " << "|" << setw(15) << "Balance" << endl;
	cout << SeparatorGenerator(120) << endl;
	for (stData& C : vUsers)
	{
		cout << "|" << setw(20) << C.Account_number << "|" << setw(60) << C.Name << "|" << setw(40) << "Balance" << endl;
	}
	cout << SeparatorGenerator(120) << endl;
	double Totale = TotaleCalculator(vUsers);
	cout << setw(60) << " " << "Totale Balance : " << Totale << endl;
}

void TransectionMenuScreen(vector<stData> &vUsers)
{
	bool Return = false;
	while (!Return)
	{
		cout << SeparatorGenerator(120) << endl;
		cout << setw(55) << " " << "Transection Menu Screen" << endl;
		cout << SeparatorGenerator(120) << endl;
		cout << setw(50) << " " << "[1] Deposit." << endl;
		cout << setw(50) << " " << "[2] Withdraw." << endl;
		cout << setw(50) << " " << "[3] TotaleBalance." << endl;
		cout << setw(50) << " " << "[4] MainMenu." << endl;
		cout << SeparatorGenerator(120) << endl;
		cout << setw(50) << "=> ";
		int user_Choice;
		cin >> user_Choice;
		cin.ignore();

		switch (user_Choice)
		{
		case 1:
			system("cls");
			DepositScreen(vUsers);
			EndScreen();
			break;
		case 2:
			system("cls");
			WithdrawScreen(vUsers);
			EndScreen();
			break;
		case 3:
			system("cls");
			BalancesScreen(vUsers);
			EndScreen();
			break;
		case 4:
			Return = true;
			break;
		default:
			cout << "unvalid user Choice [1~6]" << endl;
			break;
		}
	}

	system("cls");
}

void DepositScreen(vector<stData>& vUsers)
{
	cout << SeparatorGenerator(120) << endl;
	cout << setw(50) << " " << "Deposit Screen" << endl;
	cout << SeparatorGenerator(120) << endl;

	cout << "Enter Account number : ";
	string Accnumber;
	cin >> Accnumber;
	int Accindex = UserSerchByAccountNumber(vUsers, Accnumber);
	if (Accindex >= 0)
	{
		cout << "The following are Client Details :" << endl;
		cout << "*******************************" << endl;
		PrintClientCard(vUsers.at(Accindex));
		cout << "*******************************" << endl;
		cout << "Enter Deposit Amount : " << endl;
		double DepoAmount;
		cin >> DepoAmount;
		if (Continue_Processe("Are you Sure you want to perfrom this Action ? [1 = tes][0 = no] : "))
		{
			vUsers.at(Accindex).AccountBalance += DepoAmount;
			cout << "Amount added Seccussfuly !" << endl;
			cout << vUsers.at(Accindex).Name << "`s Account mount is : " << vUsers.at(Accindex).AccountBalance << endl;
		}
		
		

	}
	else {
		cout << "Account Not Found...!" << endl;
	}
	UploadDataToFile(vUsers);
	UpdateVector(vUsers);
}

void WithdrawScreen(vector<stData>& vUsers)
{
	cout << SeparatorGenerator(120) << endl;
	cout << setw(50) << " " << "withraw Screen" << endl;
	cout << SeparatorGenerator(120) << endl;

	cout << "Enter Account number : ";
	string Accnumber;
	cin >> Accnumber;
	int Accindex = UserSerchByAccountNumber(vUsers, Accnumber);
	if (Accindex >= 0)
	{
		cout << "The following are Client Details :" << endl;
		cout << "*******************************" << endl;
		PrintClientCard(vUsers.at(Accindex));
		cout << "*******************************" << endl;
		cout << "Enter withdrawed Amount : " << endl;
		double withdrawedAmount;
		cin >> withdrawedAmount;
		if (Continue_Processe("Are you Sure you want to perfrom this Action ? [1 = tes][0 = no] : "))
		{
			vUsers.at(Accindex).AccountBalance -= withdrawedAmount;
			cout << "Amount wathdrawed Seccussfuly !" << endl;
			cout << vUsers.at(Accindex).Name << "`s Account mount is : " << vUsers.at(Accindex).AccountBalance << endl;
		}



	}
	else {
		cout << "Account Not Found...!" << endl;
	}
	UploadDataToFile(vUsers);
	UpdateVector(vUsers);
}

void Mainmenu(vector<stData> &vUsers)
{
	while (true)
	{
		system("cls");
		UpdateVector(vUsers);
		string Separartor = SeparatorGenerator(120);
		cout << endl;
		cout << Separartor << endl;
		cout << setw(55) << " " << "Main Menu" << endl;
		cout << Separartor << endl;
		cout << setw(50) << " " << "[1] Show Clients List." << endl;
		cout << setw(50) << " " << "[2] Add New client." << endl;
		cout << setw(50) << " " << "[3] Delet Client." << endl;
		cout << setw(50) << " " << "[4] Update Client Info." << endl;
		cout << setw(50) << " " << "[5] Find Client." << endl;
		cout << setw(50) << " " << "[6] Transection." << endl;
		cout << setw(50) << " " << "[7] Exit." << endl;
		cout << SeparatorGenerator(120);
		cout << setw(50) << " " << "=> ";
		int userchoice;
		cin >> userchoice;
		cin.ignore();
		switch (userchoice)
		{
		case 1:
			system("cls");
			PrintClients(vUsers);
			break;
		case 2:
			system("cls");
			AddNewClientScreen(vUsers);
			break;
		case 3:
			system("cls");
			DeletScreen(vUsers);
			break;
		case 4:
			system("cls");
			UpdateClientInfoScreen(vUsers);
			break;
		case 5:
			system("cls");
			FindClientScreen(vUsers);
			break;
		case 6:
			system("cls");
			TransectionMenuScreen(vUsers);
			break;
		case 7:
			exit(0);
			break;
		default:
			cout << "unvalid choice...!";
			break;
		}
	}
}


int main()
{
	vector<stData> vUsers;
	LoadDataToVector(vUsers);
	Mainmenu(vUsers);
	return 0;
}

string SeparatorGenerator(int lenght = 120)
{
	string str;
	for (int i = 0; i < lenght; i++)
	{
		str += "-";
	}
	return str;
}
