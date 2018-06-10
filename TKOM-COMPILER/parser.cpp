#include "parser.h"

extern int yy_scan_string(const char *);



vector<double>* ParserStructure::parseListDefinitionNumber(char* text){
    vector<double> *myList = new vector<double>();
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

vector<string>* ParserStructure::parseListDefinitionString(char* text){
    vector<string> *myList = new vector<string>();
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

void printStringList(vector<string> vec, string variable_name){
    std::cout<<variable_name<<": ";
    for (std::vector<string>::const_iterator i = vec.begin(); i != vec.end(); ++i)
    std::cout << '\'' << *i << "\',";
    std::cout<<std::endl;
}

void printDoubleList(vector<double> vec,  string variable_name){
    std::cout<<variable_name<<": ";
    for (std::vector<double>::const_iterator i = vec.begin(); i != vec.end(); ++i)
    std::cout << *i << " ,";
    std::cout<<std::endl;
}

void printDouble(double value, string variable_name){
    std::cout<<variable_name<<": "<<value<<std::endl;
}

bool existDoubleVarialbe(string variable_name, map<string, double> var_map){
    map<string,double>::const_iterator it_number = var_map.find(variable_name);
    return it_number != var_map.end();
}
bool existDoubleListVarialbe(string variable_name, map<string, vector <double> > var_map){
    map<string,vector<double> >::const_iterator it_number_list = var_map.find(variable_name);
    return it_number_list != var_map.end();
}
bool existStringListVarialbe(string variable_name, map<string, vector <string> > var_map){
    map<string,vector<string> >::const_iterator it_string_list = var_map.find(variable_name);
    return it_string_list != var_map.end();
}
