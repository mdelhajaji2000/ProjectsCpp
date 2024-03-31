#include <iostream>
#include "encryption.h"
using namespace std;



int main()
{
    string str = "Admin#//#1234#//#-1";
    clsEncryption enc;
    for(int i = 0; i < str.size(); i++)
    {
        str[i] += 23;
    }
    cout << str << endl;
    return 0;
}