#include "Value.hpp"

Value::Value()
{
    this->value="";
}

Value::Value(const std::string& value)
{
    this->value=value;
}

std::string Value::getValue() const
{
    return this->value;
}

bool Value::CheckForNestedElements()
{
    return false;
}

void Value::SetValueString(const std::string &ValueString)
{
    this->value=ValueString;
    
}

void Value::SetValue(JSONElement &add)
{
    return;
}

void Value::UpdateValue()
{
    return;
}

vector<JSONElement>* Value::GetElements()
{
    return nullptr;
}

Value::~Value(){}

