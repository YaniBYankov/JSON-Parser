#include "JSONElement.hpp"

JSONElement::JSONElement()
{
    this->Name="";
    this->value=nullptr;
}

JSONElement::JSONElement(const string& Name,const string& Value)
{
    
    this->Name=Name;
    
    if (Value.at(0)=='\'')
    {
        ValueChar ValueChar(Value);
        this->value=ValueChar.clone();
    }
    else if (Value.at(0)=='"')
    {
        ValueString ValueString(Value);
        this->value=ValueString.clone();
    }
    else if ((Value.at(0)>='0'&&Value.at(0)<='9')||Value.at(0)=='-')
    {
        ValueNumber ValueNumber(Value);
        this->value=ValueNumber.clone();
    }
    else if(Value.at(0)=='t'||Value.at(0)=='f'||Value.at(0)=='n')
    {
        ValueBool ValueBool(Value);
        this->value=ValueBool.clone();
    }
    else if (Value.at(0)=='[')
    {
        ValueArray ValueArray(Value);
        this->value=ValueArray.clone();
        for (size_t i=0;i<this->GetValue()->GetElements()->size();i++)
        {
            this->GetValue()->GetElements()->at(i).Name=this->Name;
        }
    }
    else if (Value.at(0)=='{')
    {
        ValueObject ValueObject(Value);
        this->value=ValueObject.clone();
    }
    
}

JSONElement::JSONElement(const JSONElement& other)
{
    this->copy(other);
}

JSONElement& JSONElement::operator=(const JSONElement &other)
{
    if (this!=&other)
    {
        delete this->value;
        this->copy(other);
    }
    return *this;
}

bool JSONElement::operator==(const JSONElement &other) const
{
    if (this->getName()==other.getName()&&this->value->getValue()==other.value->getValue())
    {
        return true;
    }
    return false;
}

std::string JSONElement::getName() const
{
    return this->Name;
}

std::string JSONElement::getValue() const
{
    return this->value->getValue();
}

Value* JSONElement::GetValue()
{
    return this->value;
}

void JSONElement::editValue(const std::string& Value)
{
    delete this->value;
    
    if (Value.at(0)=='\'')
    {
        ValueChar ValueChar(Value);
        this->value=ValueChar.clone();
    }
    else if (Value.at(0)=='"')
    {
        ValueString ValueString(Value);
        this->value=ValueString.clone();
    }
    else if ((Value.at(0)>='0'&&Value.at(0)<='9')||Value.at(0)=='-')
    {
        ValueNumber ValueNumber(Value);
        this->value=ValueNumber.clone();
    }
    else if(Value.at(0)=='t'||Value.at(0)=='f'||Value.at(0)=='n')
    {
        ValueBool ValueBool(Value);
        this->value=ValueBool.clone();
    }
    else if (Value.at(0)=='[')
    {
        ValueArray ValueArray(Value);
        this->value=ValueArray.clone();
    }
    else if (Value.at(0)=='{')
    {
        ValueObject ValueObject(Value);
        this->value=ValueObject.clone();
    }
}

void JSONElement::updateValue()
{
    if (this->value->getValue().at(0)=='{'||this->value->getValue().at(0)=='[')
    {
            for (size_t i=0;i<this->value->GetElements()->size();i++)
            {
                this->value->GetElements()->at(i).updateValue();
                this->value->SetValueString(this->value->getValue());
            }
        this->value->UpdateValue();
    }
    else
    {
        this->value->SetValueString(this->value->getValue());
    }
    
    
}

void JSONElement::copy(const JSONElement &other)
{
    this->Name=other.Name;
    this->value=other.value->clone();
}

