#pragma once
#include "../WidgetsAbstract/CheckBoxAbstract.hpp"

class WindowsCheckBox : public CheckBoxAbstract
{
    void paint() const override
    {
        std::cout << "WindowsCheckBox painted" << std::endl;
    }
};
