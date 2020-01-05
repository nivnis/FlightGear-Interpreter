//
// Created by pikachu on 12/23/19.
//
#pragma once
#ifndef PORJECT1_CLIENT_H
#define PORJECT1_CLIENT_H
#pragma once
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <unordered_map>

using namespace std;

#define PORT 5402

class Client {
private:
    int port;
    string ip;
    int client_socket;

public:
    Client(string ipn, int portNumber);
    void runClientThread();
    void runClient();
};


#endif //PORJECT1_CLIENT_H