bool JSONElement::FindElementPath(const vector<std::string>& path,size_t& PathIndex) const
{
    if (this->value->getValue().at(0)=='{')
    {
        for (size_t i=0;i<this->value->GetElements()->size();i++)
        {
            if (this->value->GetElements()->at(i).getName()==path.at(PathIndex))
            {
                PathIndex++;
                if (PathIndex==path.size())
                {
                    return true;
                }
                else
                {
                    return this->value->GetElements()->at(i).FindElementPath(path, PathIndex);

                }
            }
            
        }
    }
    else if (this->value->getValue().at(0)=='[')
    {
        for (size_t i=0;i<this->value->GetElements()->size();i++)
        {
            if (this->value->GetElements()->at(i).GetValue()->GetElements()!=nullptr)
            {
                for (size_t j=0;j<this->value->GetElements()->at(i).GetValue()->GetElements()->size();j++)
                {
                    if (this->value->GetElements()->at(i).GetValue()->GetElements()->at(j).getName()==path.at(PathIndex))
                    {
                        PathIndex++;
                        if (PathIndex==path.size())
                        {
                            return true;
                        }
                        else
                        {
                            return this->value->GetElements()->at(i).GetValue()->GetElements()->at(j).FindElementPath(path, PathIndex);

                        }
                    }
                }
            }
            
        }
    }
    
    return false;
}

void JSONElement::EditByPath(const vector<std::string> &path,const std::string& Value)
{
    size_t PathIndex=1;
    size_t EditIndex=0;
    if (this->value->getValue().at(0)=='{')
    {
        this->EditElementByPathObject(path, EditIndex, PathIndex,Value);
    }
    else if (this->value->getValue().at(0)=='[')
    {
        if (path.size()>2)
        {
            this->EditElementByPathArray(path, EditIndex, PathIndex,Value);
        }
        else if (path.size()==2)
        {
            for (size_t i=0;i<this->GetValue()->GetElements()->size();i++)
            {
                if (this->GetValue()->GetElements()->at(i).GetValue()->GetElements()!=nullptr)
                {
                    for (size_t j=0;j<this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->size();j++)
                    {
                        if (this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->at(j).getName()==path.at(1))
                        {
                            this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->at(j).editValue(Value);
                        }
                    }
                }
            }
        }
    }
}

JSONElement::~JSONElement()
{
    delete this->value;
}

void JSONElement::EditElementByPathArray(const vector<std::string> &path, size_t &EditIndex, size_t &PathIndex,const std::string& Value)
{
        for (size_t i=0;i<this->GetValue()->GetElements()->size();i++)
        {
                if (this->value->GetElements()->at(i).GetValue()->GetElements()!=nullptr)
                {
                    for (size_t j=0;j<this->value->GetElements()->at(i).GetValue()->GetElements()->size();j++)
                    {
                        if (this->value->GetElements()->at(i).GetValue()->GetElements()->at(j).getName()==path.at(PathIndex)&&!(PathIndex==path.size()))
                        {
                            
                            EditIndex=0;
                            PathIndex++;
                            this->value->GetElements()->at(i).GetValue()->GetElements()->at(j).EditElementByPathObject(path, EditIndex, PathIndex, Value);
                            return;
                        }
                    }
                }
        }
    
}

void JSONElement::EditElementByPathObject(const vector<std::string> &path, size_t &EditIndex, size_t &PathIndex,const std::string& Value)
{
    while (PathIndex<path.size())
    {
        for (size_t i=0;i<this->GetValue()->GetElements()->size();i++)
        {
            if(PathIndex==path.size()-1&&this->value->GetElements()->at(i).getName()==path.at(PathIndex))
            {
                this->GetValue()->GetElements()->at(i).editValue(Value);
                this->GetValue()->GetElements()->at(i).value->SetValueString(Value);
                std::string value=this->GetValue()->GetElements()->at(i).getValue();
                PathIndex++;
                break;
            }
            else if (this->GetValue()->getValue().at(0)!='['&&this->GetValue()->GetElements()->at(i).getName()==path.at(PathIndex)&&!(PathIndex==path.size()-1))
            {
                    EditIndex=i;
                    PathIndex++;
                    this->GetValue()->GetElements()->at(i).EditElementByPathObject(path, EditIndex, PathIndex,Value);
            }
            else if (this->GetValue()->getValue().at(0)=='[')
            {
                EditIndex=i;
                if (PathIndex==path.size()-1)
                {
                    for (size_t j=0;j<this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->size();j++)
                    {
                        if (this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->at(j).getName()==path.at(PathIndex))
                        {
                            this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->at(j).editValue(Value);
                            PathIndex++;
                        }
                    }
                }
                else if (PathIndex<path.size()-1)
                {
                    this->GetValue()->GetElements()->at(i).EditElementByPathArray(path, EditIndex, PathIndex,Value);
                }
            }
        }
    }
    
}

