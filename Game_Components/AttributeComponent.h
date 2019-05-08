#ifndef ATTRIBUTE_COMPONENT_H
#define ATTRIBUTE_COMPONENT_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

class AttributeComponent
{
public:
    // Attributes
    float timer; // time remaining in seconds
    unsigned points; // For each correct answer


    // Con / Dec
    AttributeComponent();
    virtual ~AttributeComponent();

    // Functions
    void UpdatePoints();
    // Check if you gained something
    void UpdateTime( const float& dt );
};

#endif // ATTRIBUTE_COMPONENT_H