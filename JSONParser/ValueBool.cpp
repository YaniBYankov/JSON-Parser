#include "ValueBool.hpp"

ValueBool::ValueBool()
{
    this->value="";
    this->boolean="";
}

ValueBool::ValueBool(const std::string& string):Value(string)
{
    this->boolean=string;
}

Value* ValueBool::clone() const
{
    return new ValueBool(*this);
}

ValueBool::ValueBool(const ValueBool& other)
{
    
    this->copy(other);
}

ValueBool& ValueBool::operator=(const ValueBool &other)
{
    if (this!=&other)
    {
        this->copy(other);
    }
    return *this;
}

ValueBool::~ValueBool(){}

void ValueBool::copy(const ValueBool &other)
{
    this->value=other.getValue();
    this->boolean=other.boolean;
}
