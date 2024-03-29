//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//==========================[Whats new]=============================//
// * Fix Problemes
// * Export The Table to a fil [.txt, .pdf. word]
// * Fix Table settings Name [Large Colone == Colone 2]
// * Edit The code Frormat and fix problemees
// * Add Table Title
// * add Help Func
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#pragma warning(disable : 4996)


#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdio>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

struct stTable {
    int Colone_1_width = 15;
    int Colone_3_width = 15;
    int Colone_2_width = 45;
    char Left_or_Right = 'L'; // R or L || r or l {'l' = left} {'R' = right}
    string Colone_1_title = "Example:";
    string Colone_2_title = "Large Colone Here";
    string Colone_3_title = "Colone 2";
    string Colon_1_string;
    string Colone_3_string;
    string Colone_2_String;
    char Space_char = '=';
};

string getTime()
{
    time_t t = time(0);

    char* dt = ctime(&t);
    return  dt;
}

void readInput(string& txt, string Message) {
    cout << Message;
    cin >> ws;
    getline(cin, txt);
}

void ReadPositifNumber(int &number, string Message) {
    cout << Message;
    cin >> number;
    while (number < 0 || cin.fail()) {
        cin.clear();
        cin >> ws;
        cout << Message;
        cin >> number;
    }
}


bool Continue_Prosses(string Message) {
    char IS;
    cout << Message;
    cin >> IS;
    if (IS == 'Y' || IS == 'y') return true;
    else return false;
}

string rowSpace(int col1_size = 15, int main_size = 45, int col2_size = 15, char CharTyp = '=') {
    string Space = "|";
    for (int i = 0; i < col1_size; i++) {
        Space += CharTyp;
    }
    Space += "|";
    for (int i = 0; i < main_size; i++) {
        Space += CharTyp;
    }
    Space += "|";
    for (int i = 0; i < col2_size; i++) {
        Space += CharTyp;
    }
    Space += "|";
    Space += "\n";

    return Space;
}

string Add_title_Row(stTable Table) {
    string title = "";
    string C1_row = "";
    string LargC_row = "";
    string C2_row = "";
    if (Table.Left_or_Right == 'L' || Table.Left_or_Right == 'l') {
        C1_row += Table.Colone_1_title;
        C2_row += Table.Colone_3_title;
        LargC_row += Table.Colone_2_title;
        for (int i = 0; i < Table.Colone_1_width - Table.Colone_1_title.length(); i++) {
            C1_row += " ";
        }
        for (int i = 0; i < Table.Colone_2_width - Table.Colone_2_title.length(); i++) {
            LargC_row += " ";
        }
        for (int i = 0; i < Table.Colone_3_width - Table.Colone_3_title.length(); i++) {
            C2_row += " ";
        }
    }
    else {
        for (int i = 0; i < Table.Colone_1_width - Table.Colone_1_title.length(); i++) {
            C1_row += " ";
        }
        for (int i = 0; i < Table.Colone_2_width - Table.Colone_2_title.length(); i++) {
            LargC_row += " ";
        }
        for (int i = 0; i < Table.Colone_3_width - Table.Colone_3_title.length(); i++) {
            C2_row += " ";
        }

        C1_row += Table.Colone_1_title;
        C2_row += Table.Colone_3_title;
        LargC_row += Table.Colone_2_title;
    }

    title = "|" + C1_row + "|" + LargC_row + "|" + C2_row + "|" + "\n";
    return title;
}

string table_Head(stTable Table) {
    string Space = rowSpace(Table.Colone_1_width, Table.Colone_2_width, Table.Colone_3_width, Table.Space_char);

    readInput(Table.Colon_1_string, "[Colone 1 Title] {length must be < " + to_string(Table.Colone_1_width) + "}\n= > ");
    readInput(Table.Colone_2_String, "[Colone 2 Title] {length must be < " + to_string(Table.Colone_2_width) + "}\n = > ");
    readInput(Table.Colone_3_string, "[Colone 3 Title] {length must be < " + to_string(Table.Colone_3_width) + "}\n = > ");

    string head = Add_title_Row(Table);
    string _table_head = Space + head + Space;
    cout << "~~ Table Head ~~" << endl;
    cout << _table_head;
    cout << "~~            ~~" << endl;
    return _table_head;
}

string AddRow(stTable Table) {
    string Row = "";
    string C1_row = "";
    string LargC_row = "";
    string C2_row = "";
    if (Table.Left_or_Right == 'L' || Table.Left_or_Right == 'l') {
        C1_row += Table.Colon_1_string;
        C2_row += Table.Colone_3_string;
        LargC_row += Table.Colone_2_String;
        for (int i = 0; i < Table.Colone_1_width - Table.Colon_1_string.length(); i++) {
            C1_row += " ";
        }
        for (int i = 0; i < Table.Colone_2_width - Table.Colone_2_String.length(); i++) {
            LargC_row += " ";
        }
        for (int i = 0; i < Table.Colone_3_width - Table.Colone_3_string.length(); i++) {
            C2_row += " ";
        }
    }
    else {
        for (int i = 0; i < Table.Colone_1_width - Table.Colon_1_string.length(); i++) {
            C1_row += " ";
        }
        for (int i = 0; i < Table.Colone_2_width - Table.Colone_2_String.length(); i++) {
            LargC_row += " ";
        }
        for (int i = 0; i < Table.Colone_3_width - Table.Colone_3_string.length(); i++) {
            C2_row += " ";
        }

        C1_row += Table.Colon_1_string;
        C2_row += Table.Colone_3_string;
        LargC_row += Table.Colone_2_String;
    }

    Row = "|" + C1_row + "|" + LargC_row + "|" + C2_row + "|" + "\n";
    return Row;
}

