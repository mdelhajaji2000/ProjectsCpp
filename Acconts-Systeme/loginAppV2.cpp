#include <iostream>    /*--Console application--*/
#include <vector>      /*--VERSION : 2.0.1-BETA--*/
#include <algorithm>   /*--Made By : [insta : mdelhajaji2000]--*/
using namespace std;   /*--this app is not secure by any librarie*/

int Iindex = 0;
int main(); // Problemes will be fixed in next version {V3 Soon...!}
struct users
{
    string user_name;
    string password;
    int age;
    string frist_name;
    string second_name;

    
    string Country;
    string City;
    bool IsMarried;
    char gender;
    int index;//only for dev;
    bool Isfacke;
};
vector<users> USERS;


void CreatAcc()
{

    string un;
    string pwd;
    //
    int input_age;
    string input_frist_name;
    string input_second_name;
    string input_Country;
    string input_City;
    bool input_IsMarried;
    char input_gender;
    //
    cout << "creat a user name : ";
    cin >> un;//user name
    for (int j = 0; j < USERS.size(); j++)
    {
        if (un == USERS.at(j).user_name)
        {
            cout << "invalid user name (user_exist..!)" << endl;
            main();
        }
    }
    
    cout << "creat a password : ";
    cin >> pwd;//password
    cout << "enter your age : ";
    cin >> input_age;
    cout << "enter your full name : ";
    cin >> input_frist_name >> input_second_name;
    cout << "enter your country : ";
    cin >> input_Country;
    cout << "enter your city : ";
    cin >> input_City;
    cout << "Are you Married [1] or [0] : ";
    cin >> input_IsMarried;
    cout << "enter your gender [M/m] or [F/f] : ";
    cin >> input_gender;
    USERS.push_back({un, pwd, input_age,
                    input_frist_name,
                    input_second_name, 
                    input_Country, 
                    input_City, input_IsMarried, 
                    input_gender, Iindex, false});
                    Iindex++;
    bool save;
    cout << "do you want to save ? [1] or [0] : ";
    cin >> save;
    if (save)
    {
        return;
    }
    else (CreatAcc());
    
}
void accont(int AcontIndex, int i);
void SignIn()
{
    string un, pwd;
    cout << "enter the user name : ";
    cin >> un;
    cout << "enter the password : ";
    cin >> pwd;
    bool IsFind;
    for (int i = 0; i < USERS.size(); i++)
    {
        if (un == USERS.at(i).user_name && pwd == USERS.at(i).password)
        {
            int j = 0;
            accont(i, j);
            IsFind = true;
            break;
        }
        else (IsFind = false);
    }
    if (IsFind == false)
    {
        cout << "user or password are incorrect.......!" << endl;
        main();
    }
    
    SignIn();
    
}
// void delet_User(int index);
void modify(int index);
void log_in(int index);
void log_in_display_info(int index_acc)
{
    cout << "*******************************" << endl;
    cout << "accont index : " << USERS.at(index_acc).index << endl;
    cout << "accont user name : " << USERS.at(index_acc).user_name << endl;
    cout << "accont password : " << USERS.at(index_acc).password << endl;
    cout << "*******************************" << endl;
    

}
/// @brief 
/// @param AccontIndex 
void display_info(int AccontIndex)
{
    cout << "**************************************" << endl;
    cout << "Frist Name : " << USERS.at(AccontIndex).frist_name << endl;
    cout << "Second Name : " << USERS.at(AccontIndex).second_name << endl;
    cout << "Age : " << USERS.at(AccontIndex).age << endl;
    cout << "Country : " << USERS.at(AccontIndex).Country << endl;
    cout << "City : " << USERS.at(AccontIndex).City << endl;
    cout << "Married : " << USERS.at(AccontIndex).IsMarried << endl;
    cout << "Gender : " << USERS.at(AccontIndex).gender << endl;
    cout << "**************************************" << endl;
}
void delet_User(int AcontIndex);
void accont(int AcontIndex, int i)
{
    string pwd; // for user Access to log in settings
    if (i == 0)
    {
        cout << "Welcome " << USERS.at(AcontIndex).user_name << endl;
    }
    i++;
    int choice;
    cout << "type : [1] : to see your engestred info " << endl;
    cout << "type : [2] : to edit your info" << endl;
    cout << "type : [ choice : [3] : \"delet\" will be avaible soon ] " << endl;
    cout << "type : [4] : to return to main" << endl;
    cout << "type : [5] : to edit logIn settings" << endl;
    cin >> choice;
    switch (choice)
    {
        case 1 :
                display_info(AcontIndex);
            break;
        case 2 :
                 modify(AcontIndex);
            break;
        case 3 :
            cout << "delet option will be availble soon..." << endl;
            cout << "are you sure for this decision.....! [1/0] = > ";
            bool decision;
            cin >> decision;
            if (decision)
            {
                delet_User(AcontIndex);
                return;
            }
             break;
        case 4 :
            main(); // to return to the main (if you used return you return to the sign in ...!)
            break;
        case 5 :
        
            cout << "frist enter the actual password = >";
            cin >> pwd;
            if (pwd == USERS.at(AcontIndex).password)
            {
                log_in(AcontIndex);
            }
            else {
                cout << "unvalid password...!";
            }
            break;
        default :
            cout << "unvalid command input...!" << endl;
            break;
            

}
    accont(AcontIndex, i);
    }
        

