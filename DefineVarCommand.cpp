//
// Created by yuvallevy on 20/12/2019.
//

#include "DefineVarCommand.h"
#include "SymbolTable.h"
#include <vector>
#include <string>
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
    bool is_sim_var=false;
    // its creating a new var with arrow or equal.
    if (vector[0] == "var") {
        //check if its var sim or regular var.
        for(auto string_in_vector: vector){
            if(string_in_vector == "sim"){
                is_sim_var = true;
            }
        }
//        size_t found = vector[3].find("sim");
//        //its sim var
        if (is_sim_var){
            name = vector[1];
            sim = vector[4];
            direction = vector[2];
            // no value yet. need to check what should I put here.
            value = 0;
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
        symbolTable->setVarByName(name,value);

    }
    return 1;
}
// constructor
DefineVarCommand::DefineVarCommand() : Command() {

}

//    ~DefineVarCommand()= default;