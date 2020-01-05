//
// Created by yuvallevy on 05/01/2020.
//

#include <vector>
#include <iostream>
#include <string>
#include "ConditionParser.h"
using namespace std;
ConditionParser:: ConditionParser() : Command() {

}

int ConditionParser:: execute(vector<vector<string>> arr, int index) {
    vector<vector<string>> vector_commands;
    int i = index+1;

    while (arr[i][0] != "}"){
        vector_commands.push_back(arr[i]);
        i++;
    }
    i++;
    if(check_condition(arr,index)){
        run_condition(vector_commands,arr,index);
    }
    return i - index;
}

//    ConditionParser:: ~ConditionParser(){
//
//    }


bool ConditionParser::check_condition(vector<vector<string>> arr, int index){
    string full_exp = arr[index][1];
    string left_exp,right_exp;
    Interpreter* i1 = new Interpreter();
    Expression* e1 = nullptr;
    Expression* e2= nullptr;
    size_t found;
    bool condition = false;
    if ((found = full_exp.find(">=")) != string::npos){
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+2, arr[index][1].length()-(found + 2));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() >= e2->calculate()){
            condition=true;
        }
    }
    else if ((found = full_exp.find("<=")) != string::npos){
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+2, arr[index][1].length()-(found + 2));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() <= e2->calculate()){
            condition=true;
        }
    }
    else if ((found = full_exp.find(">")) != string::npos){
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+1, arr[index][1].length()-(found + 1));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() > e2->calculate()){
            condition=true;
        }
    }
    else if ((found = full_exp.find("<")) != string::npos){
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+1, arr[index][1].length()-(found + 1));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() < e2->calculate()){
            condition=true;
        }
    }
    else if ((found = full_exp.find("==")) != string::npos){
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+2, arr[index][1].length()-(found + 2));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() == e2->calculate()){
            condition=true;
        }
    }
    else if ((found = full_exp.find("!=")) != string::npos){
        left_exp = full_exp.substr(0, found);
        right_exp = full_exp.substr(found+1, arr[index][1].length()-(found + 1));
        e1 = i1->interpret(left_exp);
        e2 = i1->interpret(right_exp);
        if(e1->calculate() != e2->calculate()){
            condition=true;
        }
    }
    return condition;
}