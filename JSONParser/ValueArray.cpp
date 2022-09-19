#include "ValueArray.hpp"
#include "ValueChar.hpp"
#include "ValueString.hpp"
#include "ValueNumber.hpp"
#include "ValueBool.hpp"
#include "ValueObject.hpp"

ValueArray::ValueArray()
{
    
    this->value="";
}

ValueArray::ValueArray(const std::string& string):Value(string)
{
    std::string element="";
    size_t lenght=string.size();
    bool InArray=false;
    bool InObject=false;
    for (size_t i=1;i<lenght-1;i++)
    {
        while(string.at(i)!=',')
        {
            if (string.at(i)=='['&&InArray==false)
            {
                InArray=true;
                
            }
            if (string.at(i)==']'&&InArray==true)
            {
                InArray=false;
                
            }
            else if (string.at(i)==']'&&InArray==false)
            {
                break;
            }
            if (string.at(i)=='{'&&InObject==false)
            {
                InObject=true;
                
            }
            if (string.at(i)=='}'&&InObject==true)
            {
                InObject=false;
                
            }
           
            element.push_back(string.at(i));
            i++;
            if (string.at(i)==','&&InObject==true)
            {
                element.push_back(string.at(i));
                i++;
            }
        }
        this->array.push_back(element);
        element="";
    }
    
    size_t size=this->array.size();
    std::string Name="";
    std::string Value="";
    for (size_t i=0;i<size;i++)
    {
        Value=array.at(i);
        JSONElement element(Name,Value);
        this->values.push_back(element);
        Value="";
    }
    
}

ValueArray::ValueArray(const ValueArray& other)
{
    this->copy(other);
}

ValueArray& ValueArray::operator=(const ValueArray &other)
{
    if (this!=&other)
    {
        this->values.clear();
        this->copy(other);
    }
    return *this;
}

ValueArray::~ValueArray(){}

Value* ValueArray::clone() const
{
    return new ValueArray(*this);
}

void ValueArray::copy(const ValueArray &other)
{
    this->value=other.getValue();
    size_t size=other.values.size();
    for (size_t i=0;i<size;i++)
    {
        this->values.push_back(other.values.at(i));
    }
}

vector<JSONElement>* ValueArray::GetElements()
{
    return &this->values;
}

void ValueArray::UpdateValue()
{
    this->value="";
    this->value.push_back('[');
    for (size_t i=0;i<this->values.size();i++)
    {
        this->value+=this->values.at(i).getValue();
        if (i<this->values.size()-1)
        {
            value.push_back(',');
        }
    }
    this->value.push_back(']');
}
