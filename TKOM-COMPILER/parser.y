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
#include <vector>
#include "ErrorHandling.h"
#include "ast.h"
#include <memory>
#include <utility>

using  namespace  std;
extern  int  yylex ();
std::shared_ptr<pgm> root_ptr;
%}


%start  program

%union {
double   double_val;
string*  string_val;

std::vector<double>* list_double_val;
std::vector<string>* list_string_val;

expression *exp_node;
statement *statement_node;
function_node *fun_node;

std::list<statement*> *statement_list;
std::vector<std::pair<std::string, std::string> >* function_arguments;
std::pair<std::string, std::string>* function_argument;

std::list<function_node*>*function_list;

pgm* prgrm;
}

%token <int_val >     OR THEN AND SHOW LOOP FOREACH IF BEGINN END IN FUNCTION RETURN VAR  STRING NUMBER_TYPE LEQUAL GEQUAL EQUAL NOTEQUAL NEWLINE ARG 
%token <string_val >     VARIABLE COMMENT
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
%type <statement_node> comment
%type <statement_node> statement
%type <statement_node> return
%type <statement_list> stmnt_list
%type <statement_node> fun_execution
%type <prgrm> program
%type <fun_node> function
%type <function_argument>	function_argument
%type <function_arguments>	function_arguments_list
%type <function_list>		function_list
%type <exp_node> prior_condition

%destructor {free($$);} VARIABLE DOUBLE_LISTDEF STRING_LISTDEF  condition expression if_statement foreach_statement print_statement var_initialization var_declaration statement return stmnt_list program function function_argument function_list function_arguments_list prior_condition


%left '<' '>' '=' NOTEQUAL LEQUAL GEQUAL EQUAL
%left '+' '-'
%left '*' '/'

%%
program: BEGINN NEWLINE stmnt_list function_list  END  NEWLINE {$$ = new pgm($3,$4); root_ptr = std::make_shared<pgm>(*$$);}

	
function_list:	function_list 		NEWLINE				{ $$ = $1;}
|				function_list   	function NEWLINE	{ $$ = $1; $$ -> push_back($2);}
|														{ $$ = new std::list<function_node*>();}

function:  FUNCTION NUMBER_TYPE VARIABLE '(' function_arguments_list ')'	NEWLINE BEGINN NEWLINE stmnt_list  END FUNCTION { $$ = new function_node($10, $5, "number", *$3);}
|		   FUNCTION STRING 		VARIABLE '(' function_arguments_list ')'	NEWLINE BEGINN NEWLINE stmnt_list  END FUNCTION { $$ = new function_node($10, $5, "string", *$3);}

stmnt_list: stmnt_list NEWLINE              { $$ = $1;}
|           stmnt_list statement NEWLINE    { $$ = $1; $$ -> push_back($2); }
|                                           { $$ = new std::list<statement*>();}

function_arguments_list: function_arguments_list						{ $$ = $1; }
|						 function_arguments_list     function_argument  { $$ = $1; $$ -> push_back(*$2);}
|																		{ $$ = new std::vector<std::pair<std::string, std::string>>();}
													

function_argument:  ARG VAR NUMBER_TYPE VARIABLE	{ $$ = new std::pair<std::string, std::string>("varnumber", *$4);}
|					ARG NUMBER_TYPE		VARIABLE	{ $$ = new std::pair<std::string, std::string>("number", *$3);}
|					ARG STRING 			VARIABLE	{ $$ = new std::pair<std::string, std::string>("string", *$3);}


statement: var_initialization
|          var_declaration
|          print_statement
|          foreach_statement
|          if_statement
|		   return
|		   fun_execution
|		   comment

comment: COMMENT { $$ = new comment_node($1);}

print_statement: SHOW '(' VARIABLE ')'   											{$$ = new show_statement($3);}

foreach_statement: FOREACH VARIABLE IN VARIABLE LOOP NEWLINE stmnt_list END LOOP    {$$ = new foreach_statement($2, $4, $7);}

if_statement: IF condition THEN  NEWLINE stmnt_list END IF   						{$$ = new if_statement($2, $5);}

return: RETURN expression 							{$$ = new return_statement($2);}

