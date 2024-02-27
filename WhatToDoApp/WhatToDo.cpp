#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

using namespace std;

const string DataBasePath = "Tasks.DataBase";

struct stData
{
	string Task;
	string DeadLine;
	bool TaskStatus; // true = Done False = NotDone
	string CreatDate;
};

string TimeNow()
{
	time_t t = time(0);
	tm* nowHere = localtime(&t);
	char* dt = ctime(&t);
	string Tn = string(dt);
	return string(dt); // Convert char* to std::string
}


void readString(string& str)
{
	cin >> ws;
	getline(cin, str);
}

string PrintTaskStatus(bool TaskSt)
{
	if (TaskSt) return "Done";
	return "Not Done Yet";
}

bool stringToBool(string str)
{
	if (str == "true" || str == "1") return true;
	else if (str == "false" || str == "0") return false;
	return true;
}

stData readData()
{
	stData Data;
	cout << "Enter Task : ";
	readString(Data.Task);
	cout << "Enter Task DeadLine : ";
	readString(Data.DeadLine);
	Data.TaskStatus = false; // not done it just Created in This moument
	string timenow = TimeNow();
	timenow.erase(timenow.end() - 1, timenow.end());
	Data.CreatDate = timenow;
	return Data;
}

string LoadDataToLines(stData Data, string Delim = "//")
{
	string Line = Data.Task + Delim + Data.DeadLine + Delim + to_string(Data.TaskStatus) + Delim + Data.CreatDate + Delim;
	return Line;
}

vector<string> SplitVector(string Line, string Delim = "//")
{
	vector<string> SplitedVector;
	short pos = 0;
	string Word = "";
	while ((pos = Line.find(Delim)) != std::string::npos)
	{
		Word = Line.substr(0, pos);
		if (Word != "")
		{
			SplitedVector.push_back(Word);
		}
		Line.erase(0, pos + Delim.length());
	}

	if (Word != "")
	{
		SplitedVector.push_back(Line);
	}

	return SplitedVector;
}

void LoadLines_From_File_To_vector(vector<string> &vLines)
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

void LoadDataToStruct(vector<stData> &stData)
{
	vector<string> vLines;
	vector<string> SplitedVector;
	LoadLines_From_File_To_vector(vLines);
	for (string& Line : vLines)
	{
		SplitedVector = SplitVector(Line);
		stData.push_back({ SplitedVector.at(0), SplitedVector.at(1), stringToBool(SplitedVector.at(2)), SplitedVector.at(3)});
	}
}

void UploadDataToFile(vector<stData> Data)
{
	fstream MyFile;
	MyFile.open(DataBasePath, ios::out);
	if (MyFile.is_open())
	{
		for (stData& C : Data)
		{
			MyFile  << LoadDataToLines(C) << endl;
		}
	}
}

void Refresh(vector<stData> &Data)
{
	Data.clear();
	LoadDataToStruct(Data);
}

string SeparatorGen(int lenght = 120)
{
	string Sep = "";
	for (int i = 0; i < lenght; i++) Sep += "-";
	return Sep;
}

void AddTaskScreen(vector<stData>& TaskData)
{
	bool Addmore = true;
	while (Addmore)
	{
		cout << SeparatorGen(120) << endl;
		cout << setw(50) << "Creat New Task" << endl;
		cout << SeparatorGen(120) << endl;
		cout << "** Task Number is : " << TaskData.size() + 1 << " **" << endl;

		TaskData.push_back(readData());
		UploadDataToFile(TaskData);
		cout << "Add another Task ? : [1 = yes][0 = no : Back To Menu!] : ";
		cin >> Addmore;
		system("cls");
	}
}

void EndScreen()
{
	cout << "Press Any Key To Close..." << endl;
	system("pause>0");
	system("cls");
}


void RemoveTasckScreen(vector<stData> &TaskData)
{
	cout << SeparatorGen(120) << endl;
	cout << setw(50) << " " << "Remove Tasck Screen" << endl;
	cout << SeparatorGen(120) << endl;
	cout << "\n\n\n";
	cout << left;
	cout << CYAN;
	cout << setw(40) << " " << "------------------------------------------------" << endl;
	cout << setw(40) << " " << "| Task Number |" << setw(32) << " Task Detail" << "|" << endl;
	cout << setw(40) << " " << "------------------------------------------------" << endl;
	
	for (int i = 0; i < TaskData.size(); i++)
	{
		cout << setw(40) << " " << "|" << setw(13) << i + 1 << "|" << setw(32) << TaskData.at(i).Task << "|" << endl;
	}

	cout << setw(40) << " " << "------------------------------------------------" << endl;
	cout << setw(40) << " " << "For More Details Go To Show All Tasks Screen!" << endl;
	cout << RESET;

	cout << "Enter Task Number to Remove : ";
	int Tnumber;
	cin >> Tnumber;
	bool IsRemove;
	try
	{
		cout << "Are sure To remove This Task : |" << TaskData.at(Tnumber - 1).Task << "| ? [1 = yes][0 = no] : " << endl;
		cin >> IsRemove;
		if (IsRemove)
		{
			TaskData.erase(TaskData.begin() + (Tnumber - 1));
			cout << "Task number : " << Tnumber << " Removed Seccussfuly ...!" << endl;
		}
	}
	catch (const std::out_of_range)
	{
		cout << RED << "Tasck Not Found...!" << RESET << endl;
	}
	UploadDataToFile(TaskData);
	cout << "Press Any key To Continue !" << endl;
	system("pause>0");
}

