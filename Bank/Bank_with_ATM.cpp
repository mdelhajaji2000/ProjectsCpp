#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
// #xtension Version with Transaction

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
const string UsersDataBasePath = "Bank_Users.database";

struct stData
{
	string Account_number;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};

struct stUsers {
	string UserName;
	string CodePin;
	int Permissions;
};

vector<string> SplitVector(string Line, string Delim = "#//#");
void LoadLinesToUersStruct(vector<string>& vLines);
void LoadDataToVector(vector<stData>& vClients);
string ExportDataToLine(stData Data, string Delim);
void addClientRow(const stData& Data);
void PrintClients(const vector<stData> vClients);
void UploadDataToFile(vector<stData> vClients);
void AddNewClientScreen(vector<stData> vClients);
void UpdateVector(vector<stData>& vClients);
int UserSerchByAccountNumber(vector<stData> vClients, string account_number);
void DeletScreen(vector<stData>& vClients);
void PrintClientCard(stData UserData);
void UpdateClientInfoScreen(vector<stData>& vClients);
void FindClientScreen(vector<stData> vClients);
void EndScreen();
double TotaleCalculator(vector<stData> vClients);
void BalancesScreen(vector<stData> vClients);
void TransectionMenuScreen(vector<stData>& vClients);
void DepositScreen(vector<stData>& vClients);
void WithdrawScreen(vector<stData>& vClients);
int ReaduserChoice();
void Mainmenu(vector<stData>& vClients, vector<stUsers>& vUsers);
void PrintUserRow(stUsers User);
void PrintUsersList(const vector<stUsers> vUsers);
stUsers ReadUserData(vector<stUsers> User);
void AddUserScreen(vector<stUsers>& vUsers);
void UsersManger(vector<stUsers>& vUsers);
bool CheckUserName(vector<stUsers> Users, string Username);
bool CheckPassword(vector<stUsers> Users, string pwd);
int ReadPermissions(stUsers User);
stUsers GetUSerByUsername(vector<stUsers> vUsers, string Username);
void UserManagementScreen(vector<stUsers>& Users);
void LoadUsersToVector(vector<stUsers>& vUsers);
string UsersDataToRecord(stUsers User);
void UploadUsersDataToFile(vector<stUsers>& vUsers);
void LoadRecordsToUsersStruct(vector<string>& vLines);
void UpdateVector(vector<stUsers>& vUsers);
int main();
string SeparatorGenerator(int lenght = 120);
bool CheckPermession(stUsers User, int FunctionID); // Function ID the Function Permession Number get in Reada Permession
												    // Every Function or Choice in MainMenu Screen got a number like "[1] Clients List"...  



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

double ReadPositifNumber(string Message)
{
	cout << Message;
	double number;
	cin >> number;
	return number;
}