void JSONElement::RemoveByPathObject(const vector<std::string> &path, size_t &PathIndex)
{
    while (PathIndex<path.size())
    {
        for (size_t i=0;i<this->GetValue()->GetElements()->size();i++)
        {
            if (this->value->getValue().at(0)=='{')
            {
                if(PathIndex==path.size()-1&&this->value->GetElements()->at(i).getName()==path.at(PathIndex))
                {
                    for (size_t j=i;j<this->value->GetElements()->size()-1;j++)
                    {
                        JSONElement temp=this->value->GetElements()->at(j);
                        this->value->GetElements()->at(j)=this->value->GetElements()->at(j+1);
                        this->value->GetElements()->at(j+1)=temp;
                        
                    }
                    this->value->GetElements()->pop_back();
                    PathIndex++;
                    return;
                }
                else
                {
                    if(this->GetValue()->GetElements()->at(i).getName()==path.at(PathIndex)&&!(PathIndex==path.size()-1))
                    {
                        PathIndex++;
                        this->GetValue()->GetElements()->at(i).RemoveByPathObject(path, PathIndex);
                    }
                }
            }
            if (this->value->getValue().at(0)=='[')
            {
                for (size_t j=0;j<this->GetValue()->GetElements()->size();j++)
                {
                    for (size_t k=0;k<this->GetValue()->GetElements()->at(j).GetValue()->GetElements()->size();k++)
                    {
                        if (this->GetValue()->GetElements()->at(j).GetValue()->GetElements()->at(k).getName()==path.at(PathIndex)&&PathIndex!=path.size()-1)
                        {
                            this->GetValue()->GetElements()->at(j).GetValue()->GetElements()->at(k).RemoveByPathArray(path, PathIndex);
                        }
                        else if (this->GetValue()->GetElements()->at(j).GetValue()->GetElements()->at(k).getName()==path.at(PathIndex)&&PathIndex==path.size()-1)
                        {
                            for (size_t t=k; t<this->GetValue()->GetElements()->at(j).GetValue()->GetElements()->size()-1;t++)
                            {
                                JSONElement temp(this->GetValue()->GetElements()->at(j).GetValue()->GetElements()->at(t));
                                this->GetValue()->GetElements()->at(j).GetValue()->GetElements()->at(t)=this->GetValue()->GetElements()->at(j).GetValue()->GetElements()->at(t+1);
                                this->GetValue()->GetElements()->at(j).GetValue()->GetElements()->at(t+1)=temp;
                            }
                            this->GetValue()->GetElements()->at(j).GetValue()->GetElements()->pop_back();
                            PathIndex++;
                            return;
                        }
                    }
                    
                }
            }
        }
        
    }
}

void JSONElement::RemoveByPathArray(const vector<std::string> &path, size_t &PathIndex)
{
    for (size_t i=0;i<this->GetValue()->GetElements()->size();i++)
    {
        if (this->GetValue()->GetElements()->at(i).getValue().at(0)=='{')
        {
            for (size_t j=0;j<this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->size();j++)
            {
                if (this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->at(j).getName()==path.at(PathIndex))
                {
                    if (path.size()-PathIndex>1)
                    {
                        PathIndex++;
                        this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->at(j).RemoveByPathObject(path, PathIndex);
                        return;
                    }
                    else if (path.size()-PathIndex==1)
                    {
                        for (size_t k=j;k<this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->size()-1;k++)
                        {
                            JSONElement temp(this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->at(k));
                            this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->at(k)=this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->at(k+1);
                            this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->at(k+1)=temp;
                        }
                        this->GetValue()->GetElements()->at(i).GetValue()->GetElements()->pop_back();
                    }
                    
                }
            }
        }
        else if (this->GetValue()->GetElements()->at(i).getValue().at(0)=='[')
        {
            this->GetValue()->GetElements()->at(i).RemoveByPathArray(path, PathIndex);
        }
    }
}

