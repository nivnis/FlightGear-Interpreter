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
    size_t found;
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
    if ((found = full_exp.find(">=")) != string::npos){
        already_in = 1;
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+2, arr[index][1].length()-(found + 2));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() >= e2->calculate()){
            condition=1;
        }
    }
    else if ((found = full_exp.find("<=")) != string::npos){
        already_in = 1;
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+2, arr[index][1].length()-(found + 2));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() <= e2->calculate()){
            condition=1;
        }
    }
    else if ((found = full_exp.find(">")) != string::npos){
        already_in = 1;
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+1, arr[index][1].length()-(found + 1));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() > e2->calculate()){
            condition=1;
        }
    }
    else if ((found = full_exp.find("<")) != string::npos){
        already_in = 1;
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+1, arr[index][1].length()-(found + 1));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() < e2->calculate()){
            condition=1;
        }
    }
    else if ((found = full_exp.find("==")) != string::npos){
         already_in = 1;
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+2, arr[index][1].length()-(found + 2));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() == e2->calculate()){
            condition=1;
        }
    }
    else if ((found = full_exp.find("!=")) != string::npos){
        already_in = 1;
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+1, arr[index][1].length()-(found + 1));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() != e2->calculate()){
            condition=1;
        }
    }
    // need to make a new parser and go over the list...
    if(condition){
        int j;
        for(j=0;j< vector_commands.size();j++){
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