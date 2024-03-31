#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include "Encryption.h"
#include "LogIn.h"
// Extension Version with Transaction
// Extention Version with Encryption
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

struct stData
{
	string Account_number;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};

class clsDataFromFile {
	private :

	vector<stData> vClients;

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
		clsEncryption Encryptor;
		fstream Myfile;
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

	string ExportDataToLine(stData Data, string Delim = "#//#")
	{
		clsEncryption Encryptor;
		string Line = "";
		Line += Data.Account_number + Delim + Data.PinCode + Delim
			+ Data.Name + Delim + Data.Phone + Delim + to_string(Data.AccountBalance) + Delim;
		return Encryptor.Enc(Line);
	}


	public :

	void LoadDataToVector(vector<stData>& vClients)
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

		void UpdateVector(vector<stData>& vClients) // Clear the vector an push the Clients from file
		{
			vClients.clear();
			LoadDataToVector(vClients);
		}


};