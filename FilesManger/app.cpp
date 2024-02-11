#include <iostream>     /*Frist Version                                                         */
#include <fstream>      /*IDE : VS Code                                                         */
#include <filesystem>   /*BY : Mdelhajai2000                                                    */
#include <string>       /*Problemes and issues will be Fixed next Version                       */
#include <limits>       /*A library will be Created using The functions in This Programme Soon!!*/
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;
namespace fs = filesystem;
const string DeletedLine = "//@deletedLine@//";

void PathChanger(string& path) {
    if (path.find_first_of(" \t\n\v\"") != string::npos) { // Check if path contains spaces or special characters
        path = R"(")" + path + R"(")";
    }
}


void ReadPositifNumber(int &number, string message)
{
    cout << message;
    cin >> number;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << message;
        cin >> number;
    }
    
}

bool CheckFileExistance(const string& filename)
{
    return fs::exists(filename);
}

void readInput(string& txt, string Message, bool ReadWS = true) {
    cout << Message;
    //cin >> ws;
    getline(cin, txt);
}


void FileCreator() {
    string Filename;
    cout << "Enter File Name (don't use punctuation or spaces):" << endl;
    cin >> Filename;
    cin.ignore();
    Filename += ".txt";
    string path = "Files/" + Filename;
    if (!CheckFileExistance(path)) {
        fstream NewFile;
        NewFile.open(path, ios::out);
        if (NewFile.is_open()) {
            string Line;
            int LineCounter = 0;
            while (Line != "/end") {
                LineCounter++;
                cout << setw(4) << LineCounter << " .  ";
                readInput(Line, "", false);
                if (Line == "/end")
                {
                    continue;
                }
                NewFile << Line << endl;
            }
            NewFile.close();
            cout << "File created successfully." << endl;
        } else {
            cout << "Error: Unable to create the file." << endl;
        }
    } else {
        cout << "The file " << Filename << " already exists in " << path << endl;
    }
}

int PrintFileContent(string path)
{
    cout << "===============================" << endl;
    fstream Myfile;
    PathChanger(path);
    Myfile.open(path, ios::in);
    int LineCounter = 0;
    if (Myfile.is_open())
    {
        string Line;
        while (getline(Myfile, Line))
        {
            LineCounter++;
            cout << setw(4) << LineCounter << " .  " << Line << endl;
        }
        Myfile.close();
    }
    else cout << "We cannot find The file in this path : " << path << endl;
    cout << "===============================" << endl;

    return LineCounter;
}

void FileappendMode(string path)
{
    PathChanger(path);
    cout << endl;
    cout << "====================================" << endl;
    cout << "// " << path << ": " << endl;
    cout << endl;
    fstream AppFile;
    int LineCounter = PrintFileContent(path);
    AppFile.open(path, ios::app);
    if (AppFile.is_open())
    {
        string Line;
        while (Line != "/end")
        {
            LineCounter++;
            cout << setw(4) << LineCounter << " .  ";
            readInput(Line, "");
            AppFile << Line << endl;
        }
        
        AppFile.close();
    }
    cout << endl;
    cout << "====================================" << endl;
    cout << endl;
}

void ResetFile(string path)
{
    fstream Myfile;
    Myfile.open(path, ios::out);
    if (Myfile.is_open())
    {
        Myfile << "";
        cout << "Reset File Seccessfuly Done ! " << endl;
        string Line;
        int LineCounter = 0;
        while (Line != "/end")
        {
            LineCounter++;
            cout << setw(4) << LineCounter << " .  ";
            readInput(Line, "");
            if (Line == "/end") continue;
            Myfile << Line << endl;
        }
        
    }
}

void Load_Lines_From_File_To_Vector(string path, vector<string> &vFile)
{
    fstream Myfile;
    Myfile.open(path, ios::in);
    if (Myfile.is_open())
    {
        string Line;
        while (getline(Myfile, Line))
        {
            vFile.push_back(Line);
        }
        Myfile.close();
    }
}

