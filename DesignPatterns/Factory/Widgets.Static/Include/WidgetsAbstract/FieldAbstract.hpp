#pragma once
#include <iostream>

class FieldAbstract
{
public:
    virtual ~FieldAbstract() = default;

    virtual void paint() const = 0;
};
