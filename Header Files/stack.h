#include <iostream>
#include <string>
#include <unordered_map>

// size of the array (stack)
const int MAX_SIZE = 26; 


class Stack
{

private:

    std::string array[MAX_SIZE];

    int top;

public:

    Stack()
    {
        top = -1;
    }

    // method to push numeric elements onto stack
    void pushNumber(double value);

    // method to push character elements onto stack
    void pushChar(char variable);

    // method to pop numeric elements from stack
    double popNumber();

    // method to pop character elements from stack
    char popChar();

    // method to check if stack is empty 
    bool isEmpty();

    std::string peek_top();

    // method to empty stack
    void clearStack();
};