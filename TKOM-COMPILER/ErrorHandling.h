#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


void yyerror(char* );
namespace Errors{
    class ErrorHandling{
        public:
                static void divZeroError();
                static void undefinedVariable(string varName);
                static void updateColumn(char* s);
                static void addLine();
                static void addColumn();
                static void resetColumn();
                static void lowerBoundIncorrect(int value);
                static void upperBoundIncorrect(int value);
                static void lowerBoundGreaterThanUpperBound();
                static void incorrectLeftExpressionComparison();
                static void functionNotExist(string variable_name);
    };
}

#endif