void dev();

int main()
{
    int choice;
    cout << "Welcome to login app (;" << endl;
    cout << "type : [1] : to sign in \n" << "type : [2] : to creat new acc" << "\ntype : [3] : to close and delete all" << endl;
    cin >> choice;
    switch (choice)
    {
        case 1 :
            if (!USERS.empty())
            {
            SignIn();
            }
            else
            {
                cout << "there is no acconts alerdy...!" << endl;
            }
            break;
        case 2 :
            CreatAcc();
            break;
        case 3 :
            return 0;
            break;
        case 1990 : //dev code
            dev();
            break; // ONly for devlopper
        default :
            cout << "invlid choice (1/2) app frocement close.!" << endl;
            break;
    }

    main();
    return 0;
}

void modify(int index)
{
    int ModifyChoice;
    cout << "what do you want to modify : " << endl;
    cout << "type [] to modify : \n"
         << "[1] : Frist Name\n"
         << "[2] : Second name\n"
         << "[3] : age\n"
         << "[4] : Country\n"
         << "[5] : City\n"
         << "[6] : Married Satatu\n"
         << "[7] : Gender" << endl;
         cout << "==> ";
         cin >> ModifyChoice;
    switch (ModifyChoice)
    {
        case 1 :
            cout << "enter new Frist Name : ";
            cin >> USERS.at(index).frist_name;
            break;
        case 2 : 
            cout << "enter new Second name : ";
            cin >> USERS.at(index).second_name;
            break;
        case 3 :
            cout << "enter new age : ";
            cin >> USERS.at(index).age;
            break;
        case 4 :
            cout << "enter new Country : ";
            cin >> USERS.at(index).Country;
            break;
        case 5 :
            cout << "enter new City : ";
            cin >> USERS.at(index).City;
            break;
        case 6 : 
            cout << "enter new Marriage staue : ";
            cin >> USERS.at(index).IsMarried;
            break;
        case 7 :  
            cout << "modify the gender : ";
            cin >> USERS.at(index).gender;
            break;
    }
    bool choise;
    cout << "modify anything else ? : [0/1] : = > ";
    cin >> choise;
    if (choise)
    {
        modify(index);
    }
    return;
     
}   

