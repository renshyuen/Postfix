#include "node.h"

// initializes node parameters' default values
Node::Node()
    : identifier(""), value(0.0), hasValue(false), next(nullptr)
{
    
}

Node::Node(std::string key, double value, bool valueAssigned)
    : identifier(key), value(value), hasValue(valueAssigned), next(nullptr)
{
}