//
// Created by yuvallevy on 18/11/2019.
//

#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
using namespace std;


class Expression {
public:
    virtual double calculate() = 0;
    virtual ~Expression() {}

};
class UnaryOperator : public Expression {
protected:
    Expression* e;
public:
    UnaryOperator(Expression* e1);
    ~UnaryOperator();
};

class BinaryOperator : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression* left1, Expression* right1);
    ~BinaryOperator();
};
class Value :public Expression {
private:
    const double val;
public:
    Value(double val1);
    double calculate();
};
class Variable : public Expression {
private:
    string name;
    double val;
public:
    Variable(string name1, double val1);
    double calculate();
    Variable& operator++();
    Variable& operator++(int);
    Variable& operator--();
    Variable& operator--(int);
    Variable& operator+=(double number);
    Variable& operator-=(double number);
};

class Plus : public BinaryOperator {
public:
    Plus(Expression* left1, Expression* right1);
    double calculate();
};
class Minus : public BinaryOperator {
public:
    Minus(Expression* left1, Expression* right1);
    double calculate();
};
class Mul : public BinaryOperator {
public:
    Mul(Expression* left1, Expression* right1);
    double calculate();
};
class Div : public BinaryOperator {
public:
    Div(Expression* left1, Expression* right1);
    double calculate();
};
class UPlus : public UnaryOperator {
public:
    UPlus(Expression* e1);
    double calculate();
};
class UMinus : public UnaryOperator {
public:
    UMinus(Expression* e1);
    double calculate();
};

class Interpreter {
    stack<string> string_stack;
    queue<string> string_queue;
    stack<Expression*> exp_stack;
    map<string, double> variables_map;
public:
    Interpreter();
    Expression* interpret(string s);
    void shunting_yard(string s);
    Expression* rpn(std::queue<string> queue);
    string num_to_string(string str, unsigned int num);
    string var_to_string(string str, unsigned int num);
    int precedence(string op1);
    Expression* var_in_map(string s);
    void setVariables(string s);
    int check_variable(string str);
    int check_val(string str);
    void set_var_in_map(string var, double val);
    int paren_check(string s);
};