void ShowTaskDetailsScreen(vector<stData> TaskData)
{
	cout << SeparatorGen(120) << endl;
	cout << setw(50) << " " << "Show Task details Screen" << endl;
	cout << SeparatorGen(120) << endl;
	cout << "\n\n\n";
	cout << left;
	cout << CYAN;
	cout << setw(40) << " " << "------------------------------------------------" << endl;
	cout << setw(40) << " " << "| Task Number |" << setw(32) << " Task Detail" << "|" << endl;
	cout << setw(40) << " " << "------------------------------------------------" << endl;

	for (int i = 0; i < TaskData.size(); i++)
	{
		cout << setw(40) << " " << "|" << setw(13) << i + 1 << "|" << setw(32) << TaskData.at(i).Task << "|" << endl;
	}

	cout << setw(40) << " " << "------------------------------------------------" << endl;
	cout << RESET;

	cout << "enter Task Number : " << endl;
	int Accnum;
	cin >> Accnum;
	cin.ignore();
	bool IsFound;
	try // Apre on va ajouter account number to stdata pour ne pas utiliser try
	{
		string test;
		test = TaskData.at(Accnum - 1).Task;
		IsFound = true;
	}
	catch (const std::out_of_range)
	{
		cout << "Task Not Found ...!" << endl;
		IsFound = false;
	}

	if (IsFound)
	{
		cout << "Task details : " << endl;
		cout << "~ Task : " << TaskData.at(Accnum - 1).Task << endl;
		cout << "~ Created on : " << TaskData.at(Accnum - 1).CreatDate << endl;
		cout << "~ Dead Line : " << TaskData.at(Accnum - 1).DeadLine << endl;
		cout << "~ Task Satatus : ";
		if (TaskData.at(Accnum - 1).TaskStatus) cout << GREEN;
		else cout << RED;
		cout << PrintTaskStatus(TaskData.at(Accnum - 1).TaskStatus) << RESET << endl;
	}
	cout << "Press Any Key To Continue ...!" << endl;
	system("pause>0");
}

void ShowAllTasksScreen(vector<stData>& TaskData)
{
	cout << SeparatorGen(120) << endl;
	cout << setw(50) << " " << "Show " << TaskData.size() << " Tasks Screen" << endl;
	cout << SeparatorGen(120) << endl;
	cout << "\n\n\n" << endl;
	cout << left;
	cout << SeparatorGen(120) << endl;
	cout << "|" << setw(14) << " Task Number" << "|" << setw(44) << "                       Task" << "|" << setw(26) << "        Created Date " << "|" << setw(17) << "     Dead Line" << "|" << setw(12) << " Task status " << "|" << endl;
	cout << SeparatorGen(120) << endl;
	for (int i = 0; i < TaskData.size(); i++)
	{
		cout << "|" << setw(14) << i + 1 << "|" << setw(44) << TaskData.at(i).Task << "|" << setw(26) << TaskData.at(i).CreatDate << "|" << setw(17) << TaskData.at(i).DeadLine << "|";
		if (TaskData.at(i).TaskStatus) cout << GREEN;
		else cout << RED;
		cout << setw(12) << PrintTaskStatus(TaskData.at(i).TaskStatus) << RESET << " |" << endl;
	}
	cout << SeparatorGen(120) << "\n" << endl;
	cout << "Presse Any Key To continue...!";
	system("pause>0");
}

void MainMenu(vector<stData> &Task_Data)
{
	while(true)
	{
		Refresh(Task_Data);
		system("cls");
		cout << SeparatorGen(120) << endl;
		cout << setw(50) << " " << "Main menu Sceen" << endl;
		cout << SeparatorGen(120) << endl;
		cout << setw(50) << " " << "[1] Add Tasck." << endl;
		cout << setw(50) << " " << "[2] Remove Tasck." << endl;
		cout << setw(50) << " " << "[3] Show Task Details." << endl;
		cout << setw(50) << " " << "[4] Show All Tasks." << endl;
		cout << setw(50) << " " << "[5] Exit." << endl;
		cout << SeparatorGen(120) << endl;
		cout << setw(50) << " " << "=> ";
		int user_Choice;
		cin >> user_Choice;
		cin.ignore();
		switch (user_Choice)
		{
		case 1:
			system("cls");
			AddTaskScreen(Task_Data);
			//EndScreen(); not nedded!
			break;
		case 2:
			system("cls");
			RemoveTasckScreen(Task_Data);
			break;
		case 3:
			system("cls");
			ShowTaskDetailsScreen(Task_Data);
			break;
		case 4:
			system("cls");
			ShowAllTasksScreen(Task_Data);
			break;
		case 5:
			exit(0);
			break;
		default:
			cout << "unvalid Choice [1~5]" << endl;
			break;
		}
	}
 }

int main()
{
	vector<stData> stTaskes;
	LoadDataToStruct(stTaskes); // Load Data from The file to The vector Whene The programme start
	MainMenu(stTaskes);

	return 0;
}