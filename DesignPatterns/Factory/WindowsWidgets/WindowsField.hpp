#pragma once
#include "../WidgetsAbstract/FieldAbstract.hpp"

class WindowsField : public FieldAbstract
{
    void paint() const override
    {
        std::cout << "WindowsField painted" << std::endl;
    }
};
