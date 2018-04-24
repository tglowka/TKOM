#include  <cstdio>
#include <iostream>
#include  <cstdlib>
#include  <string>
#include <list>
using  namespace  std;
#include "parser.tab.h"
extern FILE* yyin;

int  main(int  num_args , char** args) {
if(num_args  != 2) {
    cout<<"usage: ./ lexer  filename<<cout"<<endl;
    exit (0);
}
FILE* file = fopen(args[1],"r");
if(file == NULL) {
    cout<<"couldn ’t open file"<<endl;
    exit (0);
}
yyin = file;
yyparse ();
fclose(file);
}
