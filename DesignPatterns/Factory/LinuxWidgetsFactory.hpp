#pragma once
#include <memory>

#include "LinuxWidgets/LinuxWidgets.hpp"
#include "WidgetsFactoryAbstract.hpp"

class LinuxWidgetsFactory : WidgetsFactoryAbstract
{
public:
    std::shared_ptr<ButtonAbstract> createButton() const override
    {
        return std::make_shared<LinuxButton>();
    }

    std::shared_ptr<CheckBoxAbstract> createCheckBox() const override
    {
        return std::make_shared<LinuxCheckBox>();
    }

    std::shared_ptr<FieldAbstract> createField() const override
    {
        return std::make_shared<LinuxField>();
    }
};
