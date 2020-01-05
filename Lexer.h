//
// Created by yuvallevy on 05/01/2020.
//

#ifndef PORJECT1_LEXER_H
#define PORJECT1_LEXER_H

#endif //PORJECT1_LEXER_H
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




class Lexer {
public:
    Lexer();
    vector<vector<string>> do_lexer (string file_name);
    string removeSpaces(string input);
};