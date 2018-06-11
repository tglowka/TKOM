#include "ErrorHandling.h"

int currentLine = 1;
int currentColumn = 1;

void  Errors::ErrorHandling::divZeroError(){
    cout<<"Error: division by zero !!!"<<endl;
    exit(1);
}

void  Errors::ErrorHandling::undefinedVariable(string varName){
    cout<<"Undefined variable: "<<varName<<endl;
    exit(1);
}

void yyerror(char* s){
    cout<<"Parse  Error: "<<s<<" at line: "<<currentLine<<" at column: "<<currentColumn<<endl;
    exit(1);
}

void Errors::ErrorHandling::lowerBoundIncorrect(int value){
    cout<<"Incorrect lower bound: "<<value<<endl;
    exit(1);
}

void Errors::ErrorHandling::lowerBoundGreaterThanUpperBound(){
    cout<<"Lower bound is greater than upper"<<endl;
    exit(1);
}

void Errors::ErrorHandling::upperBoundIncorrect(int value){
    cout<<"Incorrect upper bound: "<<value<<endl;
    exit(1);
}

void Errors::ErrorHandling::incorrectLeftExpressionComparison(){
    cout<<"Left expression has to be scalar"<<endl;
    exit(1);
}

void Errors::ErrorHandling::functionNotExist(string variable_name){
    cout<<"Function: "<<variable_name<<", does not exists"<<endl;
    exit(1);
}

void  Errors::ErrorHandling::updateColumn(char* s){
    string tmp(s);
    currentColumn += tmp.length();
}

void  Errors::ErrorHandling::addLine(){
    ++currentLine;
}

void  Errors::ErrorHandling::addColumn(){
    ++currentColumn;
}

void  Errors::ErrorHandling::resetColumn(){
    currentColumn = 0;
}

