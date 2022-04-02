#pragma once

#ifdef __linux__
#include "../WidgetsAbstract/FieldAbstract.hpp"

class LinuxField : public FieldAbstract
{
    void paint() const override
    {
        std::cout << "LinuxField painted" << std::endl;
    }
};

#endif