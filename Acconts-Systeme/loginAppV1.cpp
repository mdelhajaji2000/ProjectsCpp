#include <iostream>
#include <vector>
using namespace std;
//global variabels
    //login info:
        vector<string> users;
        vector<string> passwords;
    //----------------
    //users info
        vector<int> age;
        vector<string> fristname;
        vector<string> secondName;
        vector<string> countrie;
    //-----------------
//---------------------------- x

void CreatNewAcc()
{
    string userName;
    string password;
    cout << "add user name (!!no espaces!!): ";
    cin >> userName;  
    for (int i = 0; i < users.size(); i++)
    {
        if (userName == users.at(i))
    {
        cout << "We found an account with the same name or pasword..!" << endl;
        CreatNewAcc();
    }
    }
    
    
     
    users.push_back(userName);
    cout << "creat password : ";
    cin >> password;
    passwords.push_back(password);

    cout << "now enter your informations : " << endl;
    cout << "enter your frist name => ";
    string fname, sname;
    cin >> fname;
    fristname.push_back(fname); 
    cout << " your second name => " ;
    cin >> sname;
    secondName.push_back(sname);
    cout << "enter your age => ";
    int Aage;
    cin >> Aage;
    age.push_back(Aage);
    string countriee;
    cout << "enter your countrie => ";
    cin >> countriee;
    countrie.push_back(countriee);

}
void acc(int acc);
void SingIn()
{
    string user;
    string pwd;
    cout << "user name => ";
    cin >> user;
    cout << "password => ";
    cin >> pwd;
    bool Is = false;
    for (int i = 0; i < users.size(); i++)
    {
        if (user == users.at(i) && pwd == passwords.at(i))
        {
            acc(i);
            Is = false;
            break;
        }
        else(Is = true);
            
    }
    if (Is)
    {
        cout << "user or password are incorrect....!" << endl;
    }
    
    
    
}

void acc(int accIndex)
{
    cout << "welcome " << users.at(accIndex) << endl;
    cout << "there is your information : \n";
    cout << "frist name : " << fristname.at(accIndex) << "\n"
         << "second name : " << secondName.at(accIndex) << "\n"
         << "your age is : " << age.at(accIndex) << "\n"
         << "countries : " << countrie.at(accIndex) << endl; 
    
}

void dev();

int main()
{
    cout << "-----loginApp-----" << endl;
    int choice;

    cout << "welcome to loginApp:\n"
         << "what dpo you want ? :\n"
         << "type : [1] to create new accont \n"
         << "type : [2] to sign in" << endl;
    cout << "=> ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            CreatNewAcc();
            break;
        case 2:
            SingIn();
            break;
        case 3://for devlopper only
            dev();
        default:

            break;
    }
    main();
    return 0;
}

void dev()
{
    int command_number;
    cout << "command numbr => ";
    cin >> command_number;
    switch (command_number)
    {
    case 1:
        cout << "users : " << users.size() << " passwords : " << passwords.size() << endl;  
        break;
    case 2:
        for (int i = 0; i < users.size(); i++)
        {
            cout << "user name : " << users.at(i) << " : password : " << passwords.at(i) << endl;
        }
        break;
    default:
    cout << "undefined command num" << endl;
        break;
    }
}
