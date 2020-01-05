//
// Created by yuvallevy on 20/12/2019.
//

#ifndef UNTITLED_IFCOMMAND_H
#define UNTITLED_IFCOMMAND_H

#endif //UNTITLED_IFCOMMAND_H
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Command.h"
using namespace std;

class IfCommand : public Command {
public:
    int execute(vector<vector<string>> arr, int index);
    bool check_condition(vector<vector<string>> arr, int index);
    IfCommand();
//    ~PrintCommand()= default;
};