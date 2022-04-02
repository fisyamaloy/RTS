#pragma once
#ifdef _WIN32

#include <iostream>

#include "../WidgetsAbstract/ButtonAbstract.hpp"

class WindowsButton : public ButtonAbstract
{
    void paint() const override
    {
        std::cout << "WindowsButton painted" << std::endl;
    }
};

#endif