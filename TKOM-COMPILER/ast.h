#ifndef AST_H
#define AST_H

#include <list>
#include <string>
#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class statement{
public:
    virtual void evaluate() = 0;
    virtual void print() {}
};

class pgm {
 protected:
  list<statement*> *pgm_list_statements;
 public:
  pgm(list<statement*> *pgm_list_statements): pgm_list_statements(pgm_list_statements){}
  void evaluate();
  void print();
};

class expression{

protected:
    double double_val;
    vector<double> double_list_val;
    vector<string> string_list_val;
public:
    
    expression(){}
    expression(double double_val):double_val(double_val){}
    expression(vector<double> double_list_val):double_list_val(double_list_val){}
    expression(vector<string> string_list_val):string_list_val(string_list_val){}

    virtual void print() = 0;
    virtual double evaluate_number() = 0;
    virtual vector<string> evaluate_string_list() = 0;
    virtual vector<double>evaluate_double_list() = 0;
    virtual bool evaluate_bool()= 0;
};

class id_node :public expression{
protected:
    string variable_name;
public:
    id_node(string* variable_name);
    void print();
    double evaluate_number();
    vector<string> evaluate_string_list();
    vector<double>evaluate_double_list();
    bool evaluate_bool(){}
};

class double_value:public expression{
protected:
public:
    double_value(double double_val):expression(double_val){}
    void print();
    double evaluate_number();
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list(){}
    bool evaluate_bool(){}
};

class double_list_value:public expression{
protected:
public:
    double_list_value(vector<double>* double_list_val):expression(*double_list_val){}
    void print();
    double evaluate_number(){}
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list();
    bool evaluate_bool(){}
};

class string_list_value:public expression{
protected:
public:
    string_list_value(vector<string>* string_list_val):expression(*string_list_val){}
    void print();
    double evaluate_number(){}  
    vector<string> evaluate_string_list();
    vector<double>evaluate_double_list(){}
    bool evaluate_bool(){}
};

class operator_node: public expression{
protected:
    expression *left;
    expression *right;
    string left_name;
    string right_name;
public:
    operator_node(expression *l, expression *r);
    operator_node(string l_name, string r_name): left_name(l_name), right_name(r_name){}
};

class plus_node: public operator_node{
public:
    plus_node(expression *l, expression *r):operator_node(l,r){}
    double evaluate_number();
    void print();
    vector<string>  evaluate_string_list();
    vector<double>  evaluate_double_list();
    bool evaluate_bool(){}
};

class and_node: public operator_node{
public:
    and_node(expression *l, expression *r):operator_node(l,r){}
    double evaluate_number(){}
    void print();
    vector<string>  evaluate_string_list(){}
    vector<double>  evaluate_double_list(){}
    bool evaluate_bool();
};

class or_node: public operator_node{
public:
    or_node(expression *l, expression *r):operator_node(l,r){}
    double evaluate_number(){}
    void print();
    vector<string>  evaluate_string_list(){}
    vector<double>  evaluate_double_list(){}
    bool evaluate_bool();
};

class equal_node: public operator_node{
public:
    equal_node(string *l, string *r):operator_node(*l,*r){}
    double evaluate_number(){}
    void print();
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list(){}
    bool evaluate_bool();
};

class not_equal_node: public operator_node{
public:
    not_equal_node(string *l, string *r):operator_node(*l,*r){}
    double evaluate_number(){}
    void print();
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list(){}
    bool evaluate_bool();
};

class minus_node: public operator_node{
public:
    minus_node(expression *l, expression *r):operator_node(l,r){}
    void print();
    double evaluate_number();
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list(){}
    bool evaluate_bool(){}
};

class times_node: public operator_node{
public:
    times_node(expression *l, expression *r):operator_node(l,r){}
    void print();
    double evaluate_number();
    vector<string> evaluate_string_list();
    vector<double>evaluate_double_list();
    bool evaluate_bool(){}
};

