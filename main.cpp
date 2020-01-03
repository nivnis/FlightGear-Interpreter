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
vector<vector<string>> lexer(string file_name);
string removeSpaces(string input);
void parser(vector<vector<string>> arr);
int main() {
    vector<vector<string>> arr = lexer("fly.txt");
    parser(arr);

//    for (int i = 0; i < arr.size(); i++) {
//        for (int j = 0; j < arr[i].size(); j++)
//            cout << arr[i][j] << " ";
//        cout << endl;
//    }

//    vector<vector<string>> arr;
//    vector<string> small_arr;
//    vector<string> small_arr1;
//    vector<string> small_arr2;
//    vector<string> small_arr3;
//    vector<string> small_arr4;
//    small_arr.push_back("while");
//    small_arr.push_back("3+5>10");
//    arr.push_back(small_arr);
//    small_arr1.push_back("bla");
//    arr.push_back(small_arr1);
//    small_arr2.push_back("bla");
//    arr.push_back(small_arr2);
//    small_arr3.push_back("bla");
//    arr.push_back(small_arr3);
//    small_arr4.push_back("}");
//    arr.push_back(small_arr4);
//    Command* whileCommand = new WhileCommand();
//    int answer = whileCommand->execute(arr, 0);
//    std::cout << answer << std::endl;

}

