//
// Created by pikachu on 1/3/20.
//

#ifndef PORJECT1_PARSER_H
#define PORJECT1_PARSER_H

#endif //PORJECT1_PARSER_H
#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include "PrintCommand.h"
#include "WhileCommand.h"
#include "SleepCommand.h"
#include "SymbolTable.h"
#include "ex1.h"
#include "Var.h"
#include "DefineVarCommand.h"
#include "IfCommand.h"
#include "Server.h"
#include "Client.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
using namespace std;

class Parser{
private:
    unordered_map<string,Command*> command_map;

public:
    Parser();
    void parse (vector<vector<string>> arr);
};