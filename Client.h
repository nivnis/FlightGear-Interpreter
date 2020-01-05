//
// Created by pikachu on 12/23/19.
//
#pragma once
#ifndef PORJECT1_CLIENT_H
#define PORJECT1_CLIENT_H
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
class Client {
private:
    //members
    int port;
    string ip;
    int client_socket;

public:
    //client constructor by ip and port
    Client(string ipn, int portNumber);
    //makes a new thread that will run on the runClient function
    void runClientThread();
    //takes a queue of commands from the SymbolTable class and sends the commands to the simulator
    void runClient();
};


#endif //PORJECT1_CLIENT_H
