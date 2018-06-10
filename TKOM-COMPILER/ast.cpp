#include "ast.h"
#include "ErrorHandling.h"
#include "parser.h"
using namespace std;

vector<string> variables;
map <string ,double > var_double;
map <string ,vector<double> > var_list_double;
map <string ,vector<string> > var_list_string;
/*
==========================================================
=======================CONSTRUCTORS=======================
==========================================================
*/

id_node::id_node(string *variable_name){
     this->variable_name = *variable_name;
 }

operator_node::operator_node(expression *l, expression *r){
    left = l;
    right = r;
}


/*
==========================================================
=======================ABSTRAC SYNTAX TREE================
==========================================================
*/

double id_node::evaluate_number(){
    return var_double[variable_name];
}

vector<string> id_node::evaluate_string_list(){
    return var_list_string[variable_name];
}

vector<double> id_node::evaluate_double_list(){
    return var_list_double[variable_name];
}


double double_value::evaluate_number(){
    return double_val;
}

vector<string> string_list_value::evaluate_string_list(){
    return string_list_val;
}

vector<double> double_list_value::evaluate_double_list(){
    return double_list_val;
}


double plus_node::evaluate_number(){
    double l = left->evaluate_number();
    double r = right->evaluate_number();

    double value = r + l;
    return value;
}

vector<string> plus_node::evaluate_string_list(){
    vector<string> l = left->evaluate_string_list();
    vector<string> r = right->evaluate_string_list();
    l.insert( l.end(), r.begin(), r.end() );
    return l;
}

vector<double> plus_node::evaluate_double_list(){
    vector<double>  l = left->evaluate_double_list();
    vector<double>  r = right->evaluate_double_list();
    l.insert( l.end(), r.begin(), r.end() );
    return l;
}

double minus_node::evaluate_number(){
    double l = left->evaluate_number();
    double r = right->evaluate_number();
    double value = l - r;
    return value;
}

double times_node::evaluate_number(){
    double l = left->evaluate_number();
    double r = right->evaluate_number();
    double value = r * l;
    return value;
}

vector<double> times_node::evaluate_double_list(){
    vector<double>  l = left->evaluate_double_list();
    vector<double>  r = right->evaluate_double_list();
    vector<double>  final_list;
    if(l.size() <= r.size()){
        for(int i = 0; i < l.size(); ++i){
            final_list.push_back(l[i] * r[i]);
        }
    return final_list;
    }
    if(r.size() <= l.size()){
        for(int i = 0; i < r.size(); ++i){
            final_list.push_back(l[i] * r[i]);
        }
    return final_list;
    }
}

vector<string> times_node::evaluate_string_list(){
    vector<string>  l = left->evaluate_string_list();
    vector<string>  r = right->evaluate_string_list();
    vector<string>  final_list;
    if(l.size() <= r.size()){
        for(int i = 0; i < l.size(); ++i){
            final_list.push_back(l[i] + r[i]);
        }
    return final_list;
    }
    if(r.size() <= l.size()){
        for(int i = 0; i < r.size(); ++i){
            final_list.push_back(l[i] + r[i]);
        }
    return final_list;
    }
}

double divide_node::evaluate_number(){
    double l = left->evaluate_number();
    double r = right->evaluate_number();
    if(r == 0){
        Errors::ErrorHandling::divZeroError();
    }
    double value = l/r;
    return value;
}

