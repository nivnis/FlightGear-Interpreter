//
// Created by yuvallevy on 20/12/2019.
//

#include "WhileCommand.h"
#include <vector>
#include <iostream>
#include <string>
#include "SymbolTable.h"
using namespace std;
WhileCommand:: WhileCommand() : Command() {

}

int WhileCommand:: execute(vector<vector<string>> arr, int index){
    SymbolTable* symbolTable = symbolTable->getInstance();
    string full_exp = arr[index][1];
    string left_exp,right_exp;
    Interpreter* i1 = new Interpreter();
    Expression* e1 = nullptr;
    Expression* e2= nullptr;
    int condition = 0;
    // to avoid getting conditions that start with the same char like: "<" and "<="
    int already_in = 0;
    vector<vector<string>> vector_commands;
    int i = index+1;
    while (arr[i][0] != "}"){
        vector_commands.push_back(arr[i]);
        i++;
    }
    i++;
    size_t found = full_exp.find("<=");
    if ( found != string::npos && already_in == 0){
        already_in = 1;
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+2, arr[index][1].length()-(found + 2));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() <= e2->calculate()){
            condition=1;
        }
    }
    size_t found2 = full_exp.find(">=");
    if (found2  != string::npos && already_in == 0){
        already_in = 1;
        left_exp = full_exp.substr(0, found2);
        right_exp = full_exp.substr(found2+2, arr[index][1].length()-(found2 + 2));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() >= e2->calculate()){
            condition=1;
        }
    }
    size_t found3 = full_exp.find("<");
    if (found3 !=  string::npos && already_in == 0){
        already_in = 1;
        left_exp = full_exp.substr(0, found3);
        right_exp = full_exp.substr(found3+1, arr[index][1].length()-(found3 + 1));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() < e2->calculate()){
            condition=1;
        }
    }
    size_t found4 = full_exp.find(">");
    if(found4 != string::npos && already_in == 0){
        already_in = 1;
        left_exp = full_exp.substr(0, found4);
        right_exp = full_exp.substr(found4+1, arr[index][1].length()-(found4 + 1));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() > e2->calculate()){
            condition=1;
        }
    }
    size_t found5 = full_exp.find("!=");
     if (found5 != string::npos && already_in == 0){
         already_in = 1;
        left_exp = full_exp.substr(0, found5);
        right_exp = full_exp.substr(found5+2, arr[index][1].length()-(found5 + 2));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() != e2->calculate()){
            condition=1;
        }
    }
    size_t found6 = full_exp.find("==");
    if ( found6  != string::npos && already_in == 0){
        already_in = 1;
        left_exp = full_exp.substr(0, found6);
        right_exp = full_exp.substr(found6+1, arr[index][1].length()-(found6 + 1));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() == e2->calculate()){
            condition=1;
        }
    }
    // need to make a new parser and go over the list...
    if(condition){
        int j = 0;
        for(j;j< vector_commands.size();j++){
            unordered_map<string,Command*>::const_iterator got =
                    symbolTable->get_command_map().find(vector_commands[j][0]);
            Command* c = got->second;
            index += c->execute(vector_commands,j);
        }
        return 0;
    }
    return i;
}

//    IfCommand:: ~IfCommand(){
//
//    }