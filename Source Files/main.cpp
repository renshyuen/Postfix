#include "postfix.h"

int main()
{
    PostfixInterpreter interpreter;

    std::string input;

    std::cout << "Enter a postfix expression (type 'exit' to quit): " << std::endl;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "Exit" || input == "EXIT")
        {
            break;
        }


        try
        {
            interpreter.evaluatePostfix(input);

            std::cout << "\n";
        }

        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }


    return 0;
}