void log_in(int index)
{
    int choice;
    string NewPassword, NewUser;
    cout << "what do you want to edit : \n";
    cout << "[1] : user name [actuel : " << USERS.at(index).user_name << "]"; 
    cout << "\n[2] : password[actuel : " << USERS.at(index).password << "]\n";
    cin >> choice;
    switch (choice)
    {
    case 1 :
        cout << "enter the new password : = > ";
        cin >> NewUser;
        for (int j = 0; j < USERS.size(); j++)
    {
        if (NewUser == USERS.at(j).user_name)
        {
            cout << "invalid user name (user_exist..!)" << endl;
            log_in(index);
        }
    }
    USERS.at(index).user_name = NewUser;
        break;
    case 2 :
        cout << "enter the new passwrod : = > ";
        cin >> NewPassword;
        USERS.at(index).password = NewPassword;
    default:
        break;
    }
    bool IsMore;
    cout << "do you want to edit anything else ? ";
    cin >> IsMore;
    if (IsMore)
    {
        log_in(index);
    }
}

void facke_accont_creator();

void dev()
{
    cout << "you are now in admin function : " << endl;
    cout << "[1] : general info " << endl;
    cout << "[2] : to log in a user_accont" << endl;
    cout << "[3] : to see all acconts" << endl;
    cout << "[4] : return to main menu" << endl;
    cout << "[5] : to add facke acconts" << endl; //for testing raisons
    cout << "== > ";
    int choice_dev;
    int facke_aconts = 0;
    int choice_case_2;
    cin >> choice_dev;
    int index;
    string user;
    int male = 0, female = 0;
    switch (choice_dev)
    {
    case 1 :
        cout << "there is : " << USERS.size() << " user" << " [" << facke_aconts << "] are facke!" << endl;
        for (int i = 0; i < USERS.size(); i++)
        {
            if (USERS.at(i).gender == 'm' || USERS.at(i).gender == 'M')
            {
                male++;
            }
            if (USERS.at(i).gender == 'f' || USERS.at(i).gender == 'F')
            {
                female++;
            }
            if (USERS.at(i).Isfacke)
            {
                facke_aconts++;
            }
        }
        cout << "there is : " << male << " user male and " << female << " female" << endl;

        break;
    case 2 : 
        cout << "login using : \n" << "[1] : user name\n" << "[2] : accont index\n";
        cout << "= > ";
        cin >> choice_case_2;
        switch (choice_case_2)
        {
        case 1:
            cout << "enter user name : ";
            cin >> user;
            for (int i = 0; i < USERS.size(); i++)
            {
                if (user == USERS.at(i).user_name)
                {
                    accont(i,0);
                }
                else
                {
                    cout << "error : [404] :  user not found...!" << endl;
                }
                
            }
            
            
            ;
            break;
        case 2 : 
            cout << "enter the index : ";
            cin >> index;
            accont(index, 0);
            break;
        default:
            break;
        }
        case 3 :
            cout << "there are the : " << USERS.size() << " user accont : " << endl;
            for (int i = 0; i < USERS.size(); i++)
            {
                log_in_display_info(i);
            }
            
            break;
        case 4 : 
            main();
        break;
        case 5 :
            facke_accont_creator();
    default:
    cout << "unvalid choice...!" << endl;
        break;
    }
    dev();
}


void delet_User(int Acontindex)
{
    USERS.erase(USERS.begin() + Acontindex);
    Iindex--;
    for (int i = 0; i < USERS.size(); i++)
    {
        if (USERS.at(i).index > Acontindex)
        {
            USERS.at(i).index--;
        }
    }
    
    main();
}

void facke_accont_creator()
{
    int acc_number;
    string user = "kk";
    cout << "how many acconts do you want to add ? " << endl;
    cin >> acc_number;
    for (int i = 0; i < acc_number; i++)
    {
        user += "w";
        USERS.push_back({user,"test",0,"k","j","k","j",0,'h',Iindex,true});
        Iindex++;
    }

    main();
} //finished after 3 days of worcking [end the (10/12/2023 05:14 AM)]