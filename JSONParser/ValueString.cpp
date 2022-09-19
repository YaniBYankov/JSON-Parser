#include "ValueString.hpp"

ValueString::ValueString()
{
    this->value="";
    this->string="";
}

ValueString::ValueString(const std::string& string):Value(string)
{
    this->string=string;
}

Value* ValueString::clone() const
{
    return new ValueString(*this);
}

ValueString::ValueString(const ValueString& other)
{
    
    this->copy(other);
}

ValueString& ValueString::operator=(const ValueString &other)
{
    if (this!=&other)
    {
        this->copy(other);
    }
    return *this;
}

ValueString::~ValueString(){}

void ValueString::copy(const ValueString &other)
{
    this->value=other.getValue();
    this->string=other.string;
}
