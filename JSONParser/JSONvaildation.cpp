#include "JSONvaildation.hpp"

bool JSONvalidation::isValidName(const string &JSON, size_t lenght, size_t& index) const
{
    size_t NameLenght=0;
    
    if(JSON[index]==',')
    {
        index++;
    }
    if (JSON[index]!='"')
    {
        throw invalid_argument ("There is an object with invalid name that must start with opening string bracket!");
        return false;
    }
    index++;
    
    while(JSON[index]!='"'&&index<lenght)
    {
        ++index;
        NameLenght++;
    }
    if (NameLenght==lenght-2)
    {
        throw invalid_argument ("Ther is an object with invalid name that must finnish with closing string bracket!");
        return false;
    }
    else if(NameLenght==0)
    {
        throw invalid_argument ("There is an object with invalid name that must not be empty string!");
        return false;
    }
    return true;
}

bool JSONvalidation::isValidChar(const string &JSON, size_t lenght, size_t &index) const
{
    if (JSON[index]=='\'')
    {
        index++;
    }
    if(JSON[index+1]=='\''&&index<lenght)
    {
        index+=2;
    }
    if (JSON[index]!=','&&JSON[index]!=']'&&JSON[index]!='}'&&index!=lenght)
    {
        throw invalid_argument("Invalid character since there is no \",\" , \"]\" or \"}\"!");
        return false;
    }
    return true;
}

bool JSONvalidation::isValidString(const string &JSON, size_t lenght, size_t& index) const
{
    if (JSON[index]=='"')
    {
        index++;
    }
    while (JSON[index]!='"'&&index<lenght)
    {
        index++;
    }
    
    if (index+1==lenght)
    {
        throw invalid_argument("Invalid string since there are no closing quotation marks!");
        return false;
    }
    else if (JSON[index+1]!=','&&JSON[index+1]!=']'&&JSON[index+1]!='}')
    {
        throw invalid_argument("Invalid string since there is no \",\" , \"]\" or \"}\"!");
        return false;
    }
    else
    {
        return true;
    }
}

bool JSONvalidation::isValidNumber(const string &JSON, size_t lenght, size_t& index) const
{
    bool dot=false;
    if (JSON[index]=='-'||(JSON[index]>='0'&&JSON[index]<='9'))
    {
        index++;
        while ((JSON[index]>='0'&&JSON[index]<='9')||(JSON[index]=='.'&&dot==false))
        {
            index++;
        }
        if (JSON[index]!=','&&JSON[index]!=']'&&JSON[index]!='}'&&index!=lenght)
        {
            throw invalid_argument("Invalid number since there is no \",\" , \"]\" or \"}\"!");
            return false;
        }
    }
    return true;
}

