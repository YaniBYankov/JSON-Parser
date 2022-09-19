#include "ValueNumber.hpp"

ValueNumber::ValueNumber()
{
    this->value="";
    this->number="";
}

ValueNumber::ValueNumber(const std::string& string):Value(string)
{
    this->number=string;
}

Value* ValueNumber::clone() const
{
    return new ValueNumber(*this);
}

ValueNumber::ValueNumber(const ValueNumber& other)
{
    this->copy(other);
}

ValueNumber& ValueNumber::operator=(const ValueNumber &other)
{
    if (this!=&other)
    {
        this->copy(other);
    }
    return *this;
}

ValueNumber::~ValueNumber(){}

void ValueNumber::copy(const ValueNumber &other)
{
    this->value=other.getValue();
    this->number=other.number;
}
