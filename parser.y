%{
#include <iostream>
#include  <cstdio>
#include  <cstdlib>
#include  <string>
#include  <map>
#include <list>
#include "ErrorHandling.h"
using  namespace  std;
map <string ,double > var_double;
map <string ,list<double> > var_list_double;
map <string ,list<string> > var_list_string;   
extern  int  yylex ();
extern  void  yyerror(char *);

%}
%union {
int      int_val;
double   double_val;
std::string *str_val;
}
%token <int_val >     SHOW LOOP FOREACH IF BEGINN END IN FUNCTION RETURN VAR DOUBLE_TYPE INT_TYPE STRING NUMBER_TYPE LEQUAL GEQUAL EQUAL NOTEQUAL
%token <str_val >     VARIABLE
%token <double_val >  DOUBLE
%type <double_val > expression_double;
%type <double_val > inner1_double;
%type <double_val > inner2_double;

%start  parsetree
%%
parsetree:      BEGINN lines END ';';

lines:          lines  line | line;

line: SHOW  expression_double   ';'                              {cout<<$2<<endl;}
|     NUMBER_TYPE VAR VARIABLE  '='  expression_double  ';'    {var_double[*$3] = $5; delete  $3;};


expression_double: expression_double  '+'  inner1_double                 {$$ = $1 + $3;}
|               expression_double  '-'  inner1_double                  {$$ = $1 - $3;}
|               inner2_double                                       {$$ = $1;};

inner1_double: inner1_double  '*'  inner2_double                       {$$ = $1 * $3;}
|              inner1_double  '/'  inner2_double                       {if($3 == 0)  Errors::ErrorHandling::divZeroError ();  else $$ = $1 / $3;}
|              inner2_double                                    {$$ = $1;};

inner2_double:   VARIABLE                                {if(!var_double.count(*$1))   Errors::ErrorHandling::undefinedVariable(*$1); else $$ = var_double[*$1];  delete  $1;}
|                DOUBLE                                   {$$ = $1;}
|              '(' expression_double ')'                  {$$ = $2;}

%%
