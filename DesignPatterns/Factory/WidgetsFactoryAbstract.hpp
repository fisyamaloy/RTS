#pragma once
#include <memory>

#include "WidgetsAbstract/ButtonAbstract.hpp"
#include "WidgetsAbstract/CheckBoxAbstract.hpp"
#include "WidgetsAbstract/FieldAbstract.hpp"

class WidgetsFactoryAbstract
{
public:
    virtual ~WidgetsFactoryAbstract() = default;

    virtual std::shared_ptr<ButtonAbstract>   createButton() const   = 0;
    virtual std::shared_ptr<CheckBoxAbstract> createCheckBox() const = 0;
    virtual std::shared_ptr<FieldAbstract>    createField() const    = 0;
};