vector<vector<string>> lexer(string file_name){
    vector<vector<string>> main_vector_arr;
    fstream file;
    string line;
    file.open(file_name, ios::in | ios::binary);
    if(!file.is_open()){
        throw "An error";
    }
    while (getline(file, line)) {
        vector<string> vector_arr;
        // checking if we have '\t'
        size_t found;
        line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());


        // look for openDataServer
        found = line.find("openDataServer");
        if (found != string::npos){
            // number inside the parenthesis
            int i =15;
            while (line[i] != ')'){
                i++;
            }
            string number = line.substr(15,i-15);
            vector_arr.push_back("openDataServer");
            vector_arr.push_back(number);
        }

        // look for connectControlClient
        found = line.find("connectControlClient");
        if (found != string::npos){
            // number inside the parenthesis
            int i =21;
            while (line[i] != ')'){
                i++;
            }
            string in_paren = line.substr(21,i-21);
            // Vector of string to save tokens
            vector <string> tokens;
            // stringstream class check1
            stringstream check1(in_paren);
            string intermediate;
            // Tokenizing w.r.t. space ','
            while(getline(check1, intermediate, ','))
            {
                tokens.push_back(intermediate);
            }
            vector_arr.push_back("connectControlClient");
            for(int k = 0; k < tokens.size(); k++){
                if (string::npos != tokens[k].find('\"')){
                    string token = tokens[k].substr(1,tokens[k].size()-2);
                    vector_arr.push_back(token);
                } else {
                    vector_arr.push_back(tokens[k]);
                }
            }
        }

        // look for Print.
        found = line.find("Print");
        if (found != string::npos){
            // number inside the parenthesis
            int i =6;
            while (line[i] != ')'){
                i++;
            }
            string number = line.substr(6,i-6);
            vector_arr.push_back("Print");
            vector_arr.push_back(number);
        }

        // look for Sleep.
        found = line.find("Sleep");
        if (found != string::npos){
            // number inside the parenthesis
            int i =6;
            while (line[i] != ')'){
                i++;
            }
            string number = line.substr(6,i-6);
            vector_arr.push_back("Sleep");
            vector_arr.push_back(number);
        }

        // look for '='.
        found = line.find("=");
        if (found != string::npos){
            size_t found2 =  line.find("while");
            size_t found3 =  line.find("if");
            // no condition and its a define new var or change existing var.
            if (found2 == string::npos && found3 == string::npos) {
                size_t found1 = line.find("var");
                if (found1 != string::npos) {
                    line = line.substr(4, line.length() - 4);
                    vector_arr.push_back("var");
                } else{
                    // its changing value of variable.
                    vector_arr.push_back("Setvar");
                }
                // Vector of string to save tokens
                vector<string> tokens;
                // stringstream class check1
                stringstream check1(line);
                string intermediate;
                // Tokenizing w.r.t. space '='
                while (getline(check1, intermediate, '=')) {
                    tokens.push_back(intermediate);
                }
                //removing white spaces from each token and push it to the vector.
                string s = "";
                for (int k = 0; k < tokens.size(); k++) {
                std::string::iterator end_pos = std::remove(tokens[k].begin(), tokens[k].end(), ' ');
                tokens[k].erase(end_pos, tokens[k].end());
//                    s.append(tokens[k]);
                    vector_arr.push_back(tokens[k]);
                }
//                vector_arr.push_back(s);
            }
        }
        // look for '-> or '<-'
        size_t found1 = line.find("->");
        size_t found2 = line.find("<-");

        if ((found1 != string::npos) || (found2 != string::npos)){
            string with_out_var = line.substr(4,line.length()-4);
            string delimiter = "<-";
            if(found1 != string::npos){
                delimiter = "->";
            }

            // split by the arrow.
            size_t pos = 0;
            int second_string = 0;
            string token;
            // pushing 'var'
            vector_arr.push_back("var");
            while ((pos = with_out_var.find(delimiter)) != std::string::npos) {
                token = with_out_var.substr(0, pos);
                // trim from white spaces.
                std::string::iterator end_pos = std::remove(token.begin(), token.end(), ' ');
                token.erase(end_pos, token.end());
                if(second_string == 0){
                    with_out_var.erase(0, pos + delimiter.length());
                    // push first word
                    vector_arr.push_back(token);
                    // push first arrow
                    vector_arr.push_back(delimiter);
                    second_string++;
                }
                //take only whats inside the parenthasis.
                int i =4;
                while (with_out_var[i] != ')'){
                    i++;
                }
                string sec_string = with_out_var.substr(5,i-5);
                string simName = sec_string.substr(1, sec_string.length()-2);
                // push first 'sim'
                vector_arr.push_back("sim");
                // push second word
                vector_arr.push_back(simName);
                with_out_var.erase(0, pos + delimiter.length());
            }
        }
        // check while or if
        found = line.find("while");
        found1 = line.find("if");
        if (found != string::npos || found1 != string::npos){
            int i;
            if(found != string::npos) {
                vector_arr.push_back("while");
                i = 5;
            }else{
                vector_arr.push_back("if");
                i = 2;
            }
            string with_out_while = line.substr(i,line.length()-i-1);
//            while (with_out_while[i] != '{'){
//                i++;
//            }
            with_out_while = removeSpaces(with_out_while);

            vector_arr.push_back(with_out_while);
//            // Vector of string to save tokens
//            vector <string> tokens;
//            // stringstream class check1
//            stringstream check1(line);
//            string intermediate;
//            // Tokenizing w.r.t. space ' '
//            while(getline(check1, intermediate, ' '))
//            {
//                vector_arr.push_back(intermediate);
//            }
//            //removing white spaces from each token and push it to the vector.
//            for(int k = 0; k < tokens.size(); k++){
//                vector_arr.push_back(tokens[k]);
//            }
        }
        // pushing } to a vector.
        string close_paren = "}";
        if(line[0] == close_paren[0]){
            vector_arr.push_back("}");
        }


        //check func.
        main_vector_arr.push_back(vector_arr);
    }
    file.close();
    return main_vector_arr;
}

void parser(vector<vector<string>> arr){
    SymbolTable* symbol_table = symbol_table->getInstance();
    unordered_map<string,Command*> command_map;
    OpenServerCommand* openData = new OpenServerCommand();
    ConnectCommand* connectCommand = new ConnectCommand();
    DefineVarCommand* Var = new DefineVarCommand();
    SleepCommand* sleep = new SleepCommand();
    PrintCommand* print = new PrintCommand();
    WhileCommand* whilee = new WhileCommand();
    IfCommand* iff = new IfCommand();
    command_map["openDataServer"] = openData;
    command_map["connectControlClient"] = connectCommand;
    command_map["Setvar"] = Var;
    command_map["var"] = Var;
    command_map["Sleep"] = sleep;
    command_map["Print"] = print;
    command_map["while"] = whilee;
    command_map["if"] = iff;

    int index = 0;
    while( index < arr.size()){
        unordered_map<string,Command*>::const_iterator got = command_map.find(arr[index][0]);
        Command* c = got->second;
        index += c->execute(arr,index);
    }



}

string removeSpaces(string input)
{
    int length = input.length();
    for (int i = 0; i < length; i++) {
        if(input[i] == ' ')
        {
            input.erase(i, 1);
            length--;
            i--;
        }
    }
    return input;
}



