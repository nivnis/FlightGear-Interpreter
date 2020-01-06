//
// Created by yuvallevy on 20/12/2019.
//

#include "ConnectCommand.h"
#include <iostream>
#include <string>
#include <vector>

//a command that opens a new client
ConnectCommand:: ConnectCommand() : Command() {

}
//opens a client
int ConnectCommand:: execute(vector<vector<string>> arr, int index){
    //extracts the ip
    string ip = arr[index][1];
    //extracts the port
    int port = stoi(arr[index][2]);
    //make a new client
    Client* client = new Client(ip, port);
    //create a thread that will keep sending data from our maps to the simulator
    client->runClientThread();
    return 1;
}

//    ConnectCommand:: ~ConnectCommand(){
//
//    }