vector<double> sub_list::evaluate_double_list(){
    if(!existDoubleListVarialbe(list_name, var_list_double)){
        Errors::ErrorHandling::undefinedVariable(list_name);
    }
    if (lower_bound_name.empty() && upper_bound_name.empty()){

        if(lower_bound_value < 0)
            Errors::ErrorHandling::lowerBoundIncorrect(lower_bound_value);
        if(upper_bound_value >= var_list_double[list_name].size())
            Errors::ErrorHandling::upperBoundIncorrect(upper_bound_value);
        if(lower_bound_value > upper_bound_value)
            Errors::ErrorHandling::lowerBoundGreaterThanUpperBound();

        vector<double> sub_list_value (var_list_double[list_name].begin() + lower_bound_value, var_list_double[list_name].begin() + upper_bound_value );
        return sub_list_value;
    }else
    if (!lower_bound_name.empty() && upper_bound_name.empty()){
        if( existDoubleVarialbe(lower_bound_name, var_double)){

            if(var_double[lower_bound_name] < 0)
                Errors::ErrorHandling::lowerBoundIncorrect(var_double[lower_bound_name]);
            if(upper_bound_value >= var_list_double[list_name].size())
                Errors::ErrorHandling::upperBoundIncorrect(upper_bound_value);
            if(var_double[lower_bound_name] > upper_bound_value)
                Errors::ErrorHandling::lowerBoundGreaterThanUpperBound();

            vector<double> sub_list_value (var_list_double[list_name].begin() + var_double[lower_bound_name], var_list_double[list_name].begin() + upper_bound_value );
            return sub_list_value;
        }else{
            Errors::ErrorHandling::undefinedVariable(lower_bound_name);
        }
    }
    else
    if (lower_bound_name.empty() && !upper_bound_name.empty()){
        if( existDoubleVarialbe(upper_bound_name, var_double)){

            if(lower_bound_value < 0)
                Errors::ErrorHandling::lowerBoundIncorrect(lower_bound_value);
            if(var_double[upper_bound_name] >= var_list_double[list_name].size())
                Errors::ErrorHandling::upperBoundIncorrect(var_double[upper_bound_name]);
            if(lower_bound_value > var_double[upper_bound_name])
                Errors::ErrorHandling::lowerBoundGreaterThanUpperBound();

            vector<double> sub_list_value (var_list_double[list_name].begin() + lower_bound_value, var_list_double[list_name].begin() + var_double[upper_bound_name] );
            return sub_list_value;
        }else{
            Errors::ErrorHandling::undefinedVariable(upper_bound_name);
        }
    }else
    if (!lower_bound_name.empty() && !upper_bound_name.empty()){
        if( existDoubleVarialbe(upper_bound_name, var_double)){

            if(var_double[lower_bound_name] < 0)
                Errors::ErrorHandling::lowerBoundIncorrect(var_double[lower_bound_name]);
            if(var_double[upper_bound_name] >= var_list_double[list_name].size())
                Errors::ErrorHandling::upperBoundIncorrect(var_double[upper_bound_name]);
            if(var_double[lower_bound_name] > var_double[upper_bound_name])
                Errors::ErrorHandling::lowerBoundGreaterThanUpperBound();

            vector<double> sub_list_value (var_list_double[list_name].begin() + var_double[lower_bound_name], var_list_double[list_name].begin() + var_double[upper_bound_name] );
            return sub_list_value;
        }else{
            Errors::ErrorHandling::undefinedVariable(lower_bound_name + upper_bound_name);
        }
    }
}

vector<string> sub_list::evaluate_string_list(){
    if(!existStringListVarialbe(list_name, var_list_string)){
        Errors::ErrorHandling::undefinedVariable(list_name);
    }
    if (lower_bound_name.empty() && upper_bound_name.empty()){

        if(lower_bound_value < 0)
            Errors::ErrorHandling::lowerBoundIncorrect(lower_bound_value);
        if(upper_bound_value >= var_list_string[list_name].size())
            Errors::ErrorHandling::upperBoundIncorrect(upper_bound_value);
        if(lower_bound_value > upper_bound_value)
            Errors::ErrorHandling::lowerBoundGreaterThanUpperBound();

        vector<string> sub_list_value (var_list_string[list_name].begin() + lower_bound_value, var_list_string[list_name].begin() + upper_bound_value );
        return sub_list_value;
    }else
    if (!lower_bound_name.empty() && upper_bound_name.empty()){
        if( existDoubleVarialbe(lower_bound_name, var_double)){

            if(var_double[lower_bound_name] < 0)
                Errors::ErrorHandling::lowerBoundIncorrect(var_double[lower_bound_name]);
            if(upper_bound_value >= var_list_string[list_name].size())
                Errors::ErrorHandling::upperBoundIncorrect(upper_bound_value);
            if(var_double[lower_bound_name] > upper_bound_value)
                Errors::ErrorHandling::lowerBoundGreaterThanUpperBound();

            vector<string> sub_list_value (var_list_string[list_name].begin() + var_double[lower_bound_name], var_list_string[list_name].begin() + upper_bound_value );
            return sub_list_value;
        }else{
            Errors::ErrorHandling::undefinedVariable(lower_bound_name);
        }
    }
    else
    if (lower_bound_name.empty() && !upper_bound_name.empty()){
        if( existDoubleVarialbe(upper_bound_name, var_double)){

            if(lower_bound_value < 0)
                Errors::ErrorHandling::lowerBoundIncorrect(lower_bound_value);
            if(var_double[upper_bound_name] >= var_list_string[list_name].size())
                Errors::ErrorHandling::upperBoundIncorrect(var_double[upper_bound_name]);
            if(lower_bound_value > var_double[upper_bound_name])
                Errors::ErrorHandling::lowerBoundGreaterThanUpperBound();

            vector<string> sub_list_value (var_list_string[list_name].begin() + lower_bound_value, var_list_string[list_name].begin() + var_double[upper_bound_name] );
            return sub_list_value;
        }else{
            Errors::ErrorHandling::undefinedVariable(upper_bound_name);
        }
    }else
    if (!lower_bound_name.empty() && !upper_bound_name.empty()){
        if( existDoubleVarialbe(upper_bound_name, var_double)){

            if(var_double[lower_bound_name] < 0)
                Errors::ErrorHandling::lowerBoundIncorrect(var_double[lower_bound_name]);
            if(var_double[upper_bound_name] >= var_list_string[list_name].size())
                Errors::ErrorHandling::upperBoundIncorrect(var_double[upper_bound_name]);
            if(var_double[lower_bound_name] > var_double[upper_bound_name])
                Errors::ErrorHandling::lowerBoundGreaterThanUpperBound();

            vector<string> sub_list_value (var_list_string[list_name].begin() + var_double[lower_bound_name], var_list_string[list_name].begin() + var_double[upper_bound_name] );
            return sub_list_value;
        }else{
            Errors::ErrorHandling::undefinedVariable(lower_bound_name + upper_bound_name);
        }
    }
}

