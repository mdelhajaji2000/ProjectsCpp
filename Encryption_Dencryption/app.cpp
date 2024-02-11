#include <iostream>
#include <limits>
#include <string>
using namespace std;

void ReadPositifNumber(int &num, string Message)
{
    cout << Message;
    cin >> num;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << Message;
        cin >> num;
    }
    
}

void ReadString(string &text, string Message)
{
    cout << Message;
    cin >> ws;
    getline(cin, text);
}

string Encryption(string text, int Encryptionkey)
{
    for (int i = 0; i < text.length(); i++)
    {
        text.at(i) +=  Encryptionkey;
    }
    return text;
}

string Dencryption(string text, int Deencryptionkey)
{
    for (int i = 0; i < text.length(); i++)
    {
        text.at(i) -= Deencryptionkey;
    }
    return text;
}

int main()
{
    int user_choice;
    int Encryptionkey;
    string txt;
    cout << "~~ En De-En app ~~" << endl;
    cout << "Type : [1] : To Encrypt a text" << endl;
    cout << "Type : [2] : To De_encrypte a text" << endl;

    ReadPositifNumber(user_choice, "=> ");

    switch (user_choice)
    {
    case 1:
        ReadPositifNumber(Encryptionkey, "enter En key = > ");
        cout << "~~ Encryption Key [" << Encryptionkey << "]" << endl;
        ReadString(txt, "enter The txt = > ");
        cout << "Text after encryption : " << Encryption(txt, Encryptionkey) << endl;
        break;
    case 2:
        ReadPositifNumber(Encryptionkey, "enter En key = > ");
        cout << "~~ De encryption Key : [" << Encryptionkey << "]" << endl;
        ReadString(txt, "enter your text = > ");
        cout << "original text is : " << Dencryption(txt, Encryptionkey) << endl;
        break;
    default:
        cout << "unvalid commands.....!" << endl;
        break;
    }

    // to see the final step and not colse if you use .exe fil (;
    int assdew;
    cout << "enter anything to close...!" << endl;
    cin >> assdew;


    return 0;
}