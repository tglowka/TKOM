#include "ast.h"
#include "parser.h"


void pgm::print() {
 std::cout<<"begin"<<std::endl;
  for (auto v : *function_list){
        v->print();
 }
 for (auto v : *pgm_list_statements){
        v->print();
 }
 std::cout<<std::endl;
 std::cout<<"end"<<std::endl;
}

/*
==============================================================================
----------------------------PRINT METHODS-------------------------------------
==============================================================================
*/
void id_node::print (){
    std::cout<<variable_name;
}

void double_value::print (){
    std::cout<<double_val;
}

void double_list_value::print (){
    for (auto v : double_list_val)
        std::cout<<v<<" ";
}

void string_list_value::print (){
    for (auto v : string_list_val)
        std::cout<<"\""<<v<<"\""<<" ";
}

void plus_node::print(){
    std::cout<<"(";left->print();std::cout<<"+";right->print();std::cout<<")";
}

void equal_node::print(){
    std::cout<<"("<<left_name<<"=="<<right_name<<")";
}

void and_node::print(){
    std::cout<<"(";    left->print();    std::cout<<" AND ";    right->print();    std::cout<<")";
}

void or_node::print(){
    std::cout<<"(";    left->print();    std::cout<<" OR ";    right->print();    std::cout<<")";
}

void not_equal_node::print(){
    std::cout<<"("<<left_name<<"!="<<right_name<<")";
}

void minus_node::print(){
    std::cout<<"(";    left->print();    std::cout<<"-";    right->print();    std::cout<<")";
}

void times_node::print(){
    std::cout<<"(";    left->print();    std::cout<<"*";    right->print();    std::cout<<")";
}

void divide_node::print(){
    std::cout<<"(";    left->print();    std::cout<<"/";    right->print();    std::cout<<")";
}

void greater_node::print(){
    std::cout<<"("<<left_name<<">"<<right_name<<")";
}

void less_node::print(){
    std::cout<<"("<<left_name<<"<"<<right_name<<")";
}

void greater_equal_node::print(){
    std::cout<<"("<<left_name<<">="<<right_name<<")";
}

void less_equal_node::print(){
    std::cout<<"("<<left_name<<"<="<<right_name<<")";
}

void sub_list::print(){
    if(lower_bound_name.length() == 0 && lower_bound_name.length() == 0){
        std::cout<<list_name<<"["<<lower_bound_value<<","<<upper_bound_value<<"]";
    }
    if(lower_bound_name.length() != 0 && lower_bound_name.length() == 0){
        std::cout<<list_name<<"["<<lower_bound_name<<","<<upper_bound_value<<"]";
    }
    if(lower_bound_name.length() == 0 && lower_bound_name.length() != 0){
        std::cout<<list_name<<"["<<lower_bound_value<<","<<upper_bound_name<<"]";
    }
    if(lower_bound_name.length() != 0 && lower_bound_name.length() != 0){
        std::cout<<list_name<<"["<<lower_bound_name<<","<<upper_bound_name<<"]";
    }
}

void filter_list::print(){
    std::cout<<list_name<<"["<<operator_sign<<"";
    node->print();
    std::cout<<"]";
}

void var_declaration_statement::print(){
    if(variable_type_name == "double"){
        std::cout<<"var number "<<variable_name;
    }else
    if(variable_type_name == "double_list"){
        std::cout<<"number "<<variable_name;
    }else
    if(variable_type_name == "string_list"){
        std::cout<<"string "<<variable_name;
    }
}

void var_definition_statement::print(){
    if(variable_type_name == "double"){
        std::cout<<"var number "<<variable_name<<"=";
        node->print();
    }else
    if(variable_type_name == "double_list"){
        std::cout<<"number "<<variable_name<<"=";
        node->print();
    }else
    if(variable_type_name == "string_list"){
        std::cout<<"string "<<variable_name<<"=";
        node->print();
    }else
    if(variable_type_name == "null"){
        std::cout<<variable_name<<"=";
        node->print();
    }
}

void foreach_statement::print(){
    std::cout<<"foreach "<<temporary_list_element<<" in "<<list_variable_name<<" loop"<<std::endl;
    for (auto v : *foreach_statement_list){
        v->print();
        std::cout<<std::endl;
    }
    std::cout<<"end loop";
}

void if_statement::print(){
    std::cout<<"if ";
    node -> print();
    std::cout<<"then"<<std::endl;
    for (auto v : *if_statement_list){
        v->print();
        std::cout<<std::endl;
    }
    std::cout<<"end if";
}

void show_statement::print(){
    std::cout<<"show (";
    std::cout<<variable_name;
    std::cout<<")";
}

void return_statement::print(){
    std::cout<<"return ";
    node->print();
}

void function_execution::print(){
    std::cout<<function_name<<"(";
    printFunArgumentsList(*function_arguments);
    std::cout<<")";
}

void function_node::print(){
    std::cout<<"function "<<return_type<<" "<<function_name;
    std::cout<<"(";
    printFunArgumentsList(*function_arguments);
    std::cout<<" )"<<std::endl;
    std::cout<<"begin"<<std::endl;
    for (auto v : *function_list_statements){
        v->print();
        std::cout<<std::endl;
    }
    std::cout<<"end"<<std::endl;
}

void comment_node::print(){
    std::cout<<comment_content<<std::endl;
}

/*
==============================================================================
------------------------END PRINT METHODS-------------------------------------
==============================================================================
*/
