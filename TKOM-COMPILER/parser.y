%code requires{
    #include "ast.h"
}

%{
#include <iostream>
#include  <cstdio>
#include  <cstdlib>
#include  <string>
#include  <map>
#include <list>
#include "ErrorHandling.h"
//#include "parser.h"
#include "ast.h"

using  namespace  std;
extern  int  yylex ();
pgm* root;
%}


%start  program

%union {
double   double_val;
string*  string_val;
std::list<double>* list_double_val;
std::list<string>* list_string_val;
expression *exp_node;
statement *statement_node;
std::list<statement*> *statement_list;
pgm* prgrm;
}

%token <int_val >     OR THEN AND SHOW LOOP FOREACH IF BEGINN END IN FUNCTION RETURN VAR  STRING NUMBER_TYPE LEQUAL GEQUAL EQUAL NOTEQUAL NEWLINE
%token <string_val >     VARIABLE
%token <double_val >  DOUBLE
%token <list_double_val> DOUBLE_LISTDEF
%token <list_string_val> STRING_LISTDEF

%type <exp_node> condition
%type <exp_node> expression
%type <statement_node> if_statement
%type <statement_node> foreach_statement
%type <statement_node> print_statement
%type <statement_node> var_initialization
%type <statement_node> var_declaration
%type <statement_node> statement
%type <statement_list> stmnt_list
%type <prgrm> program
%type <exp_node> function
%type <exp_node> prior_condition

%left '<' '>' '=' NOTEQUAL LEQUAL GEQUAL EQUAL
%left '+' '-'
%left '*' '/'

%%
program: BEGINN NEWLINE stmnt_list END   NEWLINE {$$ = new pgm($3); root = $$;}


stmnt_list: stmnt_list NEWLINE              { $$ = $1;}
|           stmnt_list statement NEWLINE    { $$ = $1; $$ -> push_back($2); }
|                                           { $$ = new std::list<statement*>();}


statement: var_initialization
|          var_declaration
|          print_statement
|          foreach_statement
|          if_statement


print_statement: SHOW '(' expression ')'   {$$ = new show_statement($3);}

foreach_statement: FOREACH VARIABLE IN VARIABLE LOOP NEWLINE stmnt_list END LOOP   {$$ = new foreach_statement($2, $4, $7);}

if_statement: IF condition THEN  NEWLINE stmnt_list END IF   {$$ = new if_statement($2, $5);}

condition: expression                               {$$ = $1;}
|          expression           OR  condition       {$$ = new or_node($1, $3);}
|          condition            OR  expression      {$$ = new or_node($1, $3);}
|          expression           OR  expression      {$$ = new or_node($1, $3);}
|          prior_condition      AND prior_condition {$$ = new and_node($1, $3);}
|          prior_condition      OR  prior_condition {$$ = new or_node($1, $3);}
|          prior_condition      AND expression      {$$ = new and_node($1, $3);}
|          prior_condition      OR  expression      {$$ = new or_node($1, $3);}
|          expression           AND prior_condition {$$ = new and_node($1, $3);}
|          expression           OR  prior_condition {$$ = new or_node($1, $3);}
|          prior_condition                          {$$ = $1;}

prior_condition : '('condition')'                   {$$ = $2;}
|                 expression AND expression         {$$ = new and_node($1, $3);}

expression: DOUBLE                               { $$ = new double_value($1);}
|           STRING_LISTDEF                       { $$ = new string_list_value($1);}
|           DOUBLE_LISTDEF                       { $$ = new double_list_value($1);}
|           VARIABLE                             { $$ = new id_node($1);}
|           expression NOTEQUAL expression { $$ = new not_equal_node($1,$3);}
|           expression EQUAL    expression { $$ = new equal_node ($1,$3);}
|           expression GEQUAL   expression { $$ = new greater_equal_node ($1, $3);}
|           expression LEQUAL   expression { $$ = new less_equal_node ($1, $3);}
|           expression '<'      expression { $$ = new less_node ($1, $3);}
|           expression '>'      expression { $$ = new greater_node ($1, $3);}
|           expression '*'      expression { $$ = new times_node ($1, $3);}
|           expression '/'      expression { $$ = new divide_node ($1, $3);}
|           expression '+'      expression { $$ = new plus_node ($1, $3);}
|           expression '-'      expression { $$ = new minus_node ($1, $3);}
|        '('expression')'                  { $$ = $2;}
|           VARIABLE '[' VARIABLE ',' DOUBLE ']'   {$$ = new sub_list($1,$3,$5);}
|           VARIABLE '[' DOUBLE ',' DOUBLE ']'     {$$ = new sub_list($1,$3,$5);}
|           VARIABLE '[' VARIABLE ',' VARIABLE ']' {$$ = new sub_list($1,$3,$5);}
|           VARIABLE '[' DOUBLE ',' VARIABLE ']' {$$ = new sub_list($1,$3,$5);}
|           VARIABLE '[' NOTEQUAL expression']'  {$$ = new filter_list($1,"!=",$4);}
|           VARIABLE '[' EQUAL expression']'     {$$ = new filter_list($1,"==",$4);}
|           VARIABLE '[' LEQUAL expression']'    {$$ = new filter_list($1,"<=",$4);}
|           VARIABLE '[' GEQUAL expression']'    {$$ = new filter_list($1,">=",$4);}
|           VARIABLE '[' '>' expression']'       {$$ = new filter_list($1,">",$4);}
|           VARIABLE '[' '<' expression']'       {$$ = new filter_list($1,"<",$4);}


var_declaration: VAR NUMBER_TYPE VARIABLE       {$$ = new var_declaration_statement("double", $3);}
    |            NUMBER_TYPE     VARIABLE       {$$ = new var_declaration_statement("double_list", $2);}
    |            STRING          VARIABLE       {$$ = new var_declaration_statement("string_list", $2);}


var_initialization: VAR NUMBER_TYPE VARIABLE '=' expression   {$$ = new var_definition_statement("double", $3, $5);}
|                   VARIABLE                 '=' expression   {$$ = new var_definition_statement("null",$1 ,$3);}
|                   NUMBER_TYPE     VARIABLE '=' expression   {$$ = new var_definition_statement("double_list", $2, $4);}
|                   STRING          VARIABLE '=' expression   {$$ = new var_definition_statement("string_list", $2, $4);}



%%
