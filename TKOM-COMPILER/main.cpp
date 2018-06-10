#include  <cstdio>
#include <iostream>
#include  <cstdlib>
#include  <string>
#include <vector>
#include <list>
using  namespace  std;
#include "parser.tab.h"
#include "parser.h"
extern pgm* root;
extern std::shared_ptr<pgm> root_ptr;
extern int yy_scan_string(const char *);
extern FILE* yyin;

int  main(int  num_args , char** args) {

    if(num_args > 2){
        string program_code = "";
        for(int i = 1; i < num_args; ++i){
            program_code =program_code +  args[i] + '\n';
        }

        cout<<program_code<<endl;
        freopen("output.txt","w",stdout);
        readFromString(program_code);
    }else
    if(num_args == 2){
        FILE *fp;
        fp = fopen(args[1],  "r");
        yyin = fp;
        freopen("output.txt","w",stdout);
        yyparse ();
        root_ptr->evaluate();
        fclose(fp);
    }else{
        cout<<"Error, wrong arguments"<<endl;
    }

}

void readFromString(string data){
    yy_scan_string(data.c_str());
    yyparse ();
    root_ptr->print();
}
