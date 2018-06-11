#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <iostream>
#include <string>
#include <map>
#include "ast.h"
#include <memory>
#include <cstdlib>
using namespace std;
#include "parser.tab.h"
extern FILE* yyin;
extern int yylex();

class ParserStructure{
public:

    static vector<double>* parseListDefinitionNumber(char *);
    static vector<string>* parseListDefinitionString(char *);

    bool addVariable(string varName);
};
void printStringList(vector<string> vec, string variable_name);
void printDoubleList(vector<double> vec, string variable_name);
void printDouble(double value, string variable_name);
void printFunArgumentsList(vector<pair<string,string> > vec);

bool existDoubleVarialbe(string variable_name, map <string ,double > map);
bool existDoubleListVarialbe(string variable_name, map <string ,vector <double> > map);
bool existStringListVarialbe(string variable_name, map <string ,vector <string> > map);
bool existFunctionVarialbe(string variable_name, map <string ,function_node > map);


void readFromString(string data);

#endif
