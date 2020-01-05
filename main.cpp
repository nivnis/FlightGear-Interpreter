//
// Created by yuvallevy on 05/01/2020.
//
#include <string>
#include <vector>
#include "Parser.h"
#include "Lexer.h"


using namespace std;
int main(int argc, char *argv[]) {
    string fileName;
    //if a file name is passed in the arguments
    if(argc > 1) {
        fileName = argv[1];
    }
    //if there are no arguments - use the default file
    else{
        fileName = "fly.txt";
    }
    Lexer* lexer = new Lexer();
    vector<vector<string>> arr = lexer->do_lexer(fileName);
    Parser* parser = new Parser();
    parser->parse(arr);
}
