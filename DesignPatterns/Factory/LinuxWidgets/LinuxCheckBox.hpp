#pragma once
#include "../WidgetsAbstract/CheckBoxAbstract.hpp"

class LinuxCheckBox : public CheckBoxAbstract
{
    void paint() const override
    {
        std::cout << "LinuxCheckBox painted" << std::endl;
    }
};
