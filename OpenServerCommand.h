 //
// Created by yuvallevy on 20/12/2019.
//

#ifndef UNTITLED_OPENSERVERCOMMAND_H
#define UNTITLED_OPENSERVERCOMMAND_H

#endif //UNTITLED_OPENSERVERCOMMAND_H
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Command.h"
#include "Server.h"

 using namespace std;

 class OpenServerCommand : public Command {
 public:
     int execute(vector<vector<string>> arr, int index);

     OpenServerCommand();
//    ~OpenServerCommand()= default;
 };