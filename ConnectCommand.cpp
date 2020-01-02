//
// Created by yuvallevy on 20/12/2019.
//

#include "ConnectCommand.h"
#include <iostream>
#include <string>
#include <vector>


ConnectCommand:: ConnectCommand() : Command() {

}

int ConnectCommand:: execute(vector<vector<string>> arr, int index){
    string ip = arr[index][1];
    int port = stoi(arr[index][2]);
    Client* client = new Client(ip, port);
    client->runClientThread();
    return 1;
}

//    ConnectCommand:: ~ConnectCommand(){
//
//    }