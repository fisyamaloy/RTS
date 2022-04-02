#pragma once
#ifdef __linux__

#include "../WidgetsAbstract/CheckBoxAbstract.hpp"

class LinuxCheckBox : public CheckBoxAbstract
{
    void paint() const override
    {
        std::cout << "LinuxCheckBox painted" << std::endl;
    }
};

#endif