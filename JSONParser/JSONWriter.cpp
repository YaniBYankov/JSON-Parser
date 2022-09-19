#include "JSONWriter.hpp"

void JSONWriter::WriteWithoutSpaces(const std::string &JSONFilePath,const vector<JSONElement>& elements,int from,int to) const
{
    std::ofstream out(JSONFilePath,ios::out);
    if (!out.is_open())
    {
        throw invalid_argument("Couldn't open file to save in!");
        return;
    }
    out<<'{';
    for (size_t i=from;i<to;i++)
    {
        out<<elements.at(i).getName();
        out<<':';
        out<<elements.at(i).getValue();
        if (i<to-1)
        {
            out<<',';
        }
    }
    out<<'}';
    out.close();
}

void JSONWriter::WriteWithSpaces(const std::string &JSONFilePath,const vector<JSONElement>& elements,int from,int to) const
{
    std::ofstream out(JSONFilePath,ios::out);
    if (!out.is_open())
    {
        throw invalid_argument("Couldn't open file to save in!");
        return;
    }
    out<<'{';
    out<<'\n';
    for (size_t i=from;i<to;i++)
    {
        if (elements.at(i).getValue().at(0)=='{')
        {
            elements.at(i).CallPrintWithSpaces(out);
        }
        else
        {
            elements[i].Print(out);
        }
        
        if (i<to-1)
        {
            out<<',';
            out<<'\n';
        }
    }
    out<<'\n';
    out<<'}';
    out.close();
}
