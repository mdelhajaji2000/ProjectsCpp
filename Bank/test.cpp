#include <iostream>
#include <vector>

#include "ClientsGeter.h"

using namespace std;

int main()
{
    clsDataFromFile GetData;
    cout << GetData.GitData().Account_number << endl;

    return 0;
}