class divide_node: public operator_node{
public:
    divide_node(expression *l, expression *r):operator_node(l,r){}
    void print();
    double evaluate_number();
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list(){}
    bool evaluate_bool(){}
};

class greater_node: public operator_node{
public:
    greater_node(string *l, string *r):operator_node(*l,*r){}
    void print();
    double evaluate_number(){}
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list(){}
    bool evaluate_bool();
};

class less_node: public operator_node{
public:
    less_node(string *l, string *r):operator_node(*l,*r){}
    void print();
    double evaluate_number(){}
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list(){}
    bool evaluate_bool();
};

class greater_equal_node: public operator_node{
public:
    greater_equal_node(string *l, string *r):operator_node(*l,*r){}
    void print();
    double evaluate_number(){}
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list(){}
    bool evaluate_bool();
};

class less_equal_node: public operator_node{
public:
    less_equal_node(string *l, string *r):operator_node(*l,*r){}
    void print();
    double evaluate_number(){}
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list(){}
    bool evaluate_bool();
};

class sub_list: public expression {
protected:
    string list_name;
    string lower_bound_name;
    string upper_bound_name;
    int lower_bound_value;
    int upper_bound_value;
public:
    sub_list(string* list_name, string* lower_bound_name, int upper_bound_value):
        list_name(*list_name),
        lower_bound_name(*lower_bound_name),
        upper_bound_value(upper_bound_value){}
    sub_list(string* list_name, int lower_bound_value, int upper_bound_value):
        list_name(*list_name),
        lower_bound_value(lower_bound_value),
        upper_bound_value(upper_bound_value){}
    sub_list(string* list_name, string* lower_bound_name, string* upper_bound_name):
        list_name(*list_name),
        lower_bound_name(*lower_bound_name),
        upper_bound_name(*upper_bound_name){}
    sub_list(string* list_name, int lower_bound_value, string* upper_bound_name):
        list_name(*list_name),
        lower_bound_value(lower_bound_value),
        upper_bound_name(*upper_bound_name){}
    void print();
    double evaluate_number(){}
    vector<string> evaluate_string_list();
    vector<double>evaluate_double_list();
    bool evaluate_bool(){}
};

class filter_list: public expression {
protected:
    string list_name;
    string operator_sign;
    expression* node;
public:
    filter_list(string* list_name,const string operator_sign,expression* node):
        list_name(*list_name),
        operator_sign(operator_sign),
        node(node){}
    void print();
    double evaluate_number(){}
    vector<string> evaluate_string_list(){}
    vector<double>evaluate_double_list();
    bool evaluate_bool(){}
};

class var_declaration_statement:public statement{
protected:
    string variable_name;
    string variable_type_name;
public:
    var_declaration_statement(string variable_type_name, string* variable_name):
        variable_type_name(variable_type_name),
        variable_name(*variable_name){}
    void evaluate();
    void print();
};

class var_definition_statement:public statement{
protected:
    string variable_name;
    string variable_type_name;
    expression* node;
public:
    var_definition_statement(const string variable_type_name,string* variable_name, expression* node):
        variable_type_name(variable_type_name),
        variable_name(*variable_name),
        node(node){}
    void evaluate();
    void print();
};

class foreach_statement:public statement{
protected:
 string temporary_list_element;
 string list_variable_name;
 list<statement*>* foreach_statement_list;
public:
    foreach_statement(string* temporary_list_element, string* list_variable_name, list<statement*> *foreach_statement_list):
        temporary_list_element(*temporary_list_element),
        list_variable_name(*list_variable_name),
        foreach_statement_list(foreach_statement_list){}
    void evaluate();
    void print();
};

class if_statement:public statement{
protected:
 expression *node;
 list<statement*> *if_statement_list;
public:
    if_statement(expression* node ,list<statement*> * if_statement_list):
         node(node),
         if_statement_list(if_statement_list){}
    void evaluate();
    void print();
};

class show_statement:public statement{
protected:
 string variable_name;
public:
    show_statement(string* variable_name): variable_name(*variable_name){}
    void evaluate();
    void print();
};

#endif