void JSONElement::SearchByPath(const vector<std::string> &path, size_t &PathIndex,vector<JSONElement>& Searched)
{
    while (PathIndex<path.size())
    {
        for (size_t i=0;i<this->GetValue()->GetElements()->size();i++)
        {
            if(PathIndex==path.size()-1&&this->value->GetElements()->at(i).getName()==path.at(PathIndex))
            {
                PathIndex++;
                Searched.push_back(this->value->GetElements()->at(i)) ;
            }
            else
            {
                if(this->GetValue()->GetElements()->at(i).getName()==path.at(PathIndex)&&!(PathIndex==path.size()-1))
                {
                    PathIndex++;
                    this->GetValue()->GetElements()->at(i).SearchByPath(path, PathIndex,Searched);
                }
            }
        }
        
    }
}

void JSONElement::CreateByPath(const vector<std::string> &path, const std::string &value, size_t &PathIndex)
{
    while (PathIndex<path.size())
    {
        if (PathIndex==path.size()-1)
        {
            
            JSONElement element(path.at(PathIndex),value);
            this->value->SetValue(element);
            PathIndex++;
        }
        else
        {
            JSONElement element(path.at(PathIndex),"{}");
            this->value->SetValue(element);
            PathIndex++;
            this->value->GetElements()->at(0).CreateByPath(path, value, PathIndex);
        }
    }
    
    
}

size_t JSONElement::CountAllElements(size_t &Cnt)
{
    size_t size=this->GetValue()->GetElements()->size();
    for (size_t i=0;i<size;i++)
    {
        Cnt++;
        if (this->GetValue()->GetElements()->at(i).value->GetElements())
        {
            Cnt=this->GetValue()->GetElements()->at(i).CountAllElements(Cnt);
        }
    }
    return Cnt;
}

void JSONElement::Print(ostream &out) const
{
    out<<this->getName();
    out<<':';
    out<<this->getValue();

}

void JSONElement::CallPrintWithSpaces(ostream &out) const
{
        size_t TabIndex=0;
        this->PrintWithSpaces(out, TabIndex);
}

void JSONElement::PrintWithSpaces(ostream &out, size_t &TabIndex) const
{
    if (this->value->GetElements()==nullptr)
    {
        out<<this->getName();
        out<<':';
        out<<this->getValue();
        out<<',';
        out<<'\n';
    }
    else if(this->value->GetElements()!=nullptr)
    {
        out<<this->getName();
        out<<':';
        out<<'{';
        out<<'\n';
        TabIndex+=this->getName().size();
        TabIndex+=2;
        size_t TabIndexNext=TabIndex;
        if (this->value->GetElements()->size()==1)
        {
            for (size_t i=0;i<TabIndex;i++)
            {
                out<<" ";
            }
            out<<this->value->GetElements()->at(    0).getName();
            out<<':';
            out<<this->value->GetElements()->at(0).getValue();
            out<<'\n';
        }
        else if (!this->value->CheckForNestedElements())
        {
            size_t size=this->value->GetElements()->size();
            for (size_t i=0;i<size;i++)
            {
                for (size_t i=0;i<TabIndex;i++)
                {
                    out<<" ";
                }
                out<<this->value->GetElements()->at(i).getName();
                out<<':';
                out<<this->value->GetElements()->at(i).getValue();
                if(i<size-1)
                {
                    out<<',';
                }
                out<<'\n';
            }
        }
        else
        {
            for (size_t i=0;i<this->value->GetElements()->size();i++)
            {
                for (size_t i=0;i<TabIndex;i++)
                {
                    out<<" ";
                }
                this->value->GetElements()->at(i).PrintWithSpaces(out,TabIndexNext);
            }
        }
        
        for (size_t i=0;i<TabIndex;i++)
        {
            out<<" ";
        }
        out<<'}';
        out<<'\n';
    }
    
}


