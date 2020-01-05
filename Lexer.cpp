//
// Created by yuvallevy on 05/01/2020.
//

#include "Lexer.h"

using namespace std;


Lexer::Lexer(){

}

vector<vector<string>> Lexer::do_lexer(string file_name) {
    vector<vector<string>> main_vector_arr;
    fstream file;
    string line;
    file.open(file_name, ios::in | ios::binary);
    if(!file.is_open()){
        throw "An error";
    }
    // reading line by line from the file.
    while (getline(file, line)) {
        vector<string> vector_arr;
        // checking if we have '\t'
        size_t found;
        line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
        // look for openDataServer to add it to the vector and get the port of it.
        found = line.find("openDataServer");
        if (found != string::npos){
            // number inside the parenthesis
            int i =15;
            while (line[i] != ')'){
                i++;
            }
            // get whats inside of the parenthesis which is the port and add it to the vector.
            string number = line.substr(15,i-15);
            vector_arr.push_back("openDataServer");
            vector_arr.push_back(number);
        }
        // look for connectControlClient to add it to the vector and get the port of it.
        found = line.find("connectControlClient");
        if (found != string::npos){
            // number inside the parenthesis
            int i =21;
            while (line[i] != ')'){
                i++;
            }
            // get whats inside of the parenthesis which is the port and add it to the vector.
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
            for( int k = 0; k < tokens.size(); k++){
                if (string::npos != tokens[k].find('\"')){
                    string token = tokens[k].substr(1,tokens[k].size()-2);
                    vector_arr.push_back(token);
                } else {
                    vector_arr.push_back(tokens[k]);
                }
            }
        }

        // look for Print to add it to the vector and get the port of it.
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

        // look for Sleep to add it to the vector and get the port of it.
        found = line.find("Sleep");
        if (found != string::npos){
            // number inside the parenthesis
            int i =6;
            while (line[i] != ')'){
                i++;
            }
            // get whats inside of the parenthesis which is the time and add it to the vector.
            string number = line.substr(6,i-6);
            vector_arr.push_back("Sleep");
            vector_arr.push_back(number);
        }

        // look for '='.
        found = line.find("=");
        if (found != string::npos){
            size_t found2 =  line.find("while");
            size_t found3 =  line.find("if");
            // checking that its not a while or if line and only Var line.
            if (found2 == string::npos && found3 == string::npos) {
                size_t found1 = line.find("var");
                // checking if its creating new Var line or updating one.
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
        // check while or if sentence.
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
            with_out_while = removeSpaces(with_out_while);
            vector_arr.push_back(with_out_while);
        }
        // pushing } to a vector.
        string close_paren = "}";
        if(line[0] == close_paren[0]){
            vector_arr.push_back("}");
        }
        main_vector_arr.push_back(vector_arr);
    }
    file.close();
    return main_vector_arr;
}
// function that remove spaces.
string Lexer::removeSpaces(string input){
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
