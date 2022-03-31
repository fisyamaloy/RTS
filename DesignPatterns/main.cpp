#include <iostream>

#include "Factory/LinuxWidgetsFactory.hpp"
#include "Factory/WindowsWidgetsFactory.hpp"

int main()
{
    LinuxWidgetsFactory lwf;

    lwf.createButton()->paint();
    lwf.createCheckBox()->paint();
    lwf.createField()->paint();

    return 0;
}
