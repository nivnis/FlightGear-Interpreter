//
// Created by yuvallevy on 20/12/2019.
//

#ifndef UNTITLED_COMMAND_H
#define UNTITLED_COMMAND_H
#pragma once

#endif //UNTITLED_COMMAND_H
using namespace std;
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "ex1.h"
using namespace std;
// command abstract class
class Command {
public:
    virtual int execute(vector<vector<string>> arr, int index) = 0;
//    virtual ~Command() = default;
};