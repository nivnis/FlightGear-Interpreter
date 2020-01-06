//
// Created by yuvallevy on 22/12/2019.
//
#include "SymbolTable.h"
#include <string>
#include <unordered_map>
#include "Var.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"

using namespace std;

// Private constructor so that no objects can be created.
/* Null, because instance will be initialized on demand. */
SymbolTable *SymbolTable::instance = 0;

SymbolTable::SymbolTable() {
    OpenServerCommand* openData = new OpenServerCommand();
    ConnectCommand* connectCommand = new ConnectCommand();
    Command* Var = new DefineVarCommand();
    Command* sleep = new SleepCommand();
    Command* print = new PrintCommand();
    Command* whilee = new WhileCommand();
    Command* iff = new IfCommand();
    command_map["openDataServer"] = openData;
    command_map["connectControlClient"] = connectCommand;
    command_map["var"] = Var;
    command_map["Sleep"] = sleep;
    command_map["Print"] = print;
    command_map["while"] = whilee;
    command_map["if"] = iff;
}

// get the instance of the symboltable - singelton.
SymbolTable *SymbolTable::getInstance() {
    if (instance == 0) {
        instance = new SymbolTable();
    }
    return instance;
}
// func that getting the var members and creates a new Var
void SymbolTable::addVar(string name, string sim, string direction, double value) {
    SymbolTable* symbolTable = symbolTable->getInstance();
    //adding new var with or without sim
        Var* var = new Var(name,direction,sim,value);
        simMapMutex.lock();
        symbolTable->sim_map[sim] = var;
        simMapMutex.unlock();
        varMapMutex.lock();
        symbolTable->variables_map[name] = var;
        varMapMutex.unlock();
}
// func that gets a new value for a Var and sets it using name of the Var
void SymbolTable::setVarByName(const string &name, double value) {
    varMapMutex.lock();
    if (this->variables_map.find(name) != this->variables_map.cend()){
        this->variables_map.find(name)->second->setVal(value);
        if (this->variables_map.find(name)->second->getDirection()=="->"){
            clientCommands.push(makeClientCommand(this->variables_map.find(name)->second));
        }
    }
    varMapMutex.unlock();
}
// func that create the "Set" command for the client.
string SymbolTable::makeClientCommand(Var *var) {
    string commandString = "set ";
    commandString.append(var->getSim() + " " + to_string(var->getVal()) + "\r\n");
    return commandString;
}
// func that gets a new value for a Var and sets it using name of the sim
void SymbolTable::setVarBySim(const string &sim, double value) {
    simMapMutex.lock();
    if (this->sim_map.find(sim) != this->sim_map.cend()){
        this->sim_map.find(sim)->second->setVal(value);
    }
    simMapMutex.unlock();
}
// func that get a string which is the name of the var or the sim and go over the maps and return the Var.
Var SymbolTable::getVar(string name){
    simMapMutex.lock();
    unordered_map<string, Var *>::const_iterator got1 = variables_map.find (name);
    if ( got1 != variables_map.end() ) {
        simMapMutex.unlock();
        return *got1->second;
    }
    simMapMutex.unlock();
    return NULL;
}
// func that get a string which is the the sim and go over the map and return the Var.

Var SymbolTable::getVarBySim(const string &sim) {
    simMapMutex.lock();
    unordered_map<string, Var*>::const_iterator got2 = sim_map.find (sim);
    if ( got2 != sim_map.end() ) {
        simMapMutex.unlock();
        return *got2->second;
    }
    simMapMutex.unlock();
    return NULL;
}
// return the var map from name to Var*.
unordered_map<string, Var *> SymbolTable::get_variables_map(){
    return this->variables_map;
}
// return the var map from sim to Var*.
unordered_map<string, Var *> SymbolTable::get_sim_map(){
    return this->sim_map;
}
// return the clientCommands map.

queue<string> * SymbolTable::getClientCommands() {
    return &this->clientCommands;
}
