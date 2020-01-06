//
// Created by yuvallevy on 20/12/2019.
//
#include "OpenServerCommand.h"
#include <vector>
#include <string>
using namespace std;
//a command that opens a server
OpenServerCommand:: OpenServerCommand() : Command() {

}
//opens a server
int OpenServerCommand:: execute(vector<vector<string>> arr, int index){
    //extract the port
    int port;
    Interpreter interpreter;
    try{
        port = (int) interpreter.interpret(arr[index][1])->calculate();
    }catch(char* err) {
        port = 5400;
    } catch(exception* ex){
        port = 5400;
    }
    //create a new server
    Server* server = new Server(port);
    //create a thread that will keep getting data from server and update our variables
    server->runServerThread();
    return 1;
}
//    OpenServerCommand:: ~OpenServerCommand(){
//
//    }
