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

// Private constructor so that no objects can be created.
    SymbolTable();

public:
    /* Static access method. */
    static SymbolTable *getInstance();

    void addVar(string name1, string sim1, string direction, double value1, bool answer);
    Var* getVar(string name);
    unordered_map<string, Var *> get_variables_map();
    unordered_map<string, Var *> get_sim_map();
    unordered_map<string, Command *> get_command_map();
};

