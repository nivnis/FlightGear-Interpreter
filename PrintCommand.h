//
// Created by yuvallevy on 20/12/2019.
//

#ifndef UNTITLED_PRINTCOMMAND_H
#define UNTITLED_PRINTCOMMAND_H
#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "Command.h"

using namespace std;

class PrintCommand : public Command {
public:
    int execute(vector<vector<string>> arr, int index);

    PrintCommand();
//    ~PrintCommand()= default;
};

#endif //UNTITLED_PRINTCOMMAND_H