void readDataFromUser(vector<stData> vClients, stData& Data, bool Isnew = true)// true = new_accont; false = edit_account
{
	bool Continue = false;
	while (!Continue)
	{
		if (Isnew)
		{
			string tempAccnum = ReadString("Enter Account Number : ");
			if (UserSerchByAccountNumber(vClients, tempAccnum) == -1)
			{
				Data.Account_number = tempAccnum;
				Continue = true;
			}
			else
			{
				cout << " " << "account with " << tempAccnum << " account number alerdy exist !" << endl;
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
	Myfile.open(ClientDataBasePath, ios::in);
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

void LoadDataToVector(vector<stData>& vClients)
{
	vector<string> vLines;
	vector<string> vSplitedVector;
	LoadLinesToUersStruct(vLines);
	for (int i = 0; i < vLines.size(); i++)
	{
		vSplitedVector = SplitVector(vLines.at(i));
		vClients.push_back({ vSplitedVector.at(0), vSplitedVector.at(1), vSplitedVector.at(2), vSplitedVector.at(3), stod(vSplitedVector.at(4)) });
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

void PrintClients(const vector<stData> vClients)
{
	cout << endl;
	cout << setw(50) << " " << "Clients List (" << vClients.size() << ") Client(s)" << endl;
	cout << endl;
	cout << left;
	cout << SeparatorGenerator(120);
	cout << "|" << setw(16) << " Account Number" << "|" << setw(13) << " Pin Code " << "|" << setw(38 + 5) << " Client Name" << "|" << setw(15 + 6) << " Phone" << "|" << setw(20) << " Balance" << "|" << endl;
	cout << "|----------------|-------------|-------------------------------------------|---------------------|--------------------|" << endl;
	for (const stData& line : vClients)
	{
		addClientRow(line);
	}
	cout << "|----------------|-------------|-------------------------------------------|---------------------|--------------------|" << endl;


	cout << "Press any key To Continue..." << endl;
	system("pause>0");
	system("cls");
}

void UploadDataToFile(vector<stData> vClients)
{
	fstream Myfile;
	Myfile.open(ClientDataBasePath, ios::out);
	if (Myfile.is_open())
	{
		for (stData& C : vClients)
		{
			Myfile << ExportDataToLine(C) << endl;
		}
		Myfile.close();
	}
}

void AddNewClientScreen(vector<stData> vClients)
{
	cout << SeparatorGenerator(120) << endl;
	cout << setw(50) << " " << "Add New Client Screen" << endl;
	cout << SeparatorGenerator(120) << endl;
	stData NewClient;
	readDataFromUser(vClients, NewClient);
	vClients.push_back(NewClient);
	cout << "New Client Added Succssusfly !" << endl;
	UploadDataToFile(vClients);
	LoadDataToVector(vClients);
	cout << endl;
	cout << "Press any key to Continue..." << endl;
	system("pause>0");
	system("cls");
	return;
}

void UpdateVector(vector<stData>& vClients) // Clear the vector an push the Clients from file
{
	vClients.clear();
	LoadDataToVector(vClients);
}

int UserSerchByAccountNumber(vector<stData> vClients, string account_number)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (account_number == vClients.at(i).Account_number) return i;
	}
	return -1;
}

void DeletScreen(vector<stData>& vClients)
{
	string Accnum;
	cout << SeparatorGenerator(120) << endl;
	cout << setw(50) << " " << "Delet Client Screen" << endl;
	cout << SeparatorGenerator(120) << endl;

	cout << "Enter Account Number : ";
	cin >> Accnum;
	int Account_index = UserSerchByAccountNumber(vClients, Accnum);
	if (Account_index >= 0)
	{
		cout << "Account : " << Accnum << " Was found!" << endl;
		cout << "Client Data : " << endl;
		PrintClientCard(vClients.at(Account_index));
		bool IsDelet;
		cout << "Are you Sure To Delet This Client ? [1 = true][0 = false] : ";
		cin >> IsDelet;

		if (IsDelet)
		{
			vClients.erase(vClients.begin() + Account_index);
			cout << "Account Seccussfuly Deleted ...!" << endl;
		}
		UploadDataToFile(vClients);
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

void UpdateClientInfoScreen(vector<stData>& vClients)
{
	cout << SeparatorGenerator(120) << endl;
	cout << setw(50) << " " << "Update Client Info Screen" << endl;
	cout << SeparatorGenerator(120) << endl;
	cout << "Enter Account Number : ";
	string Accnum;
	cin >> Accnum;
	cin.ignore();
	int Acc_index = UserSerchByAccountNumber(vClients, Accnum);
	if (Acc_index >= 0)
	{
		cout << "Account : " << Accnum << " was Found !" << endl;
		cout << "Client Info : " << endl;
		PrintClientCard(vClients.at(Acc_index));

		readDataFromUser(vClients, vClients.at(Acc_index), false);

		cout << "Do you Want To save Changes [1 = yes][0 = no] : " << endl;
		int Issave;
		cin >> Issave;
		if (Issave)	UploadDataToFile(vClients);
	}
	else {
		cout << "Account : " << Accnum << " Not Found !" << endl;
	}

	cout << "Enter Any key To continue...";
	system("pause>0");
	system("cls");
}

void FindClientScreen(vector<stData> vClients)
{
	cout << SeparatorGenerator(120) << endl;
	cout << setw(55) << " " << "Find Client Screen" << endl;
	cout << SeparatorGenerator(120) << endl;
	cout << "Enter Account Number : ";
	string Accnum;
	cin >> Accnum;
	int accindex = UserSerchByAccountNumber(vClients, Accnum);
	if (accindex >= 0)
	{
		cout << "Account : " << Accnum << " was Found !" << endl;
		cout << "Client Info : " << endl;
		PrintClientCard(vClients.at(accindex));

	}
	else (cout << "Account " << Accnum << " was not found ..!" << endl);

	cout << "Presse Any Key To Continue...";
	system("pause>0");
	system("cls");
}

void EndScreen()
{
	cout << endl;
	cout << "Presse Any Key To Continue...";
	system("pause>0");
	system("cls");
}

// Transection Extention Functions :
void DepositScreen(vector<stData>& vClients);
void WithdrawScreen(vector<stData>& vClients);

double TotaleCalculator(vector<stData> vClients)
{
	double Totale = 0;
	for (stData& C : vClients)
	{
		Totale += C.AccountBalance;
	}
	return Totale;
}

void BalancesScreen(vector<stData> vClients)
{
	cout << endl;
	cout << left;
	cout << setw(50) << " " << "Balances List " << vClients.size() << " Client(s)" << endl;
	cout << endl;
	cout << SeparatorGenerator(120) << endl;

	cout << "|" << setw(20) << "Account Balance" << "|" << setw(60) << "Client Name " << "|" << setw(15) << "Balance" << endl;
	cout << SeparatorGenerator(120) << endl;
	for (stData& C : vClients)
	{
		cout << "|" << setw(20) << C.Account_number << "|" << setw(60) << C.Name << "|" << setw(40) << "Balance" << endl;
	}
	cout << SeparatorGenerator(120) << endl;
	double Totale = TotaleCalculator(vClients);
	cout << setw(60) << " " << "Totale Balance : " << Totale << endl;
}

void TransectionMenuScreen(vector<stData>& vClients)
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
			DepositScreen(vClients);
			EndScreen();
			break;
		case 2:
			system("cls");
			WithdrawScreen(vClients);
			EndScreen();
			break;
		case 3:
			system("cls");
			BalancesScreen(vClients);
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

void DepositScreen(vector<stData>& vClients)
{
	cout << SeparatorGenerator(120) << endl;
	cout << setw(50) << " " << "Deposit Screen" << endl;
	cout << SeparatorGenerator(120) << endl;

	cout << "Enter Account number : ";
	string Accnumber;
	cin >> Accnumber;
	int Accindex = UserSerchByAccountNumber(vClients, Accnumber);
	if (Accindex >= 0)
	{
		cout << "The following are Client Details :" << endl;
		cout << "*******************************" << endl;
		PrintClientCard(vClients.at(Accindex));
		cout << "*******************************" << endl;
		cout << "Enter Deposit Amount : " << endl;
		double DepoAmount;
		cin >> DepoAmount;
		if (Continue_Processe("Are you Sure you want to perfrom this Action ? [1 = tes][0 = no] : "))
		{
			vClients.at(Accindex).AccountBalance += DepoAmount;
			cout << "Amount added Seccussfuly !" << endl;
			cout << vClients.at(Accindex).Name << "`s Account mount is : " << vClients.at(Accindex).AccountBalance << endl;
		}



	}
	else {
		cout << "Account Not Found...!" << endl;
	}
	UploadDataToFile(vClients);
	UpdateVector(vClients);
}

void WithdrawScreen(vector<stData>& vClients)
{
	cout << SeparatorGenerator(120) << endl;
	cout << setw(50) << " " << "withraw Screen" << endl;
	cout << SeparatorGenerator(120) << endl;

	cout << "Enter Account number : ";
	string Accnumber;
	cin >> Accnumber;
	int Accindex = UserSerchByAccountNumber(vClients, Accnumber);
	if (Accindex >= 0)
	{
		cout << "The following are Client Details :" << endl;
		cout << "*******************************" << endl;
		PrintClientCard(vClients.at(Accindex));
		cout << "*******************************" << endl;
		cout << "Enter withdrawed Amount : " << endl;
		double withdrawedAmount;
		cin >> withdrawedAmount;
		if (Continue_Processe("Are you Sure you want to perfrom this Action ? [1 = tes][0 = no] : "))
		{
			vClients.at(Accindex).AccountBalance -= withdrawedAmount;
			cout << "Amount wathdrawed Seccussfuly !" << endl;
			cout << vClients.at(Accindex).Name << "`s Account mount is : " << vClients.at(Accindex).AccountBalance << endl;
		}



	}
	else {
		cout << "Account Not Found...!" << endl;
	}
	UploadDataToFile(vClients);
	UpdateVector(vClients);
}

int ReaduserChoice()
{
	int userChoice;
	cout << setw(50) << " " << "=> ";
	cin >> userChoice;
	while (cin.fail())
	{
		cout << "Invalid Input !" << endl;
		cout << setw(50) << " " << "=> ";
		cin >> userChoice;
		cin.ignore(std::numeric_limits<std::streamsize>::max());
		cin.clear();
	}
	return userChoice;
}

void UsersManger(vector<stUsers> &vUsers);

void Mainmenu(vector<stData>& vClients, vector<stUsers> &vUsers, stUsers User) // User = Loged In user or The Actual User
{
	while (true)
	{
		system("cls");
		UpdateVector(vClients);
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
		cout << setw(50) << " " << "[7] Manage User." << endl;
		cout << setw(50) << " " << "[8] Log out." << endl;
        cout << setw(50) << " " << "[9] ATM System." << endl;
		cout << setw(50) << " " << "[10] Exit and Close." << endl;
		cout << SeparatorGenerator(120);
		int userchoice = ReaduserChoice();
		cin.ignore();
		switch (userchoice)
		{
		case 1:
			system("cls");
			if (CheckPermession(User, 1)) PrintClients(vClients);
			break;
		case 2:
			system("cls");
			if (CheckPermession(User, 2)) AddNewClientScreen(vClients);
			break;
		case 3:
			system("cls");
			if (CheckPermession(User, 3)) DeletScreen(vClients);
			break;
		case 4:
			system("cls");
			if (CheckPermession(User, 4)) UpdateClientInfoScreen(vClients);
			break;
		case 5:
			system("cls");
			if (CheckPermession(User, 5)) FindClientScreen(vClients);
			break;
		case 6:
			system("cls");
			if (CheckPermession(User, 6)) TransectionMenuScreen(vClients);
			break;
		case 7:
			system("cls");
			if (CheckPermession(User, 7)) UsersManger(vUsers);
			break;
		case 8:
			system("cls");
			return;
			break;
		case 9:
			system("ATM_System.exe");
			break;
        case 10:
            exit(0);
            break;
		default:
			cout << "unvalid choice...!";
			break;
		}
	}
}

// extention 2 Functions : 
void LoadRecordsToUsersStruct(vector<string>& vLines);

void PrintUserRow(stUsers User)
{
	cout << left;
	cout << "|" << setw(40) << User.UserName << "|" << setw(40) << User.CodePin << "|" << setw(36) << User.Permissions << "|" << endl;
}

void PrintUsersList(const vector<stUsers> vUsers)
{
	string Sep = SeparatorGenerator(120);
	cout << endl;
	cout << setw(50) << " " << "Users List (" << vUsers.size() << ") User(s)" << endl;
	cout << endl;
	cout << left;
	cout << Sep << endl;
	cout << "|" << setw(40) << "User Name" << "|" << setw(40) << "User Pin Code" << "|" << setw(36) << "User Permission" << "|" << endl;
	cout << Sep;
	for (stUsers C : vUsers)
	{
		PrintUserRow(C);
	}
	cout << Sep << endl;
	EndScreen();
}

stUsers ReadUserData(vector<stUsers> vUsers)
{
	stUsers User;
	bool Continue = false;
	while (!Continue)
	{
		string tempUsername = ReadString("Creat User name : ");
		if (!CheckUserName(vUsers, tempUsername))
		{
			User.UserName = tempUsername;
			Continue = true;
		}
		else
		{
			cout << " " << "account with [" << tempUsername << "] user name alerdy exist !" << endl;
			Continue = false;
		}
		if (Continue)
		{
			User.CodePin = ReadString("Creat a Code Pin : ");
			User.Permissions = ReadPermissions(User);
		}
	}
	return User;
}

void AddUserScreen(vector<stUsers> &vUsers)
{
	string Separator = SeparatorGenerator(120);
	bool Continue = true;
	while (Continue)
	{
		system("cls");
		cout << Separator << endl;
		cout << setw(45) << " " << "Manage Users : Add new User" << endl;
		cout << Separator << endl;
		vUsers.push_back(ReadUserData(vUsers));
		UploadUsersDataToFile(vUsers);
		cout << "user add Successufly !" << endl;
		Continue = Continue_Processe("Do you want to add another user ? : {1 = yes} {0 = no} : ");
		cin.ignore();
	}
	
	EndScreen();
}

int ReadPermissions(stUsers User)
{
	bool IsGet;
	int PermessionsCounter;
	cout << "Give Full Acsses To : " << User.UserName << " ? {yes = 1} {no = 0} : ";
	cin >> IsGet;
	if (IsGet)PermessionsCounter = -1;// Give Full Access To User
	else
	{
		cout << "Do you want To give Access To : {1 = true} {0 = false}" << endl;
		cout << endl;
		cout << "Show Clients List : 1/0 : ";
		cin >> IsGet;
		if (IsGet) PermessionsCounter = 1;
		cout << "Add New Client ? 1/0 : ";
		cin >> IsGet;
		if (IsGet) PermessionsCounter = (PermessionsCounter | 2);
		cout << "Remove Client ? 1/0 : ";
		cin >> IsGet;
		if (IsGet) PermessionsCounter = (PermessionsCounter | 3);
		cout << "Update Client Info ? 1/0 : ";
		cin >> IsGet;
		if (IsGet) PermessionsCounter = (PermessionsCounter | 4);
		cout << "Find Client ? 1/0 : ";
		cin >> IsGet;
		if (IsGet) PermessionsCounter = (PermessionsCounter | 5);
		cout << "Transactions ? 1/0 : ";
		cin >> IsGet;
		if (IsGet) PermessionsCounter = (PermessionsCounter | 6);
		cout << "Manage Users ? 1/0 : ";
		cin >> IsGet;
		if (IsGet) PermessionsCounter = (PermessionsCounter | 7);
	}
	return PermessionsCounter;
}

bool CheckPermession(stUsers User, int FunctionID)
{
	string Separator = SeparatorGenerator(120);
	if (User.Permissions == (User.Permissions | FunctionID)) return true;
	else
	{
		cout << Separator << endl;
		cout << RED << "Action Denied !" << endl;
		cout << "You Dont Have PErmession To Do That !" << endl;
		cout << "Please Contact You Admin" << endl;
		cout << RESET;
		cout << Separator << endl;
		cout << "\n\n\n";
		EndScreen();
	}
	return false;
}

void PrintUserCard(stUsers User)
{
	cout << left;
	cout << "**********************************" << endl;
	cout << setw(12) << "User name" << ": " << User.UserName << endl;
	cout << setw(12) << "PIN Code" << ": " << User.CodePin << endl;
	cout << setw(12) << "Permessions" << ": " << User.Permissions << endl;
	cout << "**********************************" << endl;
}

int GetUserIndex(vector<stUsers> vUsers, string Username)
{
		for (int i = 0; i < vUsers.size(); i++)
		{
			if (vUsers.at(i).UserName == Username)
			{
				return i;
			}
		}
		return false;
}

void DeletUser(vector<stUsers> &Users)
{
	string Separator = SeparatorGenerator(120);
	cout << Separator << endl;
	cout << setw(45) << " " << "Manage Users : Delet User Screen" << endl;
	cout << Separator << endl;

	string username = ReadString("enter user name : ");
	stUsers User = GetUSerByUsername(Users, username);
	int Account_index;
	bool IsDelet;
	if (CheckUserName(Users, username))
	{
		PrintUserCard(User);
		cout << "\n\n";
	    IsDelet = Continue_Processe("Are you sure to Delet [" + username + "] ? {1 = yes} {0 = no} : ");
		Account_index = CheckUserName(Users, username);
		if (IsDelet)
		{
			Users.erase(Users.begin() + Account_index); 
			cout << "Users Seccussfuly Deleted ...!" << endl;
		}
	}
	else {
		cout << "User [" << username << "] Not Found !" << endl;
	}
	UploadUsersDataToFile(Users);
	EndScreen();
}

void readUpdatedUserData(stUsers &User)
{
	cout << "Edit " << User.UserName << "`s Data : " << endl;
	cout << setw(50) << " " << "[1] Edit User Name." << endl;
	cout << setw(50) << " " << "[2] Edit Pin Code." << endl;
	cout << setw(50) << " " << "[3] Edit Permessions." << endl;
	int UserChoice;
	cin >> UserChoice;
	cin.ignore();

	switch (UserChoice)
	{
	case 1:
		cout << "enter new user name : [Actual : " << User.UserName << " ]" << endl;
		cout << setw(50) << " ";  User.UserName = ReadString("=>");
		break;
	case 2:
		cout << "enter new Pin Code : [Actual : " << User.CodePin << "]" << endl;
		cout << setw(50) << " "; User.CodePin = ReadString("=>");
		break;
	case 3:
		User.Permissions = ReadPermissions(User);
		break;
	default:
		cout << "Unvalid Choice...!" << endl;
		break;
	}

}

void UpdateUser(vector<stUsers> &vUsers)
{
	string Separator = SeparatorGenerator(120);
	cout << Separator << endl;
	cout << setw(45) << " " << "Manage Users : Update User Info" << endl;
	cout << Separator << endl;

	string User_name;
	cout << "enter user name : ";
	cin >> User_name;
	cin.ignore();
	int Acc_index = GetUserIndex(vUsers, User_name);
	if (CheckUserName(vUsers, User_name))
	{
		if (Acc_index >= 0)
		{
			cout << "Account : " << User_name << " was Found !" << endl;
			cout << "User Data : " << endl;
			PrintUserCard(vUsers.at(Acc_index));

			readUpdatedUserData(vUsers.at(Acc_index));

			cout << "Do you Want To save Changes [1 = yes][0 = no] : " << endl;
			bool Issave;
			cin >> Issave;
			if (Issave)	UploadUsersDataToFile(vUsers);
		}
	}
	else {
		cout << "User : " << User_name << " Not Found !" << endl;
	}
	

	EndScreen();
}

void Find_User_Using_User_name(vector<stUsers> &vUsers)
{
	string Separator = SeparatorGenerator(120);
	cout << Separator << endl;
	cout << setw(45) << "Users Manager : Find User" << endl;
	cout << Separator << endl;

	string user_name = ReadString("enter user name : ");
	int userIndex = GetUserIndex(vUsers, user_name);
	if (CheckUserName(vUsers, user_name))
	{
		cout << "user Found !" << endl;
		cout << user_name << " Data are : " << endl;
		PrintUserCard(vUsers.at(userIndex));
	}
	else {
		cout << "user with : [" << user_name << "] user_name not Found !" << endl;
	}

	cout << endl;
	EndScreen();
}

void UsersManger(vector<stUsers>& vUsers)
{
	while (true)
	{
		UpdateVector(vUsers);
		string Sep = SeparatorGenerator(120);
		cout << Sep << endl;
		cout << setw(45) << " " << "Manage Users Menue Screen" << endl;
		cout << Sep << endl;
		cout << setw(50) << " " << "[1] Users List." << endl;
		cout << setw(50) << " " << "[2] Add New User." << endl;
		cout << setw(50) << " " << "[3] Delet User." << endl;
		cout << setw(50) << " " << "[4] Update User Info." << endl;
		cout << setw(50) << " " << "[5] Find User." << endl;
		cout << setw(50) << " " << "[6] Main menu." << endl;
		cout << Sep << endl;
		int userChoice = ReaduserChoice();
		cin.ignore();
		switch (userChoice)
		{
		case 1:
			system("cls");
			PrintUsersList(vUsers);
			break;
		case 2:
			system("cls");
			AddUserScreen(vUsers);
			break;
		case 3:
			system("cls");
			DeletUser(vUsers);
			break;
		case 4:
			system("cls");
			UpdateUser(vUsers);
			break;
		case 5:
			system("cls");
			Find_User_Using_User_name(vUsers);
			break;
		case 6:
			return;
		default:
			cout << "Invalid Choice !" << endl;
			system("cls");
			break;
		}
	}
}

bool CheckUserName(vector<stUsers> Users, string Username)
{
	for (int i = 0; i < Users.size(); i++)
	{
		if (Users.at(i).UserName == Username) // if the user index is 0 the function will return 1
		{
			return true;
		}
	}
	return false;
}

bool CheckPassword(vector<stUsers> Users, string pwd)
{
	for (int i = 0; i < Users.size(); i++)
	{
		if (Users.at(i).CodePin == pwd) return true;
	}
	return false;
}

stUsers GetUSerByUsername(vector<stUsers> vUsers, string Username)
{
	for (int i = 0; i < vUsers.size(); i++)
	{
		if (vUsers.at(i).UserName == Username) return vUsers.at(i);
	}
}

stUsers	LogInScreen(vector<stUsers> &Users)
{
	while (true)
	{
		cout << SeparatorGenerator(120) << endl;
		cout << setw(50) << " " << "Log In Screen" << endl;
		cout << SeparatorGenerator(120) << endl;

		string input_Username = ReadString("enter user name : "), input_Pin_Code = ReadString("enter Pin Code : ");
		if (CheckPassword(Users, input_Pin_Code) && CheckUserName(Users, input_Username))
		{
			return GetUSerByUsername(Users, input_Username);
		}
		else cout << "Invalid Username / PIN Code..!" << endl;
		EndScreen();
	}
}

void LoadUsersToVector(vector<stUsers>& vUsers)
{
	vector<string> vLines;
	vector<string> vSplitedVector;
	LoadRecordsToUsersStruct(vLines);
	for (int i = 0; i < vLines.size(); i++)
	{
		vSplitedVector = SplitVector(vLines.at(i));
		vUsers.push_back({ vSplitedVector.at(0), vSplitedVector.at(1), stoi(vSplitedVector.at(2)) });
	}
}

string UsersDataToRecord(stUsers User)
{
	string Delimiter = "#//#";
	return User.UserName + Delimiter + User.CodePin + Delimiter + to_string(User.Permissions);
}

void UploadUsersDataToFile(vector<stUsers> &vUsers)
{
	fstream Myfile;
	Myfile.open(UsersDataBasePath, ios::out);
	if (Myfile.is_open())
	{
		for (stUsers& C : vUsers)
		{
			Myfile << UsersDataToRecord(C) << endl;
		}
		Myfile.close();
	}
}

void LoadRecordsToUsersStruct(vector<string>& vLines)
{
	fstream Myfile;
	Myfile.open(UsersDataBasePath, ios::in);
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

void UpdateVector(vector<stUsers>& vUsers) // Clear the vector an push the Clients from file
{
	vUsers.clear();
    LoadUsersToVector(vUsers);
}


void LogIn()
{
	vector<stData> vClients;
	vector<stUsers> vUsers;
	LoadDataToVector(vClients);
	LoadUsersToVector(vUsers);

	while (true)
	{
		Mainmenu(vClients, vUsers, LogInScreen(vUsers));
	}
}

int main()
{
	LogIn();

	return 0;
}

string SeparatorGenerator(int lenght)
{
	string str;
	for (int i = 0; i < lenght; i++)
	{
		str += "-";
	}
	return str;
} //
