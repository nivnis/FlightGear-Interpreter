//
// Created by yuvallevy on 20/12/2019..
//

#ifndef UNTITLED_CONDITIONPARSER_H
#define UNTITLED_CONDITIONPARSER_H

#endif //UNTITLED_CONDITIONPARSER_H
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "SymbolTable.h"
#include "Parser.h"
#include "Command.h"
using namespace std;

class ConditionParser : public Command {
public:
    int execute(vector<vector<string>> arr, int index);
    bool check_condition(vector<vector<string>> arr, int index);
    ConditionParser();
    virtual void run_condition(vector<vector<string>> vector_command,vector<vector<string>> arr, int index) = 0;
//    ~ConditionParser()= default;
};