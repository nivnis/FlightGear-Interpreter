//
// Created by yuvallevy on 22/12/2019.
//
#include "SymbolTable.h"
#include <iostream>
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

SymbolTable *SymbolTable::getInstance() {
    if (instance == 0) {
        instance = new SymbolTable();
    }
    return instance;
}

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

string SymbolTable::makeClientCommand(Var *var) {
    string commandString = "set ";
    commandString.append(var->getSim() + " " + to_string(var->getVal()) + " \r\n");
    return commandString;
}

void SymbolTable::setVarBySim(const string &sim, double value) {
    simMapMutex.lock();
    if (this->sim_map.find(sim) != this->sim_map.cend()){
        this->sim_map.find(sim)->second->setVal(value);
    }
    simMapMutex.unlock();
}

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

unordered_map<string, Var *> SymbolTable::get_variables_map(){
    return this->variables_map;
}
unordered_map<string, Var *> SymbolTable::get_sim_map(){
    return this->sim_map;
}
unordered_map<string, Command *> SymbolTable::get_command_map(){
    return this->command_map;
}

queue<string> * SymbolTable::getClientCommands() {
    return &this->clientCommands;
}
