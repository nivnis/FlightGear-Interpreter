#include "Server.h"
#include "Client.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello, World!";
    //Server s(5400);
    Client c(5402);
    return 0;
}