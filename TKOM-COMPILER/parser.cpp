#include "parser.h"
extern int yy_scan_string(const char *);



list<double>* ParserStructure::parseListDefinitionNumber(char* text){
    list<double> *myList = new list<double>();
    string tmp;
    double listValue;
    string data(text);

    for(int i = 1; i < data.size(); ++i){
        if(data[i] == ',' || data[i] == '}'){
            listValue = atof(tmp.c_str());
            myList->push_back(listValue);
            tmp.clear();
            continue;
        }
        tmp += data[i];
    }
    return myList;
}

list<string>* ParserStructure::parseListDefinitionString(char* text){
    list<string> *myList = new list<string>();
    string tmp;
    string listValue;
    string data(text);
    bool startStringValue = false;

    for(int i = 1; i < data.size(); ++i){
        if(data[i] == '\'' && startStringValue == false){
            startStringValue = true;
            continue;
        }else
        if(data[i] == '\'' && startStringValue == true){
            startStringValue = false;
            myList->push_back(tmp);
            tmp.erase();
            continue;
        }else
        if(startStringValue == true){
            tmp = tmp + data[i];
        }
    }
    return myList;
}
