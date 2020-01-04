//
// Created by pikachu on 1/3/20.
//

#include "Parser.h"

using namespace std;


Parser::Parser() {
    OpenServerCommand *openData = new OpenServerCommand();
    ConnectCommand *connectCommand = new ConnectCommand();
    DefineVarCommand *Var = new DefineVarCommand();
    SleepCommand *sleep = new SleepCommand();
    PrintCommand *print = new PrintCommand();
    WhileCommand *whilee = new WhileCommand();
    IfCommand *iff = new IfCommand();
    this->command_map["openDataServer"] = openData;
    this->command_map["connectControlClient"] = connectCommand;
    this->command_map["Setvar"] = Var;
    this->command_map["var"] = Var;
    this->command_map["Sleep"] = sleep;
    this->command_map["Print"] = print;
    this->command_map["while"] = whilee;
    this->command_map["if"] = iff;
}


void Parser::parse(vector<vector<string>> arr) {
    int index = 0;
    while (index < arr.size()) {
        Command* c = command_map.find(arr[index][0])->second;
        index += c->execute(arr, index);
    }
    //cout<<"doneeee"<<endl;
}
