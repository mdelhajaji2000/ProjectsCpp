#include <iostream>
#include <random>
using namespace std;

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
#define YELLOW  "\033[33m"

int random_generator(int x = 1, int y = 3)
{
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> distribution(x, y);
    return distribution(gen);
}

void result(int user_choice, int computer_choice = random_generator())
{
    string choice[] = {"rock", "paper", "scissors"};
    cout << GREEN << "your choice : " << choice[user_choice - 1] << "\n" << RESET;
    cout <<  RED << "computer choice : " << choice[computer_choice - 1] << endl;
    cout << RESET << endl;
    cout << YELLOW;
   if (user_choice == 1 && computer_choice == 2)
    {
        cout << "computer win" << endl;
    }
    else if (user_choice == 1 && computer_choice == 3)
    {
        cout << "you win..!" << endl;
    }
    else if (user_choice == 2 && computer_choice == 1)
    {
        cout << "you win " << endl;
    }
    else if (user_choice == 2 && computer_choice == 3)
    {
        cout << "computer win" << endl;
    }
    else if (user_choice == 3 && computer_choice == 1)
    {
        cout << "computer win" << endl;
    }
    else if (user_choice == 3 && computer_choice == 2)
    {
        cout << "you win" << endl;
    } 
    else if (user_choice == computer_choice)
    {
        cout << "draw" << endl;
    } 
    cout << RESET << endl;
}

int main()
{
    int user_choice;
    int computer_choice = random_generator();
    cout << "=======Rock, Paper, Scissors=======" << endl;
    cout << "type : [1] : to choice rock \n"
         << "type : [2] : to choice paper\n" 
         << "type : [3] : to choice scissors" << endl;
         cin >> user_choice;
    
    if (user_choice > 0 && user_choice < 4)
    {
        result(user_choice);
        main();
    }
    return 0;
}