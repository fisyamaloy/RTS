#pragma once
#include <iostream>

class ButtonAbstract
{
public:
    virtual ~ButtonAbstract() = default;

    virtual void paint() const = 0;
};
