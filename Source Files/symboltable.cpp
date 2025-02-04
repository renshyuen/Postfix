#include "symboltable.h"

SymbolTable::SymbolTable()
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        head[i] = nullptr;
    }
}


SymbolTable::~SymbolTable()
{
    // clear existing records in symbol table when exiting
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        Node* current = head[i];
        
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;

            delete temp;
        }

        head[i] = nullptr;
    }
}


int SymbolTable::hashFunction(std::string id)
{
    char firstCharacter = id[0];

    // convert 'A' to 'Z' or 'a' to 'z' to the corresponding index
    if (firstCharacter >= 'A' && firstCharacter <= 'Z')
    {
        return firstCharacter - 'A';
    }
    
    else if (firstCharacter >= 'a' && firstCharacter <= 'z')
    {
        return firstCharacter - 'a';
    }
    
    // invalid character
    else
    {
        return -1;
    }
}


bool SymbolTable::insert(std::string id, double value)
{
    // get hash index for the identifier
    int index = hashFunction(id);

    // if insertion fails
    if (index == -1)
    {
        throw std::runtime_error("symbol table: insert failed \n");
    }

    // create a new Node
    Node* newNode = new Node(id, value, true);

    // insert at the beginning if no collision
    if (head[index] == nullptr)
    {
        head[index] = newNode;
    }

    // handle collision using chaining
    else
    {
        Node* start = head[index];
        
        while (start->next != nullptr)
        {
            start = start->next;
        }

        start->next = newNode;
    }

    return true;
}


double SymbolTable::lookup(std::string id)
{
    int index = hashFunction(id);

    // get linked list at hash index
    Node* start = head[index];

    if (index == -1)
    {
        // invalid identifier for hash function
        throw std::runtime_error("symbol table: invalid variable \n");
    }

    while (start != nullptr)
    {
        if (start->identifier == id)
        {
            if (!start->hasValue)
            {
                throw std::runtime_error("symbol table: variable '" + id + "' has no existing value");
            }

            // return the value associated with the identifier
            return start->value;
        }

        // move to the next node
        start = start->next;
    }

    // if identifier not found
    throw std::runtime_error("symbol table: variable '" + id + "' has no existing value \n");

    return 0;
}


bool SymbolTable::remove(std::string id)
{
    int index = hashFunction(id);

    if (index == -1)
    {
        // invalid identifier for hash function
        throw std::runtime_error("symbol table: invalid variable \n");
    } 

    Node* current = head[index];

    Node* prev = nullptr;

    while (current != nullptr)
    {
        if (current->identifier == id)
        {
            if (prev == nullptr)
            {
                // node to be deleted is the head node
                head[index] = current->next;
            }

            else
            {
                // bypass the node to be deleted
                prev->next = current->next;
            }

            delete current;
            return true;
        }

        prev = current;
        current = current->next;
    }

    throw std::runtime_error("symbol table: variable '" + id + "' is not removed");
    return false;
}


bool SymbolTable::isExist(std::string id)
{
    int index = hashFunction(id);

    if (index == -1)
    {
        // invalid identifier for hash function
        throw std::runtime_error("symbol table: invalid variable \n");
    }

    Node* start = head[index];

    while (start != nullptr)
    {
        // check if variable has been assigned a value
        if (start->identifier == id)
        {
            return start->hasValue;
        }

        start = start->next;
    }

    // variable has not been assigned a value

    return false;
}