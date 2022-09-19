#include "ValueChar.hpp"

ValueChar::ValueChar()
{
    this->value="";
    this->character='\0';
}

ValueChar::ValueChar(const std::string& string):Value(string)
{
    this->character=string.at(1);
}

Value* ValueChar::clone() const
{
    return new ValueChar(*this);
}

ValueChar::ValueChar(const ValueChar& other)
{
    
    this->copy(other);
}

ValueChar& ValueChar::operator=(const ValueChar &other)
{
    if (this!=&other)
    {
        this->copy(other);
    }
    return *this;
}

ValueChar::~ValueChar(){}

void ValueChar::copy(const ValueChar &other)
{
    this->value=other.getValue();
    this->character=other.character;
}
