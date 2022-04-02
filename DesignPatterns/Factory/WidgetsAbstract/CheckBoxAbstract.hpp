#pragma once
#include <iostream>

class CheckBoxAbstract
{
public:
    virtual ~CheckBoxAbstract() = default;

    virtual void paint() const = 0;
};
