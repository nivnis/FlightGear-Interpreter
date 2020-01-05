
#include "WhileCommand.h"
#include <vector>
#include <iostream>
#include <string>
#include "SymbolTable.h"
#include "Parser.h"
using namespace std;
WhileCommand:: WhileCommand() : ConditionParser() {

}

void WhileCommand:: run_condition(vector<vector<string>> vector_command,vector<vector<string>> arr, int index){
    Parser* parser = new Parser();
    while(check_condition(arr,index)){
        parser->parse(vector_command);
    }
}

//    WhileCommand:: ~WhileCommand(){
//
//    }