bool JSONvalidation::isValidArray(const string &JSON, size_t lenght, size_t& index) const
{
    bool HasAnyValue=false;
    bool valid=true;
    index++;
    if (JSON.at(index)=='[')
    {
        return false;
    }
    while (JSON.at(index)!=']'&&index!=lenght-1)
    {
        HasAnyValue=true;
        try {
            if (isValidValue(JSON, lenght, index))
            {
                if (JSON.at(index)=='"')
                {
                    index++;
                }

               if (JSON[index]==',')
               {
                   index++;
               }
               else if (JSON[index]==']')
               {
                   if(index==lenght-1)
                   {
                       continue;
                   }
                   else if(JSON[index+1]==']')
                   {
                       while(index<lenght&&JSON[index+1]==']')
                       {
                           index++;
                       }
                       continue;
                   }
               }
               else
               {
                   valid=false;
               }
            }
        } catch (const invalid_argument& e) {
            throw e;
        }
    }
    
    if(valid&&HasAnyValue)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool JSONvalidation::isValidBool(const string &JSON, size_t lenght, size_t &index) const
{
    
    if (JSON[index]=='t'&&JSON[index+1]=='r'&&JSON[index+2]=='u'&&JSON[index+3]=='e')
    {
        index+=4;
        if (JSON[index]==','||JSON[index]==']'||JSON[index]=='}')
        {
            return true;
        }
        else
        {
            throw invalid_argument("Invalid bool value since there is no \",\" , \"]\" or \"}\"!");
            return false;
        }
    }
    else if (JSON[index]=='f'&&JSON[index+1]=='a'&&JSON[index+2]=='l'&&JSON[index+3]=='s'&&JSON[index+4]=='e')
    {
        index+=5;
        if (JSON[index]==','||JSON[index]==']'||JSON[index]=='}')
        {
            return true;
        }
        else
        {
            throw invalid_argument("Invalid bool value since there is no \",\" , \"]\" or \"}\"!");
            return false;
        }
    }
    else if (JSON[index]=='n'&&JSON[index+1]=='u'&&JSON[index+2]=='l'&&JSON[index+3]=='l')
    {
        index+=4;
        if (JSON[index]==','||JSON[index]==']'||JSON[index]=='}')
        {
            return true;
        }
        else
        {
            throw invalid_argument("Invalid bool value since there is no \",\" , \"]\" or \"}\"!");
            return false;
        }
    }
    else
    {
        throw invalid_argument("Invalid bool value!");
        return false;
    }
}

string JSONvalidation::getObject(const string &JSON, size_t lenght, size_t &index) const
{
    string object="";
    if (JSON.at(index)=='{')
    {
        object.push_back('{');
    }
    
    index++;
    
    bool inString=false;
    
    size_t openingBracket=1;
    size_t closingBracket=0;
    
    while (openingBracket!=closingBracket&&index!=lenght)
    {
        if (JSON[index]=='"'&&inString==false)
        {
            inString=true;
        }
        if (JSON[index]=='"'&&inString==true)
        {
            inString=false;
        }
        if (JSON[index]=='{'&&inString==false)
        {
            openingBracket++;
        }
        if(JSON[index]=='}'&&inString==false)
        {
            closingBracket++;
        }
        object.push_back(JSON[index]);
        index++;
        
        if (JSON.at(index)=='}'&&openingBracket==closingBracket)
        {
            index--;
        }
    }
    return object;
}

bool JSONvalidation::isValidValue(const string &JSON, size_t lenght, size_t& index) const
{
    bool valid=false;
    
    if (JSON[index]=='\'')
    {
        try
        {
            if (this->isValidChar(JSON, lenght, index))
            {
                valid=true;
            }
        }
        catch (const invalid_argument& e)
        {
            throw e;
        }
    }
    else if (JSON[index]=='"')
    {
        try
        {
            if (this->isValidString(JSON, lenght,index))
            {
                valid=true;
            }
        }
        catch (const invalid_argument& e)
        {
            throw e;
        }
    }
    else if (JSON[index]=='-'||(JSON[index]>='0'&&JSON[index]<='9'))
    {
        try
        {
            if (this->isValidNumber(JSON, lenght, index))
            {
                valid=true;
            }
        }
        catch (const invalid_argument& e)
        {
            throw e;
        }
    }
    else if (JSON[index]=='[')
    {
        try
        {
            if (this->isValidArray(JSON, lenght, index))
            {
                valid=true;
            }
        }
        catch (const invalid_argument& e)
        {
            throw e;
        }
    }
    else if (JSON[index]=='t'||JSON[index]=='f'||JSON[index]=='n')
    {
        try
        {
            if (this->isValidBool(JSON, lenght, index))
            {
                valid=true;
            }
        }
        catch (const invalid_argument& e)
        {
            throw e;
        }
    }
    else if(JSON[index]=='{')
    {
        string object=this->getObject(JSON, lenght, index);
        valid=this->IsValidJSON(object);
        //index++;
    }
    else
    {
        throw invalid_argument("Invalid value!");
    }
    return valid;
}

bool JSONvalidation::IsValidJSON(const string &JSON) const
{
    if(!(JSON.size()>0))
    {
        throw invalid_argument ("This is empty file!");
        
    }
    else
    {
        size_t lenght=JSON.size();
        if(JSON.front()!='{'||JSON.back()!='}')
        {
            throw invalid_argument ("JSON file is invalid since there is no \"{\" or \"}\"!");
            return false;
        }
        if (lenght==2)
        {
            return true;
        }
        for (size_t i=1;i<lenght-1;i++)
        {
            bool Name=false;
            bool Value=false;
            
            try
            {
                Name=this->isValidName(JSON, lenght, i);
                if (Name==false)
                {
                    throw invalid_argument("JSON file has an object with invalid name!");
                    return false;
                }
            }
            catch (const invalid_argument& e)
            {
                throw e;
            }
            i++;
            if(JSON.at(i)!=':')
            {
                throw invalid_argument("JSON file is missing \":\" between name and it's value!");
            }
            else
            {
                i++;
            }
            try
            {
                Value=this->isValidValue(JSON, lenght, i);
                if (Value==false)
                {
                    throw invalid_argument("JSON file has an object with invalid value!");
                    return false;
                }
            }
            catch (const invalid_argument& e)
            {
                throw e;
            }
        }
        return true;
    }
    return false;
}

