#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "encryption.h"

using namespace std;

struct stUsers
{
	string UserName;
	string CodePin;
	int Permissions;
};

class UsersLoader
{
private:
	vector<stUsers> _vUsers;
	string UsersDataBasePath = R"(C:\Users\mdelh\Documents\fundamontal.cpp\vs-community\test\Bank_Users.database)";

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

	void LoadRecordsToUsersStruct(vector<string>& vLines)
	{
		fstream Myfile;
		clsEncryption Encryptor;
		Myfile.open(UsersDataBasePath, ios::in);
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

	string UsersDataToRecord(stUsers User)
	{
		string Delimiter = "#//#";
		clsEncryption Encryptor;
		return User.UserName + Delimiter + User.CodePin + Delimiter + to_string(User.Permissions);
	}

public :
	UsersLoader();

	void LoadUsersToVector()
	{
		vector<string> vLines;
		vector<string> vSplitedVector;
		LoadRecordsToUsersStruct(vLines);
		for (int i = 0; i < vLines.size(); i++)
		{
			vSplitedVector = SplitVector(vLines.at(i), "#//#");
			_vUsers.push_back({ vSplitedVector.at(0), vSplitedVector.at(1), stoi(vSplitedVector.at(2)) });
		}
	}

	void UploadUsersDataToFile()
	{
		fstream Myfile;
		Myfile.open(UsersDataBasePath, ios::out);
		if (Myfile.is_open())
		{
			for (stUsers& C : _vUsers)
			{
				Myfile << UsersDataToRecord(C) << endl;
			}
			Myfile.close();
		}
	}

	vector<stUsers> getUsers()
	{
		return _vUsers;
	}

	void setUsers(vector<stUsers> vUsers)
	{
		_vUsers = vUsers;
	}
};

UsersLoader::UsersLoader()
{
	LoadUsersToVector();
}