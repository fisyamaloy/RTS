#pragma once
#include <iostream>

#include "../WidgetsAbstract/ButtonAbstract.hpp"

class LinuxButton : public ButtonAbstract
{
    void paint() const override
    {
        std::cout << "LinuxButton painted" << std::endl;
    }
};
