//
// Created by yuvallevy on 22/12/2019.
//

#ifndef UNTITLED_VAR_H
#define UNTITLED_VAR_H
#pragma once
#endif //UNTITLED_VAR_H
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class Var{
private:
    string name;
    string direction;
    string sim;
    double val;
public:
    Var(string name1, string direction1, string sim1, double val1);
    Var(string name1, double val1);
    double setVal(double val1);
    double getVal();
    string getSim();
//    ~Var()= default;
};