#include "parser.h"

list<double>* ParserStructure::parseListDefinition(char* text){
    list<double> *myList = new list<double>();
    string tmp;
    double listValue;
    string data(text);

    for(int i = 1; i < data.size() - 1; ++i){
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
