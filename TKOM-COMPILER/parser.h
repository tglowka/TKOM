#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
using namespace std;
#include "parser.tab.h"
extern FILE* yyin;
extern int yylex();
extern pgm* root;

class ParserStructure{
public:
    list<string> variables;
    map <string ,double > var_double;
    map <string ,list<double> > var_list_double;
    map <string ,list<string> > var_list_string;

public:

    static list<double>* parseListDefinitionNumber(char *);
    static list<string>* parseListDefinitionString(char *);

    bool addVariable(string varName);
};

void readFromString(string data);

#endif
