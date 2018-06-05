#ifndef AST_H
#define AST_H

#include <list>
#include <string>
#include <iterator>
#include <iostream>



class statement{
public:
    virtual void evaluate() = 0;
    virtual void print() {}
};

class pgm {
 protected:
  std::list<statement*> *pgm_list_statements;
 public:
  pgm(std::list<statement*> *pgm_list_statements): pgm_list_statements(pgm_list_statements){}
  void evaluate();
};

class expression{
protected:
    double double_val;
    std::list<double> double_list_val;
    std::list<std::string> string_list_val;
public:

    expression(){}
    expression(double double_val):double_val(double_val){}
    expression(std::list<double> double_list_val):double_list_val(double_list_val){}
    expression(std::list<std::string> string_list_val):string_list_val(string_list_val){}

    virtual void print() = 0;
    virtual double evaluate_number() = 0;
    virtual std::list<std::string> evaluate_string_list() = 0;
    virtual std::list<double>evaluate_double_list() = 0;
};

class id_node :public expression{
protected:
    std::string variable_name;
public:
    id_node(std::string* variable_name):variable_name(*variable_name){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class double_value:public expression{
protected:
public:
    double_value(double double_val):expression(double_val){}// double_val(double_val){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class double_list_value:public expression{
protected:
public:
    double_list_value(std::list<double>* double_list_val):expression(*double_list_val){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class string_list_value:public expression{
protected:
public:
    string_list_value(std::list<std::string>* string_list_val):expression(*string_list_val){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class operator_node: public expression{
protected:
    expression *left;
    expression *right;
public:
    operator_node(expression *l, expression *r):left(l), right(r){}
};

class plus_node: public operator_node{
public:
    plus_node(expression *l, expression *r):operator_node(l,r){}
    double evaluate_number(){}
    void print();
    std::list<std::string>  evaluate_string_list(){}
    std::list<double>  evaluate_double_list(){}
};

class and_node: public operator_node{
public:
    and_node(expression *l, expression *r):operator_node(l,r){}
    double evaluate_number(){}
    void print();
    std::list<std::string>  evaluate_string_list(){}
    std::list<double>  evaluate_double_list(){}
};

class or_node: public operator_node{
public:
    or_node(expression *l, expression *r):operator_node(l,r){}
    double evaluate_number(){}
    void print();
    std::list<std::string>  evaluate_string_list(){}
    std::list<double>  evaluate_double_list(){}
};

class equal_node: public operator_node{
public:
    equal_node(expression *l, expression *r):operator_node(l,r){}
    double evaluate_number(){}
    void print();
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class not_equal_node: public operator_node{
public:
    not_equal_node(expression *l, expression *r):operator_node(l,r){}
    double evaluate_number(){}
    void print();
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class minus_node: public operator_node{
public:
    minus_node(expression *l, expression *r):operator_node(l,r){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class times_node: public operator_node{
public:
    times_node(expression *l, expression *r):operator_node(l,r){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class divide_node: public operator_node{
public:
    divide_node(expression *l, expression *r):operator_node(l,r){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class greater_node: public operator_node{
public:
    greater_node(expression *l, expression *r):operator_node(l,r){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class less_node: public operator_node{
public:
    less_node(expression *l, expression *r):operator_node(l,r){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class greater_equal_node: public operator_node{
public:
    greater_equal_node(expression *l, expression *r):operator_node(l,r){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class less_equal_node: public operator_node{
public:
    less_equal_node(expression *l, expression *r):operator_node(l,r){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class sub_list: public expression {
protected:
    std::string list_name;
    std::string lower_bound_name;
    std::string upper_bound_name;
    int lower_bound_value;
    int upper_bound_value;
public:
    sub_list(std::string* list_name, std::string* lower_bound_name, int upper_bound_value):
        list_name(*list_name),
        lower_bound_name(*lower_bound_name),
        upper_bound_value(upper_bound_value){}
    sub_list(std::string* list_name, int lower_bound_value, int upper_bound_value):
        list_name(*list_name),
        lower_bound_value(lower_bound_value),
        upper_bound_value(upper_bound_value){}
    sub_list(std::string* list_name, std::string* lower_bound_name, std::string* upper_bound_name):
        list_name(*list_name),
        lower_bound_name(*lower_bound_name),
        upper_bound_name(*upper_bound_name){}
    sub_list(std::string* list_name, int lower_bound_value, std::string* upper_bound_name):
        list_name(*list_name),
        lower_bound_value(lower_bound_value),
        upper_bound_name(*upper_bound_name){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class filter_list: public expression {
protected:
    std::string list_name;
    std::string operator_sign;
    expression* node;
public:
    filter_list(std::string* list_name,const std::string operator_sign,expression* node):
        list_name(*list_name),
        operator_sign(operator_sign),
        node(node){}
    void print();
    double evaluate_number(){}
    std::list<std::string> evaluate_string_list(){}
    std::list<double>evaluate_double_list(){}
};

class var_declaration_statement:public statement{
protected:
    std::string variable_name;
    std::string variable_type_name;
public:
    var_declaration_statement(std::string variable_type_name, std::string* variable_name):
        variable_type_name(variable_type_name),
        variable_name(*variable_name){}
    void evaluate(){}
    void print();
};

class var_definition_statement:public statement{
protected:
    std::string variable_name;
    std::string variable_type_name;
    expression* node;
public:
    var_definition_statement(const std::string variable_type_name,std::string* variable_name, expression* node):
        variable_type_name(variable_type_name),
        variable_name(*variable_name),
        node(node){}
    void evaluate(){}
    void print();
};

class foreach_statement:public statement{
protected:
 std::string temporary_list_element;
 std::string list_variable_name;
 std::list<statement*>* foreach_statement_list;
public:
    foreach_statement(std::string* temporary_list_element, std::string* list_variable_name, std::list<statement*> *foreach_statement_list):
        temporary_list_element(*temporary_list_element),
        list_variable_name(*list_variable_name),
        foreach_statement_list(foreach_statement_list){}
    void evaluate(){}
    void print();
};

class if_statement:public statement{
protected:
 expression *node;
 std::list<statement*> *if_statement_list;
public:
    if_statement(expression* node ,std::list<statement*> * if_statement_list):
         node(node),
         if_statement_list(if_statement_list){}
    void evaluate(){}
    void print();
};

class show_statement:public statement{
protected:
 expression *node;
public:
    show_statement(expression* node): node(node){}
    void evaluate(){}
    void print();
};

#endif
