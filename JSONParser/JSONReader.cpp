#include "JSONReader.hpp"

void JSONReader::removeSpacesFront(string &string)
{
    while (string[0]==' ')
    {
        string.erase(0, 1);
    }
}

void JSONReader::removeSpacesBack(string &string)
{
    size_t lenght=string.size()-1;
    while (string[0]==' ')
    {
        string.erase(lenght,1);
        lenght--;
    }
}

void JSONReader::removeSpacesIn(string &string)
{
    
    size_t lenght=string.size();
    
    for (size_t i=0;i<lenght;i++)
    {
        if (string[i]=='"')
        {
            ++i;
            while(string[i]!='"'&& i<lenght-1)
            {
                ++i;
                if(string[i]=='\\'&&string[i+1]=='\"')
                {
                    i+=2;
                }
            }
        }
        
        if (string[i]==' ')
        {
            string.erase(i,1);
            --i;
            --lenght;
        }
    }
}

void JSONReader::removeSpaces(string &string)
{
    this->removeSpacesFront(string);
    this->removeSpacesBack(string);
    this->removeSpacesIn(string);
}

string JSONReader::ReadJSON(const string &JSONfilepath)
{
    ifstream read(JSONfilepath,ios::in);
    string currLine;
    string result= "";
    
    if (!read.is_open())
    {
        throw invalid_argument("Invalid file!");
    }
    else
    {
       
        while (getline(read,currLine))
        {
            result+=currLine;
        }
    }
    
    this->removeSpaces(result);
    read.close();
    return result;
}

bool JSONReader::isValid(const string &JSON) const
{
    return this->validation.IsValidJSON(JSON);
}
