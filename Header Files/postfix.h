#include "stack.h"
#include "symboltable.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

class PostfixInterpreter 
{
private:

    Stack stack;
    SymbolTable symbol_table;
    
    // perform operations (+ - * /)
    double applyOperator(char op, double num1, double num2);

    // assign value to a variable and insert into symbol table as a pair
    void assignVariable(std::string variable, double value);

    // variable check
    bool variableCheck(std::string variable);

public:

    // evaluate user input
    double evaluatePostfix(std::string expression);

};