string Table_Body(stTable Table) {
    string TableBody = "";
    string Space = rowSpace(Table.Colone_1_width, Table.Colone_2_width, Table.Colone_3_width, Table.Space_char);
    int Colon_index = 0;

    do {
        Colon_index++;
        readInput(Table.Colon_1_string, "[Colone 1 Text] {length must be < " + to_string(Table.Colone_1_width) + "}\n= > ");
        readInput(Table.Colone_2_String, "[Colone 2 Text] {length must be < " + to_string(Table.Colone_2_width) + "}\n = > ");
        readInput(Table.Colone_3_string, "[Colone 3 Text] {length must be < " + to_string(Table.Colone_3_width) + "}\n = > ");

        TableBody += AddRow(Table);
        TableBody += Space;
    } while (Continue_Prosses("Add Column? [Y/N]: "));

    return TableBody;
}

stTable TableSettingsEditor() {
    static stTable Table;
    int user_choice;

    do {
        cout << "===============================" << endl;
        cout << "[1] ~ Colone 1 Size: \"" << Table.Colone_1_width << "\"]" << endl;
        cout << "[2] ~ Colone 2 Size: \"" << Table.Colone_2_width << "\"]" << endl;
        cout << "[3] ~ Colone 3 Size: \"" << Table.Colone_3_width << "\"]" << endl;
        cout << "===============================" << endl;

        ReadPositifNumber(user_choice, "Enter setting index to edit: ");
        switch (user_choice) {
            case 1:
                cout << "~~Edit Colone 1~~" << endl;
                cout << "[current is: " << Table.Colone_1_width << "]" << endl;
                ReadPositifNumber(Table.Colone_1_width, "Enter new Parameter: ");
                break;
            case 2:
                cout << "~~Edit Colone 2~~" << endl;
                cout << "[current is: " << Table.Colone_2_width << "]" << endl;
                ReadPositifNumber(Table.Colone_2_width, "Enter new Parameter: ");
                break;
            case 3:
                cout << "~~Edit Colone 3~~" << endl;
                cout << "[current is: " << Table.Colone_3_width << "]" << endl;
                ReadPositifNumber(Table.Colone_3_width, "Enter new Parameter: ");
                break;
            default:
                cout << "Undefined Command!!!!...." << endl;
                break;
        }
    } while (Continue_Prosses("Save Changes? [Y/N]: ") && Continue_Prosses("Edit anything else? [Y/N]: "));

    return Table;
}

string Export_string_table(string Table_Body, string table_Head)
{
    return table_Head + Table_Body;
}

void ExportToFile(string Table)
{
    string format;
    string path = "";
    string FileName;
    cout << "~ Enter The File Name => (no Spaces!!)" << endl;
    cout << "=> ";
    cin >> FileName;
    cout << "enter The File format : [.txt .pdf .{customized}]" << endl;
    cout << "=> ";
    cin >> format;
    path += FileName + "." + format; 
    fstream Myfile;
    Myfile.open(path, ios::out);
    if (Myfile.is_open())
    {
        Myfile << Table << endl;
        Myfile << "Exported at : " << getTime() << endl;
        Myfile.close();
    }
}
void Gethelp();
void FunctionsManger(int userCh) {
    static stTable tableset;
    string TableStr;
    switch (userCh) {
        case 1:
            tableset = TableSettingsEditor();
            break;
        case 2:
            TableStr = Export_string_table(Table_Body(tableset), table_Head(tableset));
            cout << TableStr << endl;
            cout << "Do you want to Export The Table to a file ? " << endl;
            cout << "[yes = 1 / No = 0]=> ";
            int userCh;
            cin >> userCh;
            if (userCh)
            {
                ExportToFile(TableStr);
            }
            
            break;
        case 3:
            Gethelp();
            break;
        case 4:
            // When you finish the table creator function use it to create a default table
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
}

void main_menu() {
    cout << "=================" << endl;
    cout << "= Table-Formatting =" << endl;
    cout << "=================" << endl;
    cout << "\n";
    cout << "Welcome To Table Formatting app created using C++" << endl;
    cout << "~ Type [1]: to edit table settings" << endl;
    cout << "~ Type [2]: to create the table" << endl;
    cout << "~ Type [3]: to get help" << endl;
    cout << "~ Type [4]: to see example Default table" << endl;

    int user_choice;
    ReadPositifNumber(user_choice, "=> ");
    FunctionsManger(user_choice);
    main_menu();
}

void FileContentPrinter(string path)
{
    fstream Myfile;
    Myfile.open(path, ios::in);
    if (Myfile.is_open())
    {
        string Line;
        while (getline(Myfile, Line))
        {
            cout << Line << endl;
        }
        Myfile.close();
    }
}

void Gethelp() {
    string HelpFilePath = ".Help";
    FileContentPrinter(HelpFilePath);
}

int main() {
    main_menu();
    int close;
    cin >> close;
    return 0;
}
