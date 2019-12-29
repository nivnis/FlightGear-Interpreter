//
// Created by pikachu on 12/23/19.
//

#ifndef PORJECT1_CLIENT_H
#define PORJECT1_CLIENT_H
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 5402

class Client {
private:
    int port;

public:
    Client(int portNumber);
};


#endif //PORJECT1_CLIENT_H