vector<double> filter_list::evaluate_double_list(){
    if(!existDoubleListVarialbe(list_name, var_list_double)){
        Errors::ErrorHandling::undefinedVariable(list_name);
    }
    vector<double> sub_list_value(var_list_double[list_name].size());
    if(operator_sign == ">"){
        auto it = copy_if (var_list_double[list_name].begin(), var_list_double[list_name].end(), sub_list_value.begin(), [&](double i){return i > node->evaluate_number();} );
        sub_list_value.resize(distance(sub_list_value.begin(),it));
    }else
    if(operator_sign == "<"){
        auto it = copy_if (var_list_double[list_name].begin(), var_list_double[list_name].end(), sub_list_value.begin(), [&](double i){return i < node->evaluate_number();} );
        sub_list_value.resize(distance(sub_list_value.begin(),it));   
    }else
    if(operator_sign == "<="){
        auto it = copy_if (var_list_double[list_name].begin(), var_list_double[list_name].end(), sub_list_value.begin(), [&](double i){return i <= node->evaluate_number();} );
        sub_list_value.resize(distance(sub_list_value.begin(),it));
    }else
    if(operator_sign == ">="){
        auto it = copy_if (var_list_double[list_name].begin(), var_list_double[list_name].end(), sub_list_value.begin(), [&](double i){return i >= node->evaluate_number();} );
        sub_list_value.resize(distance(sub_list_value.begin(),it));
    }else
    if(operator_sign == "=="){
        auto it = copy_if (var_list_double[list_name].begin(), var_list_double[list_name].end(), sub_list_value.begin(), [&](double i){return i == node->evaluate_number();} );
        sub_list_value.resize(distance(sub_list_value.begin(),it));
    }else
    if(operator_sign == "!="){
        auto it = copy_if (var_list_double[list_name].begin(), var_list_double[list_name].end(), sub_list_value.begin(), [&](double i){return i != node->evaluate_number();} );
        sub_list_value.resize(distance(sub_list_value.begin(),it));
    }
    return sub_list_value;
}


bool and_node::evaluate_bool(){
    return left->evaluate_bool() && right->evaluate_bool();
}

bool or_node::evaluate_bool(){
    return left->evaluate_bool() || right->evaluate_bool();
}