fun_execution: VARIABLE '('function_arguments_list')' {$$ = new function_execution($1, $3);}

condition: expression                               {$$ = $1;}
|          expression           OR  condition       {$$ = new or_node($1, $3);}
|          condition            OR  expression      {$$ = new or_node($1, $3);}
|          prior_condition      AND prior_condition {$$ = new and_node($1, $3);}
|          prior_condition      OR  prior_condition {$$ = new or_node($1, $3);}
|          prior_condition      AND expression      {$$ = new and_node($1, $3);}
|          prior_condition      OR  expression      {$$ = new or_node($1, $3);}
|          expression           AND prior_condition {$$ = new and_node($1, $3);}
|          expression           OR  prior_condition {$$ = new or_node($1, $3);}
|          prior_condition                          {$$ = $1;}

prior_condition : '('condition')'                {$$ = $2;}
|                 expression AND expression      {$$ = new and_node($1, $3);}

expression: DOUBLE                               { $$ = new double_value($1);}
|           STRING_LISTDEF                       { $$ = new string_list_value($1);}
|           DOUBLE_LISTDEF                       { $$ = new double_list_value($1);}
|           VARIABLE                             { $$ = new id_node($1);}
|           VARIABLE NOTEQUAL VARIABLE { $$ = new not_equal_node($1,$3);}
|           VARIABLE EQUAL    VARIABLE { $$ = new equal_node ($1,$3);}
|           VARIABLE GEQUAL   VARIABLE { $$ = new greater_equal_node ($1, $3);}
|           VARIABLE LEQUAL   VARIABLE { $$ = new less_equal_node ($1, $3);}
|           VARIABLE '<'      VARIABLE { $$ = new less_node ($1, $3);}
|           VARIABLE '>'      VARIABLE { $$ = new greater_node ($1, $3);}
|           expression '*'      expression { $$ = new times_node ($1, $3);}
|           expression '/'      expression { $$ = new divide_node ($1, $3);}
|           expression '+'      expression { $$ = new plus_node ($1, $3);}
|           expression '-'      expression { $$ = new minus_node ($1, $3);}
|        '('expression')'                  { $$ = $2;}
|           VARIABLE '[' VARIABLE ',' DOUBLE ']'   {$$ = new sub_list($1,$3,$5);}
|           VARIABLE '[' DOUBLE ',' DOUBLE ']'     {$$ = new sub_list($1,$3,$5);}
|           VARIABLE '[' VARIABLE ',' VARIABLE ']' {$$ = new sub_list($1,$3,$5);}
|           VARIABLE '[' DOUBLE ',' VARIABLE ']'   {$$ = new sub_list($1,$3,$5);}
|           VARIABLE '[' NOTEQUAL expression']'    {$$ = new filter_list($1,"!=",$4);}
|           VARIABLE '[' EQUAL expression']'       {$$ = new filter_list($1,"==",$4);}
|           VARIABLE '[' LEQUAL expression']'      {$$ = new filter_list($1,"<=",$4);}
|           VARIABLE '[' GEQUAL expression']'      {$$ = new filter_list($1,">=",$4);}
|           VARIABLE '[' '>' expression']'         {$$ = new filter_list($1,">",$4);}
|           VARIABLE '[' '<' expression']'         {$$ = new filter_list($1,"<",$4);}



var_declaration: VAR NUMBER_TYPE VARIABLE       {$$ = new var_declaration_statement("double", $3);}
    |            NUMBER_TYPE     VARIABLE       {$$ = new var_declaration_statement("double_list", $2);}
    |            STRING          VARIABLE       {$$ = new var_declaration_statement("string_list", $2);}


var_initialization: VAR NUMBER_TYPE VARIABLE '=' expression   {$$ = new var_definition_statement("double", $3, $5);}
|                   VARIABLE                 '=' expression   {$$ = new var_definition_statement("null",$1 ,$3);}
|                   NUMBER_TYPE     VARIABLE '=' expression   {$$ = new var_definition_statement("double_list", $2, $4);}
|                   STRING          VARIABLE '=' expression   {$$ = new var_definition_statement("string_list", $2, $4);}



%%
