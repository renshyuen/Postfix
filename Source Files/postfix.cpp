#include "postfix.h"

double PostfixInterpreter::applyOperator(char op, double num1, double num2)
{
    switch (op)
    {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/':
            if (num2 != 0)
            {
                return num1 / num2;
            } 

            else
            {
                throw std::runtime_error("postfix: division by zero \n");
            }

        /**
         *  additional mathematical operations
         */

        // exponentiation
        case '^': return std::pow(num1, num2);

        // modulo
        case '%':
            if (num2 != 0)
            {
                return std::fmod(num1, num2);
            }

            else
            {
                throw std::runtime_error("postfix: modulo by zero");
            }

        default: throw std::runtime_error("postfix: undefined operator \n");
    }
}


void PostfixInterpreter::assignVariable(std::string variable, double value)
{
    // if the variable has an existing value, delete and insert
    if (symbol_table.isExist(variable))
    {
        symbol_table.remove(variable);
    }

    symbol_table.insert(variable, value);
}


bool PostfixInterpreter::variableCheck(std::string variable)
{
    char firstCharacter = variable[0];

    if (firstCharacter >= 'A' && firstCharacter <= 'Z' || firstCharacter >= 'a' && firstCharacter <= 'z')
    {
        return true;
    }
    
    else
    {
        return false;
    }
}


double PostfixInterpreter::evaluatePostfix(std::string expression)
{
    // tokenize one by one
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        // if token is a variable assignment
        if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '^' || token[0] == '%'))
        {
            if (!stack.isEmpty())
            {
                // take a look at the first top element
                std::string firstElement = stack.peek_top();

                // if the first top element is a character
                if (std::isalpha(firstElement[0]))
                {
                    char character1 = stack.popChar();
                    std::string str1(1, character1);
                    double value1 = symbol_table.lookup(str1);

                    if (stack.isEmpty())
                    {
                        throw std::runtime_error("postfix: insufficient operands \n");
                    }

                    else
                    {
                        // take a look at the next top element
                        std::string secondElement = stack.peek_top();

                        // if the next top element is also a character
                        if (std::isalpha(secondElement[0]))
                        {
                            char character2 = stack.popChar();
                            std::string str2(1, character2);
                            double value2 = symbol_table.lookup(str2); 

                            // get result and push back onto stack 
                            double result1 = applyOperator(token[0], value2, value1);  
                            stack.pushNumber(result1);
                        }

                        // if the next top element is a number instead
                        else
                        {
                            double value3 = stack.popNumber();

                            // get result and push back onto stack
                            double result2 = applyOperator(token[0], value3, value1);
                            stack.pushNumber(result2);
                        }
                    }
                }



                // if the first top element is a number instead
                else
                {
                    double value1 = stack.popNumber();

                    if (stack.isEmpty())
                    {
                        throw std::runtime_error("postfix: insufficient operands \n");
                    }

                    else
                    {
                        // take a look at the next top element
                        std::string secondElement = stack.peek_top();

                        // if the next top element is a character
                        if (std::isalpha(secondElement[0]))
                        {
                            char character3 = stack.popChar();
                            std::string str3(1, character3);
                            double value2 = symbol_table.lookup(str3);

                            // get result and push back onto stack 
                            double result1 = applyOperator(token[0], value2, value1);
                            stack.pushNumber(result1);
                        }

                        // if the next top element is also a number
                        else
                        {
                            double value3 = stack.popNumber();
                            
                            // get result and push back onto stack 
                            double result2 = applyOperator(token[0], value3, value1);
                            stack.pushNumber(result2);
                        }
                    }
                }
            }

            else
            {
                throw std::runtime_error("postfix: stack is empty \n");
            }
        }



        // if token is an operator
        else if (token.size() == 1 && token == "=")
        {
            if (stack.isEmpty())
            {
                throw std::runtime_error("postfix: stack is empty \n");
            }

            else
            {
                std::string firstElement = stack.peek_top();

                // if the first top element is a character
                if (std::isalpha(firstElement[0]))
                {
                    char character1 = stack.popChar();
                    std::string str1(1, character1);

                    if (stack.isEmpty())
                    {
                        throw std::runtime_error("postfix: insufficient operands \n");
                    }

                    else
                    {
                        std::string secondElement = stack.peek_top();

                        // if the next top element is also a character
                        if (std::isalpha(secondElement[0]))
                        {
                            throw std::runtime_error("postfix: variable cannot be assigned to another variable \n");
                        }

                        else
                        {
                            double value1 = stack.popNumber();

                            // assign value to variable and push variable onto stack
                            assignVariable(str1, value1);
                            // stack.pushChar(character1);
                        }
                    }
            
                }


                // if the first top element is a number instead
                else
                {
                    double value2 = stack.popNumber();

                    if (stack.isEmpty())
                    {
                        throw std::runtime_error("postfix: insufficient operands \n");
                    }

                    else
                    {
                        std::string secondElement = stack.peek_top();

                        // if the next top element is also a number
                        if (std::isdigit(secondElement[0]))
                        {
                            throw std::runtime_error("postfix: value cannot be assigned to another value \n");
                        }

                        else
                        {
                            char character2 = stack.popChar();
                            std::string str2(1, character2);

                            // assign value to variable and push variable onto stack
                            assignVariable(str2, value2);
                            // stack.pushChar(character2); 
                        }
                    }
                           
                }
            }
        }



        /** if token is an operand */
        else
        {
            // if the operand is a number
            if (std::isdigit(token[0]) || (token.length() > 1 && std::isdigit(token[1])))
            {
                double number;
                std::istringstream(token) >> number;

                stack.pushNumber(number);
            }

            // if operand is a variable
            else if (token.size() == 1 && std::isalpha(token[0]))
            {
                // validate naming of variable
                if (variableCheck(token))
                {
                    char character = token[0];
                    stack.pushChar(character);
                }

                else
                {
                    throw std::runtime_error("postfix: variable naming must be a single alphabet \n");
                }
            }

            else
            {
                throw std::runtime_error("postfix: variable naming must be a single alphabet \n");
            }
        }
        

    }



    if (!stack.isEmpty())
    {
        // display the element at the top of the stack only

        std::cout << "Stack: " << stack.peek_top() << std::endl;

        stack.clearStack();
    }

    else
    {
        std::cout << "Stack: " << std::endl;
    }

    return 0;
}