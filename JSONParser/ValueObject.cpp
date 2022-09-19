#include "ValueObject.hpp"

ValueObject::ValueObject()
{
    this->value="";
}



ValueObject::ValueObject(const std::string& string):Value(string)
{
    size_t lenght=string.size();
    std::string Name="";
    std::string Value="";
    for (size_t i=1;i<lenght-1;i++)
    {
        while (string.at(i)!=':')
        {
            Name.push_back(string.at(i));
            i++;
        }
        i++;
        if (string.at(i)!='['&&string.at(i)!='{')
        {
            while(string.at(i)!=','&&string.at(i)!='}')
            {
                Value.push_back(string.at(i));
                ++i;
            }
        }
        else
        {
            if (string.at(i)=='[')
            {
                size_t OpeningSQBracket=1;
                size_t ClosinSQBracket=0;
                Value.push_back('[');
                ++i;
                while(OpeningSQBracket!=ClosinSQBracket)
                {
                    if (string.at(i)=='[')
                    {
                        OpeningSQBracket++;
                    }
                    if (string.at(i)==']')
                    {
                        ClosinSQBracket++;
                    }
                    Value.push_back(string.at(i));
                    ++i;
                }
            }
            if (string.at(i)=='{')
            {
                size_t OpeningBracket=1;
                size_t ClosinBracket=0;
                Value.push_back('{');
                ++i;
                while(OpeningBracket!=ClosinBracket)
                {
                    if (string.at(i)=='{')
                    {
                        OpeningBracket++;
                    }
                    if (string.at(i)=='}')
                    {
                        ClosinBracket++;
                    }
                    Value.push_back(string.at(i));
                    i++;
                }
            }

        }
        JSONElement element(Name,Value);
        this->elements.push_back(element);
        Name="";
        Value="";
    }
}

ValueObject::ValueObject(const ValueObject& other)
{
    this->copy(other);
}

ValueObject& ValueObject::operator=(const ValueObject &other)
{
    if (this!=&other)
    {
        this->elements.clear();
        this->copy(other);
    }
    return *this;
}

ValueObject::~ValueObject(){}

Value* ValueObject::clone() const
{
    return new ValueObject(*this);
}

void ValueObject::UpdateValue()
{
    this->value="";
    this->value.push_back('{');
    for (size_t i=0;i<this->elements.size();i++)
    {
        this->value+=this->elements.at(i).getName();
        this->value.push_back(':');
        this->value+=this->elements.at(i).getValue();
        if (i!=this->elements.size()-1)
        {
            this->value.push_back(',');
        }
    }
    this->value.push_back('}');
}

void ValueObject::SetValue(JSONElement &add)
{
    this->elements.push_back(add);
}

vector<JSONElement>* ValueObject::GetElements()
{
    return &this->elements;
}

void ValueObject::copy(const ValueObject &other)
{
    this->value=other.getValue();
    size_t size=other.elements.size();
    for (size_t i=0;i<size;i++)
    {
        this->elements.push_back(other.elements[i]);
    }
}

bool ValueObject::CheckForNestedElements()
{
    size_t size=this->elements.size();
    for (size_t i=0;i<size;i++)
    {
        if (this->elements.at(i).GetValue()->GetElements()!=nullptr)
        {
            return true;
        }
    }
    return false;
}
