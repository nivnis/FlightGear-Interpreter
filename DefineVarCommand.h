//
// Created by yuvallevy on 20/12/2019.
//

#ifndef UNTITLED_DEFINEVARCOMMAND_H
#define UNTITLED_DEFINEVARCOMMAND_H

#endif //UNTITLED_DEFINEVARCOMMAND_H
#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "Command.h"

using namespace std;

class DefineVarCommand : public Command {

public:
    int execute(vector<vector<string>> arr, int index);

    DefineVarCommand();
//    ~DefineVarCommand()= default;
};