void Upload_Lines_From_Vector_To_File(string path, vector<string> &vFile)
{
    fstream Myfile;
    Myfile.open(path, ios::out);
    if (Myfile.is_open())
    {
        for (string &Lines : vFile)
        {
            if (Lines == DeletedLine) continue;
            Myfile << Lines << endl;
        }
        Myfile.close();
    }
}

void EditLine(string path)
{
    int user_choice;
    cout << "Type : ~[] To : " << endl;
    cout << "~ [1] : Remove specific Line" << endl;
    cout << "~ [2] : Edit a Specific Line" << endl;
    cin >> user_choice;
    cin.ignore();
    vector<string> vFileLines;
    Load_Lines_From_File_To_Vector(path, vFileLines);
    PrintFileContent(path);
    string Line;
    int LineToRemove;
    int LineToEdit;
    bool IS;
    string newLine;
    switch (user_choice)
    {
    case 1:
        cout << "enter The Line number to Remove it : " << endl;
        ReadPositifNumber(LineToRemove, "=> ");
        cout << "You want to Delet This Line ? : [1 = yes] [0 = no]" << endl;
        cout << setw(4) << LineToRemove << " .  " << vFileLines.at(LineToRemove - 1) << endl;
        cin >> IS;
        if (IS) vFileLines.at(LineToRemove - 1) = DeletedLine;
        else EditLine(path);
        cout << "Line Secssussfuly Deleted !" << endl;
        Upload_Lines_From_Vector_To_File(path, vFileLines);
        break;
    case 2:
        cout << "enter The line numebr To edit : " << endl;
        ReadPositifNumber(LineToEdit, "=> ");
        cout << "Do you want to edit This Line : [1 = yes] [0 = no]" << endl;
        cout << setw(4) << LineToEdit << " .  " << vFileLines.at(LineToEdit - 1) << endl;
        cout << "=> ";
        cin >> IS;
        cin.ignore();
        readInput(newLine, "edited Line : ");
        if (IS) vFileLines.at(LineToEdit - 1) = newLine;
        else EditLine(path);
        cout << "Line num [" << LineToEdit << "] Secsussfuly edited!" << endl;
        Upload_Lines_From_Vector_To_File(path, vFileLines);
        break;
    default:
        break;
    }
}



void FileEditor(string path)
{
    string Path = R"(")" + path + R"(")";
    fstream Myfile;
    int user_choice;
    cout << "Type : ~[] To : " << endl;
    cout << "~ [1] : add other Lines" << endl;
    cout << "~ [2] : remove content and add new Lines" << endl;
    cout << "~ [3] : edit a specific Line" << endl;
    cin >> user_choice;
    cin.ignore();
    switch (user_choice)
    {
    case 1:
        FileappendMode(path);
        break;
    case 2:
        ResetFile(path);
        break;
    case 3:
        EditLine(path);
        break;
    default:
        break;
    }
}

void FileManger()
{
    int user_choice;
    cout << "Type : ~[] To : " << endl;
    cout << "~ [1] : To creat File" << endl;
    cout << "~ [2] : To Print File Content" << endl;
    cout << "~ [3] : To Edit File" << endl;
    ReadPositifNumber(user_choice, "=> ");
    string path;
    switch (user_choice)
    {
    case 1:
        FileCreator();
        break;
    case 2:
        cout << "enter The File path : ";
        cin >> path;
        PrintFileContent(path);
        break;
    case 3:
        cout << "enter The File path : ";
        cin >> path;
        FileEditor(path);
        break;
    case 5319:
    cout << "~~~Source Code~~~" << endl;
        PrintFileContent("C:\\Users\\mdelh\\Documents\\fundamontal.cpp\\github_C++_projects\\Myprojects\\ProjectsCpp\\FilesManger\\app.cpp");
    default:
    cout << "undefined command" << endl;
        break;
    }
}
int main()
{
    FileManger();
    int a;
    cin >> a;
    return 0;
}