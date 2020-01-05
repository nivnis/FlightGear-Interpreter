//
// Created by yuvallevy on 20/12/2019..
//

#ifndef UNTITLED_IFCOMMAND_H
#define UNTITLED_IFCOMMAND_H

#endif //UNTITLED_IFCOMMAND_H
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "ConditionParser.h"

using namespace std;

class IfCommand : public ConditionParser {
public:
    void run_condition(vector<vector<string>> vector_command,vector<vector<string>> arr, int index);
    IfCommand();
//    ~IfCommand()= default;

};