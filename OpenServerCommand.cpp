//
// Created by yuvallevy on 20/12/2019.
//
#include "OpenServerCommand.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

OpenServerCommand:: OpenServerCommand() : Command() {

}

int OpenServerCommand:: execute(vector<vector<string>> arr, int index){
    int port = stoi(arr[index][1]);
    Server* server = new Server(port);
    server->runServerThread();
    return 1;
}
//    OpenServerCommand:: ~OpenServerCommand(){
//
//    }
