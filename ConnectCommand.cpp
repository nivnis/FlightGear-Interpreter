//
// Created by yuvallevy on 20/12/2019.
//

#include "ConnectCommand.h"
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
    int port;
    Interpreter interpreter;
    try{
        port = (int) interpreter.interpret(arr[index][2])->calculate();
    }catch(char* err) {
        port = 5402;
    } catch(exception* ex){
        port = 5402;
    }
    //make a new client
    Client* client = new Client(ip, port);
    //create a thread that will keep sending data from our maps to the simulator
    client->runClientThread();
    return 1;
}

//    ConnectCommand:: ~ConnectCommand(){
//
//    }