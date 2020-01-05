//
// Created by yuvallevy on 22/12/2019.
//

#ifndef UNTITLED_SYMBOLTABLE_H
#define UNTITLED_SYMBOLTABLE_H

#endif //UNTITLED_SYMBOLTABLE_H
#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdio>
#include <queue>
#include "Var.h"
#include "DefineVarCommand.h"
#include "SleepCommand.h"
#include "WhileCommand.h"
#include "PrintCommand.h"
#include "IfCommand.h"
#include <mutex>

using namespace std;
class SymbolTable {
private:
    /* Here will be the instance stored. */
    static SymbolTable *instance;
    unordered_map<string, Var *> variables_map; // name, Var*
    unordered_map<string, Var *> sim_map; // sim, Var*
    unordered_map<string,Command*> command_map;
    mutex simMapMutex, varMapMutex;
    queue<string> clientCommands;

// Private constructor so that no objects can be created.
    SymbolTable();

public:
    /* Static access method. */
    static SymbolTable *getInstance();

    void addVar(string name, string sim, string direction, double value);
    Var getVar(string name);
    Var getVarBySim(const string &sim);
    void setVarByName(const string &name, double value);
    void setVarBySim(const string &sim, double value);

    unordered_map<string, Var *> get_variables_map();
    unordered_map<string, Var *> get_sim_map();
    queue<string> * getClientCommands();


private:
    static string makeClientCommand(Var* var);

};

