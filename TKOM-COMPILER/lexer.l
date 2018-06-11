%{
#include  <cstdio>
#include <iostream>
#include  <cstdlib>
#include  <string>
#include <list>
using  namespace  std;
#include "parser.tab.h"
#include "ErrorHandling.h"
#include "parser.h"
extern void yyerror(char* );


%}
%option noyywrap

%%
[ ]                     Errors::ErrorHandling::addColumn();
[\t]                    Errors::ErrorHandling::addColumn();
[\n]                    Errors::ErrorHandling::addLine(); Errors::ErrorHandling::resetColumn();return NEWLINE;
or                      Errors::ErrorHandling::updateColumn(yytext);return OR;
and                     Errors::ErrorHandling::updateColumn(yytext);return AND;
var                     Errors::ErrorHandling::updateColumn(yytext);return VAR;
number                  Errors::ErrorHandling::updateColumn(yytext);return NUMBER_TYPE;
string                  Errors::ErrorHandling::updateColumn(yytext);return STRING;
show                    Errors::ErrorHandling::updateColumn(yytext);return SHOW;
foreach                 Errors::ErrorHandling::updateColumn(yytext);return FOREACH;
if                      Errors::ErrorHandling::updateColumn(yytext);return IF;
end                     Errors::ErrorHandling::updateColumn(yytext);return END;
then                    Errors::ErrorHandling::updateColumn(yytext);return THEN;
begin                   Errors::ErrorHandling::updateColumn(yytext);return BEGINN;
loop                    Errors::ErrorHandling::updateColumn(yytext);return LOOP;
arg						Errors::ErrorHandling::updateColumn(yytext);return ARG;
in                      Errors::ErrorHandling::updateColumn(yytext);return IN;
return                  Errors::ErrorHandling::updateColumn(yytext);return RETURN;
function                Errors::ErrorHandling::updateColumn(yytext);return FUNCTION;
==                      Errors::ErrorHandling::updateColumn(yytext);return EQUAL;
!=                      Errors::ErrorHandling::updateColumn(yytext);return NOTEQUAL;
\<=                     Errors::ErrorHandling::updateColumn(yytext);return LEQUAL;
\>=                     Errors::ErrorHandling::updateColumn(yytext);return GEQUAL;
#.+						Errors::ErrorHandling::updateColumn(yytext);yylval.string_val = new  string(yytext); return COMMENT;
\{[0-9]+(\.[0-9]+)?(,[0-9]+(\.[0-9]+)?)*\}             Errors::ErrorHandling::updateColumn(yytext);yylval.list_double_val = ParserStructure::parseListDefinitionNumber(yytext);return DOUBLE_LISTDEF;
\{(\'.+\')(,(\'.+\'))*\}                               Errors::ErrorHandling::updateColumn(yytext);yylval.list_string_val = ParserStructure::parseListDefinitionString(yytext);return STRING_LISTDEF;
[a-zA-Z][a-zA-Z0-9]*                                   Errors::ErrorHandling::updateColumn(yytext); yylval.string_val = new  string(yytext); return  VARIABLE ;
[0-9]+(\.[0-9]+)?                                      Errors::ErrorHandling::updateColumn(yytext); yylval.double_val = atof(yytext); return  DOUBLE;
[/\+\*\[\]\)\(\-\.,\}\{=;\>\<]                         Errors::ErrorHandling::addColumn();return yytext[0];
%%