bool equal_node::evaluate_bool(){
    if(existDoubleVarialbe(left_name, var_double) && existDoubleVarialbe(right_name, var_double)){
        return var_double[left_name] == var_double[right_name];
    }
    if(existDoubleVarialbe(left_name, var_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_double[left_name] == var_list_double[right_name].size();
    }
    if(existDoubleVarialbe(left_name, var_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_double[left_name] == var_list_string[right_name].size();
    }


    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleVarialbe(right_name, var_double)){
        return var_list_double[left_name].size() == var_double[right_name];
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_double[left_name].size() == var_list_double[right_name].size();
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_double[left_name].size() == var_list_string[right_name].size();
    }


    if(existStringListVarialbe(left_name, var_list_string) && existDoubleVarialbe(right_name, var_double)){
        return var_list_string[left_name].size() == var_double[right_name];
    }
    if(existStringListVarialbe(left_name, var_list_string) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_string[left_name].size() == var_list_double[right_name].size();
    }
    if(existStringListVarialbe(left_name, var_list_string) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_string[left_name].size() == var_list_string[right_name].size();
    }
}

bool not_equal_node::evaluate_bool(){
    if(existDoubleVarialbe(left_name, var_double) && existDoubleVarialbe(right_name, var_double)){
        return var_double[left_name] != var_double[right_name];
    }
    if(existDoubleVarialbe(left_name, var_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_double[left_name] != var_list_double[right_name].size();
    }
    if(existDoubleVarialbe(left_name, var_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_double[left_name] != var_list_string[right_name].size();
    }


    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleVarialbe(right_name, var_double)){
        return var_list_double[left_name].size() != var_double[right_name];
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_double[left_name].size() != var_list_double[right_name].size();
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_double[left_name].size() != var_list_string[right_name].size();
    }


    if(existStringListVarialbe(left_name, var_list_string) && existDoubleVarialbe(right_name, var_double)){
        return var_list_string[left_name].size() != var_double[right_name];
    }
    if(existStringListVarialbe(left_name, var_list_string) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_string[left_name].size() != var_list_double[right_name].size();
    }
    if(existStringListVarialbe(left_name, var_list_string) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_string[left_name].size() != var_list_string[right_name].size();
    }
}

bool greater_node::evaluate_bool(){
    if(existDoubleVarialbe(left_name, var_double) && existDoubleVarialbe(right_name, var_double)){
        return var_double[left_name] >var_double[right_name];
    }
    if(existDoubleVarialbe(left_name, var_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_double[left_name] > var_list_double[right_name].size();
    }
    if(existDoubleVarialbe(left_name, var_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_double[left_name] > var_list_string[right_name].size();
    }


    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleVarialbe(right_name, var_double)){
        return var_list_double[left_name].size() > var_double[right_name];
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_double[left_name].size() > var_list_double[right_name].size();
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_double[left_name].size() > var_list_string[right_name].size();
    }


    if(existStringListVarialbe(left_name, var_list_string) && existDoubleVarialbe(right_name, var_double)){
        return var_list_string[left_name].size() > var_double[right_name];
    }
    if(existStringListVarialbe(left_name, var_list_string) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_string[left_name].size() > var_list_double[right_name].size();
    }
    if(existStringListVarialbe(left_name, var_list_string) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_string[left_name].size() > var_list_string[right_name].size();
    }
}

bool less_node::evaluate_bool(){
    if(existDoubleVarialbe(left_name, var_double) && existDoubleVarialbe(right_name, var_double)){
        return var_double[left_name] < var_double[right_name];
    }
    if(existDoubleVarialbe(left_name, var_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_double[left_name] < var_list_double[right_name].size();
    }
    if(existDoubleVarialbe(left_name, var_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_double[left_name] < var_list_string[right_name].size();
    }


    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleVarialbe(right_name, var_double)){
        return var_list_double[left_name].size() < var_double[right_name];
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_double[left_name].size() < var_list_double[right_name].size();
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_double[left_name].size() < var_list_string[right_name].size();
    }


    if(existStringListVarialbe(left_name, var_list_string) && existDoubleVarialbe(right_name, var_double)){
        return var_list_string[left_name].size() < var_double[right_name];
    }
    if(existStringListVarialbe(left_name, var_list_string) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_string[left_name].size() < var_list_double[right_name].size();
    }
    if(existStringListVarialbe(left_name, var_list_string) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_string[left_name].size() < var_list_string[right_name].size();
    }
}

bool less_equal_node::evaluate_bool(){
    if(existDoubleVarialbe(left_name, var_double) && existDoubleVarialbe(right_name, var_double)){
        return var_double[left_name] <= var_double[right_name];
    }
    if(existDoubleVarialbe(left_name, var_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_double[left_name] <= var_list_double[right_name].size();
    }
    if(existDoubleVarialbe(left_name, var_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_double[left_name] <= var_list_string[right_name].size();
    }


    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleVarialbe(right_name, var_double)){
        return var_list_double[left_name].size() <= var_double[right_name];
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_double[left_name].size() <= var_list_double[right_name].size();
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_double[left_name].size() <= var_list_string[right_name].size();
    }


    if(existStringListVarialbe(left_name, var_list_string) && existDoubleVarialbe(right_name, var_double)){
        return var_list_string[left_name].size() <= var_double[right_name];
    }
    if(existStringListVarialbe(left_name, var_list_string) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_string[left_name].size() <= var_list_double[right_name].size();
    }
    if(existStringListVarialbe(left_name, var_list_string) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_string[left_name].size() <= var_list_string[right_name].size();
    }
}

bool greater_equal_node::evaluate_bool(){
    if(existDoubleVarialbe(left_name, var_double) && existDoubleVarialbe(right_name, var_double)){
        return var_double[left_name] >= var_double[right_name];
    }
    if(existDoubleVarialbe(left_name, var_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_double[left_name] >= var_list_double[right_name].size();
    }
    if(existDoubleVarialbe(left_name, var_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_double[left_name] >= var_list_string[right_name].size();
    }


    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleVarialbe(right_name, var_double)){
        return var_list_double[left_name].size() >= var_double[right_name];
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_double[left_name].size() >= var_list_double[right_name].size();
    }
    if(existDoubleListVarialbe(left_name, var_list_double) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_double[left_name].size() >= var_list_string[right_name].size();
    }


    if(existStringListVarialbe(left_name, var_list_string) && existDoubleVarialbe(right_name, var_double)){
        return var_list_string[left_name].size() >= var_double[right_name];
    }
    if(existStringListVarialbe(left_name, var_list_string) && existDoubleListVarialbe(right_name, var_list_double)){
        return var_list_string[left_name].size() >= var_list_double[right_name].size();
    }
    if(existStringListVarialbe(left_name, var_list_string) && existStringListVarialbe(right_name, var_list_string)){
        return var_list_string[left_name].size() >= var_list_string[right_name].size();
    }
}

void show_statement::evaluate(){
    if(existDoubleVarialbe(variable_name, var_double)){
        printDouble(var_double[variable_name], variable_name);
    }else
    if(existDoubleListVarialbe(variable_name, var_list_double)){
        printDoubleList(var_list_double[variable_name], variable_name);
    }else
    if(existStringListVarialbe(variable_name, var_list_string)){
        printStringList(var_list_string[variable_name], variable_name);
    }else{
        Errors::ErrorHandling::undefinedVariable(variable_name);
    }
}

void var_declaration_statement::evaluate(){
    if (variable_type_name == "double"){
        var_double[variable_name] = 0;
    }else
    if (variable_type_name == "double_list"){
        var_list_double[variable_name] = vector<double>(1,0);
    }else
    if (variable_type_name == "string_list"){
        var_list_string[variable_name] = vector<string>(1,"nothing");
    }
}

void var_definition_statement::evaluate(){
    if (variable_type_name == "double"){
        var_double[variable_name] = node -> evaluate_number();
    }else
    if (variable_type_name == "double_list"){
        var_list_double[variable_name] = node -> evaluate_double_list();
    }else
    if (variable_type_name == "string_list"){
        var_list_string[variable_name] = node -> evaluate_string_list();
    }else
    if ( variable_type_name == "null"){
        if(existDoubleVarialbe(variable_name, var_double)){
            var_double[variable_name] = node -> evaluate_number();
        }else
        if(existDoubleListVarialbe(variable_name, var_list_double)){
            var_list_double[variable_name] = node -> evaluate_double_list();
        }else
        if(existStringListVarialbe(variable_name, var_list_string)){
            var_list_string[variable_name] = node -> evaluate_string_list();
        }else{
            Errors::ErrorHandling::undefinedVariable(variable_name);
        }
    }
}

void foreach_statement::evaluate(){
    int count;
    if(existStringListVarialbe(list_variable_name,var_list_string))
        count = var_list_string[list_variable_name].size();
    if(existDoubleListVarialbe(list_variable_name,var_list_double))
        count = var_list_double[list_variable_name].size();
    for(int i = 0; i < count; ++i){   
        for (auto v : *foreach_statement_list){
            v->evaluate();
        }
    }
}

void if_statement::evaluate(){
    bool conditions_result = node->evaluate_bool();
    if(conditions_result){
        for (auto v : *if_statement_list){
            v->evaluate();
        }
    }
}


void pgm::evaluate() {
 std::cout<<"begin"<<std::endl;
 for (auto v : *pgm_list_statements){
        v->evaluate();
 }
 std::cout<<std::endl;
 std::cout<<"end"<<std::endl;
}