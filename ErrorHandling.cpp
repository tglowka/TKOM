#include "ErrorHandling.h"

int currentLine = 1;
int currentColumn = 1;
int aaa = 0;

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
