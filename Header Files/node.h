#include <string>

class Node
{
    std::string identifier;
    double value;
    bool hasValue;

    Node* next;

public:

    Node();
    Node(std::string key, double value, bool valueAssigned);

    // Symbol Table needs access
    friend class SymbolTable;
};