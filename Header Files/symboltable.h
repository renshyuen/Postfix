#include "node.h"

#include <iostream>
#include <string>

#define MAX_SIZE 26

class SymbolTable
{
    // array of pointers to Node (hash table)
    Node* head[MAX_SIZE];

public:

    SymbolTable();
    ~SymbolTable();

    // hash function
    int hashFunction(std::string id); 
    
    // function to insert an identifier
    bool insert(std::string id, double value);
    
    // function to find value based on given identifier
    double lookup(std::string id);

    // function to delete an identifier
    bool remove(std::string id);

    // function to check if a variable exists and has a non-default value
    bool isExist(std::string id);
};