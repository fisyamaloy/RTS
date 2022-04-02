#include <iostream>

#include "Factory/WindowsWidgetsFactory.hpp"

int main()
{
    WindowsWidgetsFactory lwf;
    lwf.createButton()->paint();
    lwf.createCheckBox()->paint();
    lwf.createField()->paint();

    return 0;
}
