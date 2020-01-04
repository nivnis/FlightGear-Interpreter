//
// Created by yuvallevy on 20/12/2019.
//

#include "DefineVarCommand.h"
#include "SymbolTable.h"
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include "ex1.h"

using namespace std;

int DefineVarCommand::execute(vector<vector<string>> arr, int index) {
    Interpreter* i1 = new Interpreter();
    Expression* e1 = nullptr;
    SymbolTable *symbolTable = symbolTable->getInstance();
    vector<string> vector = arr[index];
    string name, sim, direction;
    string to_inter;
    double value;
    bool answer;
    // its creating a new var with arrow or equal.
    if (vector[0] == "var") {
        //check if its var sim or regular var.
        size_t found = vector[3].find("sim");
        //its sim var
        if ( found != string::npos){
            name = vector[1];
            sim = vector[4];
            direction = vector[2];
            // no value yet. need to check what should I put here.
            value = 0;
            answer = false;
            symbolTable->addVar(name, sim, direction, value);
        }
        //its regular var.
        else{
            name = vector[1];
            sim = '"';
            direction = "=";
            to_inter = vector[2];
            e1 = i1->interpret(to_inter);
            value = e1->calculate();
            answer = false;
            symbolTable->addVar(name, sim, direction, value);
        }
    } else {

        // its changing the value of a var.
        // Set var
        to_inter = vector[2];
        name = vector[1];
        sim = "=";
        direction = "";
        e1 = i1->interpret(to_inter);
        value = e1->calculate();
        answer = true;
        symbolTable->setVarByName(name,value);

    }

    return 1;
}

DefineVarCommand::DefineVarCommand() : Command() {

}

//    ~DefineVarCommand()= default;