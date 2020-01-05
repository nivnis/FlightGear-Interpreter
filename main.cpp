//
// Created by yuvallevy on 05/01/2020.
//
#include <string>
#include <vector>
#include "Parser.h"
#include "Lexer.h"


using namespace std;
int main() {
    Lexer* lexer = new Lexer();
    vector<vector<string>> arr = lexer->do_lexer("fly.txt");
    Parser* parser = new Parser();
    parser->parse(arr);
}
