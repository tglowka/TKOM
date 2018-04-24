#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
using namespace std;

class ParserStructure{
public:
    list<string> variables;
    map <string ,double > var_double;
    map <string ,list<double> > var_list_double;
    map <string ,list<string> > var_list_string;

public:

    static list<double>* parseListDefinition(char *);

    bool addVariable(string varName);


};


#endif
