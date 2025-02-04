#include "stack.h"

void Stack::pushNumber(double value)
{
    if (top >= (MAX_SIZE - 1))
    {
        throw std::runtime_error("stack: stack is full");
    }

    else
    {
        try
        {
            std::string val = std::to_string(value);
            array[++top] = val;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }   
    }
}

void Stack::pushChar(char variable)
{
    if (top >= (MAX_SIZE - 1))
    {
        throw std::runtime_error("stack: stack is full");
    }

    else
    {
        try
        {
            std::string var(1, variable);
            array[++top] = var;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        } 
    }
}

double Stack::popNumber()
{
    if (top < 0)
    {
        throw std::runtime_error("stack: stack is empty");
    }

    else
    {
        try
        {
            double value = std::stod(array[top]);
            top--;

            return value;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}

char Stack::popChar()
{
    if (top < 0)
    {
        throw std::runtime_error("stack: stack is empty");
    }

    else
    {
        try
        {
            char variable = array[top][0];
            top--;

            return variable;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }       
    }

    return 0;
}

bool Stack::isEmpty()
{
    return (top < 0);
}

std::string Stack::peek_top()
{
    if (top < 0)
    {
        throw std::runtime_error("stack: stack is empty");
    }

    else
    {
        return array[top];
    }
}

void Stack::clearStack()
{
    // reset top to empty stack
    top = -1;
}