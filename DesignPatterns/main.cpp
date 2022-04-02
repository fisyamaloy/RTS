#include <iostream>

#include "Factory/LinuxWidgetsFactory.hpp"
#include "Factory/WindowsWidgetsFactory.hpp"

int main()
{
    WindowsWidgetsFactory lwf;
    lwf.createButton()->paint();
    lwf.createCheckBox()->paint();
    lwf.createField()->paint();

    return 0;
}
