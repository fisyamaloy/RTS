#pragma once
#ifdef _WIN32

#include <memory>

#include "WidgetsFactoryAbstract.hpp"
#include "WindowsWidgets/WindowsWidgets.hpp"

class WindowsWidgetsFactory : public WidgetsFactoryAbstract
{
public:
    std::shared_ptr<ButtonAbstract> createButton() const override
    {
        return std::make_shared<WindowsButton>();
    }

    std::shared_ptr<CheckBoxAbstract> createCheckBox() const override
    {
        return std::make_shared<WindowsCheckBox>();
    }

    std::shared_ptr<FieldAbstract> createField() const override
    {
        return std::make_shared<WindowsField>();
    }
};

#endif