#include "JSONContainer.hpp"

JSONContainer::JSONContainer()
{
    this->JSONFilePath="";
    this->JSON="";
}

void JSONContainer::JSONContainerFill(const string& JSONFilePath)
{
    string JSON="";
    
    JSON=this->reader.ReadJSON(JSONFilePath);
    try
    {
        if (this->reader.isValid(JSON))
        {
            this->JSON=JSON;
            this->JSONFilePath=JSONFilePath;
            this->setJSON();
        }
    }
    catch (const invalid_argument& e)
    {
        throw e;
    }
}

void JSONContainer::setJSON()
{
    size_t lenght=this->JSON.size();
    bool setName=false;
    bool setValue=false;
    std::string Name="";
    std::string Value="";
    for (size_t i=1;i<lenght-1;i++)
    {
        if(setName==false&&setValue==false)
        {
            Name.push_back(this->JSON.at(i));
            ++i;
            while(this->JSON.at(i)!='"')
            {
                Name.push_back(this->JSON.at(i));
                ++i;
            }
            Name.push_back(this->JSON.at(i));
            setName=true;
            ++i;
        }
        else if (setName==true&&setValue==false)
        {
            if (this->JSON.at(i)!='['&&this->JSON.at(i)!='{')
            {
                while(this->JSON.at(i)!=','&&i<lenght-1)
                {
                    Value.push_back(this->JSON.at(i));
                    ++i;
                }
                setValue=true;
            }
            else
            {
                if (this->JSON.at(i)=='[')
                {
                    size_t OpeningSQBracket=1;
                    size_t ClosinSQBracket=0;
                    Value.push_back('[');
                    ++i;
                    while(OpeningSQBracket!=ClosinSQBracket)
                    {
                        if (this->JSON.at(i)=='[')
                        {
                            OpeningSQBracket++;
                        }
                        if (this->JSON.at(i)==']')
                        {
                            ClosinSQBracket++;
                        }
                        Value.push_back(this->JSON.at(i));
                        ++i;
                    }
                    setValue=true;
                }
                if (this->JSON.at(i)=='{')
                {
                    size_t OpeningBracket=1;
                    size_t ClosinBracket=0;
                    Value.push_back('{');
                    ++i;
                    while(OpeningBracket!=ClosinBracket)
                    {
                        if (this->JSON.at(i)=='{')
                        {
                            OpeningBracket++;
                        }
                        if (this->JSON.at(i)=='}')
                        {
                            ClosinBracket++;
                        }
                        Value.push_back(this->JSON.at(i));
                        i++;
                    }
                    setValue=true;
                }
                
            }
        }
        if (setName==true&&setValue==true)
        {
            setName=false;
            setValue=false;
            JSONElement element(Name,Value);
            this->JSONElements.push_back(element);
            Name="";
            Value="";
        }
    }
}


size_t JSONContainer::CountAllJSONElements()
{
    size_t Cnt=0;
    for (Iterator it=this->begin();it!=this->end();++it)
    {
        Cnt++;
        if (it.operator*().GetValue()->GetElements())
        {
            Cnt=it.operator*().CountAllElements(Cnt);
        }
    }
    return Cnt;
}

void JSONContainer::print() const
{
    if (this->JSONElements.size()==0)
    {
        throw invalid_argument("JSON file is empty!");
        return;
    }
    cout<<'{';
    cout<<'\n';
    size_t lenght=this->JSONElements.size();
    for (size_t i=0;i<lenght;i++)
    {
        if (this->JSONElements.at(i).getValue().at(0)=='{')
        {
            this->JSONElements.at(i).CallPrintWithSpaces(cout);
        }
        else
        {
            this->JSONElements[i].Print(cout);
        }
        
        if (i<lenght-1)
        {
            cout<<',';
            cout<<'\n';
        }
    }
    cout<<'\n';
    cout<<'}';
    cout<<'\n';
}

void JSONContainer::printsearched() const
{
    size_t size=this->Searched.size();
    if (size==0)
    {
        throw invalid_argument("There are no searched elements!");
        return;
    }
    for (size_t i=0;i<size;i++)
    {
        if (this->Searched[i].getValue().at(0)=='{')
        {
            this->Searched[i].CallPrintWithSpaces(cout);
        }
        else
        {
            this->Searched[i].Print(cout);
        }
        cout<<'\n';
    }
}

void JSONContainer::printsearchedat(const size_t index) const
{
    if (this->Searched.size()==0)
    {
        throw invalid_argument("There are no searched elements!");
        return;
    }
    if (index>=this->Searched.size())
    {
        throw invalid_argument("Index out of bounds!");
        return;
    }
    this->Searched.at(index).Print(cout);
}

void JSONContainer::savesearched(const std::string &FilePath) const
{
    std::ofstream out(FilePath,ios::out);
    if (!out.is_open())
    {
        throw invalid_argument("Couldn't open file to save in!");
        return;
    }
    size_t size=this->Searched.size();
    if (size==0)
    {
        throw invalid_argument("There are no searched elements!");
        return;
    }
    for (size_t i=0;i<size;i++)
    {
        if (this->Searched.at(i).getValue().at(0)=='{')
        {
            this->Searched.at(i).CallPrintWithSpaces(out);
        }
        else
        {
            this->Searched.at(i).Print(out);
        }
        out<<'\n';
    }
    
}

void JSONContainer::savesearchedat(const std::string &FilePath, const size_t index) const
{
    std::ofstream out(FilePath,ios::out);
    if (!out.is_open())
    {
        throw invalid_argument("Couldn't open file to save in!");
        return;
    }
    if (this->Searched.size()==0)
    {
        throw invalid_argument("There are no searched elements!");
        return;
    }
    if (index>=this->Searched.size())
    {
        throw invalid_argument("Index out of bounds!");
        return;
    }
    this->Searched.at(index).Print(out);
    
}

void JSONContainer::UpdateValue()
{
    for (Iterator it=this->begin();it!=this->end();++it)
    {
        it.operator*().updateValue();
    }
}

bool JSONContainer::FindElementByPath(const std::string &element)
{
    vector<std::string>path=this->GetPath(element);
    
for (Iterator it=this->begin();it!=this->end();++it)
{
    if (it.operator*().getName()==path[0])
    {
        if (it.operator*().getValue().at(0)=='{')
        {
            size_t PathIndex=1;
            return it.operator*().FindElementPath(path,PathIndex);
        }
        else if (it.operator*().getValue().at(0)=='[')
        {
            size_t PathIndex=1;
            return it.operator*().FindElementPath(path,PathIndex);
        }
        return true;
    }
}
return false;
}

bool JSONContainer::FindElement(const std::string &element)
{
    for (Iterator it=this->begin();it!=this->end();++it)
    {
        if (it.operator*().getName()==element)
        {
            return true;
        }
    }
    return false;
}

vector<std::string> JSONContainer::GetPath(const std::string &element)
{
    
    std::string Name=element;
    if (Name=="")
    {
        throw invalid_argument("Invalid name path!");
    }
        reader.removeSpaces(Name);
        size_t lenghtName=Name.size();
    if(Name.at(0)!='"'||Name.at(lenghtName-1)!='"')
    {
        throw invalid_argument("Invalid name path!");
    }
        vector<std::string>path;
    
        for (size_t i=1;i<lenghtName-1;i++)
        {
            std::string temp="";
            temp.push_back('\"');
            while (Name.at(i)!='\"')
            {
                temp.push_back(Name.at(i));
                i++;
            }
            temp.push_back('\"');
            path.push_back(temp);
            i++;
        }
    return path;
}

void JSONContainer::EditByPath(const std::string &element,const std::string& Value)
{
    vector<std::string> path;
    try {
        path=this->GetPath(element);
    }
    catch (const invalid_argument& e)
    {
        throw e;
    }
    
    if (path.size()==1)
    {
        bool found=false;
        size_t index=0;
        
        for (Iterator it=this->begin();it!=this->end();++it)
        {
            if (it.operator*().getName()==element)
            {
                index=this->getIndex(it.operator*().getName());
                found=true;
            }
        }
        if (!found)
        {
            throw invalid_argument("There is no such element!");
            return;
        }
        else
        {
                this->JSONElements.at(index).editValue(Value);
        }
        return;
    }
    
    if (!this->FindElementByPath(element))
        {
            throw invalid_argument("Couldn't find element with this path!");
            return;
        }
    
    for (Iterator it=this->begin();it!=this->end();++it)
        {
            if (it.operator*().getName()==path[0])
            {
                if (it.operator*().getValue().at(0)=='{')
                {
                    it.operator*().EditByPath(path,Value);
                }
                else if (it.operator*().getValue().at(0)=='[')
                {
                    it.operator*().EditByPath(path,Value);
                }
            }
        }
}

size_t JSONContainer::getIndex(const std::string& name)
{
    size_t index=0;
    for (Iterator it=this->begin();it!=this->end();++it)
    {
        if (it.operator*().getName()==name)
        {
            return index;
        }
            index++;
    }
    return index;
}

void JSONContainer::edit(const std::string &element, const std::string& value)
{
    if(this->JSONElements.size()==0)
    {
        throw invalid_argument("There aren't any elements!");
        return;
    }
    
    JSONvalidation validate;
    bool valid=false;
    size_t zero=0;
    if (value.at(zero)=='{')
    {
        valid=validate.IsValidJSON(value);
    }
    else
    {
        string temp="{\"Name\":";
        temp=temp+value;
        temp.push_back('}');
        try
        {
            valid=validate.IsValidJSON(temp);
        }
        catch (const invalid_argument& e)
        {
            throw invalid_argument("Couldn't edit because the value is invalid!");
        }
        
    }
    if (!valid)
    {
        throw invalid_argument("Couldn't edit because the value is invalid!");
        return;
    }
    
    try
    {
        this->EditByPath(element, value);
    }
    catch (const invalid_argument& e)
    {
        throw e;
    }
    
    
    this->UpdateValue();
}

void JSONContainer::RemoveByPath(vector<std::string>& path,size_t& PathIndex)
{
   
    for (Iterator it=this->begin();it!=this->end();++it)
    {
        if (it.operator*().getName()==path.at(0))
        {
            if (it.operator*().getValue().at(0)=='{')
            {
                PathIndex++;
                it.operator*().RemoveByPathObject(path, PathIndex);
            }
            else if(it.operator*().getValue().at(0)=='[')
            {
                PathIndex++;
                it.operator*().RemoveByPathArray(path, PathIndex);
            }
        }
    }
    
}

void JSONContainer::remove(const std::string &element)
{
    vector<std::string> path=this->GetPath(element);
    size_t PathSize=path.size();
    
    if (PathSize==1)
    {
        if (!this->FindElement(path.at(0)))
        {
            throw invalid_argument("Couldn't remove this element since it is not found!");
            return;
        }
            size_t from=0;
            size_t lenght=this->JSONElements.size();
            for (size_t i=0;i<lenght;i++)
            {
                if (this->JSONElements[i].getName()==path.at(0))
                {
                    from=i;
                }
            }
            for (size_t i=from;i<lenght-1;i++)
            {
                JSONElement temp=this->JSONElements.at(i);
                this->JSONElements.at(i)=this->JSONElements.at(i+1);
                this->JSONElements.at(i+1)=temp;
            }
            this->JSONElements.pop_back();
        return;
    }
    if (PathSize>1)
    {
        if (!this->FindElementByPath(element))
        {
            throw invalid_argument("Couldn't remove this element since it is not found!");
            return;
        }
        size_t PathIndex=0;
        
        this->RemoveByPath(path, PathIndex);
        
    }
    this->UpdateValue();
}

void JSONContainer::CreateByPath(vector<std::string> &path, const std::string &Value, size_t &PathIndex)
{
    JSONElement element(path.at(0),"{}");
    
    PathIndex++;
    element.CreateByPath(path,Value,PathIndex);
    this->JSONElements.push_back(element);
}

void JSONContainer::create(const std::string &name, const std::string &value)
{
    vector<std::string> path=this->GetPath(name);
    std::string Name=path.at(path.size()-1);
    std::string object="";
    
    object.push_back('{');
    object=object+Name;
    object.push_back(':');
    object=object+value;
    object.push_back('}');
    JSONvalidation validate;
    if(value.at(0)=='{')
    {
        try
        {
            if (!validate.IsValidJSON(value))
            {
                throw invalid_argument("Couldn't create element since it has invalid value!");
                return;
            }
        }
        catch (const invalid_argument& e)
        {
            throw e;
        }
    }
    try
    {
        validate.IsValidJSON(object);
    }
    catch (const invalid_argument& e)
    {
        throw invalid_argument("Couldn't create element since it is invalid!");
    }
    if(path.size()==1)
    {
        JSONElement element(Name,value);
        
        
        for (Iterator it=this->begin();it!=this->end();++it)
        {
            if (it.operator*()==element)
            {
                throw invalid_argument("This element already exists!");
                return;
            }
        }
        this->JSONElements.push_back(element);
        return;
    }
    
    if (path.size()>1)
    {
            if(this->FindElementByPath(name))
            {
                throw invalid_argument("This element already exists!");
                return;
            }
        size_t PathIndex=0;
        this->CreateByPath(path,value,PathIndex);
    }
    this->UpdateValue();
}

void JSONContainer::SearchByPath(vector<std::string> &path, size_t &PathIndex)
{
    for (Iterator it=this->begin();it!=this->end();++it)
    {
        if (it.operator*().getName()==path.at(0))
        {
            PathIndex++;
            it.operator*().SearchByPath(path, PathIndex, this->Searched);
        }
    }
}


void JSONContainer::search(const std::string &key)
{
    vector<std::string> path=this->GetPath(key);
    
    if(path.size()==1)
    {
        if(!this->FindElement(key))
        {
            throw invalid_argument("There is no element under this key!");
            return;
        }
       
        for (Iterator it=this->begin();it!=this->end();++it)
        {
            if (it.operator*().getName()==key)
            {
                this->Searched.push_back(it.operator*());
            }
        }
        return;
    }
    if (path.size()>1)
    {
        if(!this->FindElementByPath(key))
        {
            throw invalid_argument("There is no element under this key!");
            return;
        }
        size_t PathIndex=0;
        this->SearchByPath(path, PathIndex);
    }
        
    
}

void JSONContainer::move(const std::string &from, const std::string &to)
{
    if (!this->FindElement(from))
    {
        throw invalid_argument("Couldn't find element from which to move!");
    }
    else if (!this->FindElement(to))
    {
        throw invalid_argument("Couldn't find element to move to!");
    }
    else
    {
        size_t FromIndex=this->getIndex(from);
        size_t ToIndex=this->getIndex(to);
        this->edit(this->JSONElements[ToIndex].getName(), this->JSONElements[FromIndex].getValue());
    }
}

void JSONContainer::save(const std::string &option) const
{
    size_t to=this->JSONElements.size();
    
    if (option=="minimal")
    {
        
        this->writer.WriteWithoutSpaces(this->JSONFilePath, this->JSONElements,0,to);
        return;
    }
    
        this->writer.WriteWithSpaces(this->JSONFilePath, this->JSONElements,0,to);
}

void JSONContainer::saveft(const std::string &option, int from, int to) const
{
    if (option=="minimal")
    {
        this->writer.WriteWithoutSpaces(this->JSONFilePath, this->JSONElements,from,to);
        return;
    }
    
        this->writer.WriteWithSpaces(this->JSONFilePath, this->JSONElements,from,to);
}

void JSONContainer::saveas(const std::string &FilePath, const std::string &option) const
{
    size_t to=this->JSONElements.size();
    if (option=="minimal")
    {
        this->writer.WriteWithoutSpaces(FilePath, this->JSONElements,0,to);
        return;
    }
    
        this->writer.WriteWithSpaces(FilePath, this->JSONElements,0,to);
}
void JSONContainer::saveasft(const std::string &FilePath, const std::string &option,int from,int to) const
{
    if (option=="minimal")
    {
        this->writer.WriteWithoutSpaces(FilePath, this->JSONElements,from,to);
        return;
    }
    
        this->writer.WriteWithSpaces(FilePath, this->JSONElements,from,to);
}

JSONElement& JSONContainer::operator[](int index)
{
    if (index>=this->Searched.size())
    {
        throw invalid_argument("Index out of bounds!");
        return this->Searched.at(0);
    }
    else
    {
        return this->Searched.at(index);
    }
}

bool JSONContainer::IsEmpty() const
{
    if (this->JSONFilePath=="")
    {
        return true;
    }
    return false;
}

void JSONContainer::PrintFilePath() const
{
    cout<<this->JSONFilePath;
    cout<<'\n';
}

void JSONContainer::CommandExcecutor(const std::string &command)
{
    std::string type="";
    vector<std::string> arg;
    std::string currentArg="";
    size_t index=0;
    bool flag=false;
    bool InString=false;
    size_t lenght=command.size();
    for (size_t i=0;i<lenght;i++)
    {
        if (command.at(i)!=' '&&!flag)
        {
            type.push_back(command.at(i));
        }
        else if (command.at(i)==' '&&!flag)
        {
            flag=true;
            
        }
        else if (command.at(i)!=' '&&flag)
        {
            if (command.at(i)=='"'&&flag&&InString==false)
            {
                InString=true;
            }
            else if (command.at(i)=='"'&&flag&&InString==true)
            {
                InString=false;
            }
            currentArg.push_back(command.at(i));
        }
        else if (command.at(i)==' '&&flag&&InString==true)
        {
            currentArg.push_back(command.at(i));
        }
        else if (command.at(i)==' '&&flag&&InString==false)
        {
            arg.push_back(currentArg);
            currentArg="";
            index++;
        }
        if (i==lenght-1&&flag)
        {
            arg.push_back(currentArg);
            currentArg="";
        }
        
    }
    
    if(type=="print")
    {
        try
        {
            this->print();
        }
        catch (const invalid_argument& e)
        {
            cerr<<e.what()<<'\n';
        }
        
    }
    else if(type=="edit")
    {
        size_t size=arg.size();
        std::string value=arg.at(size-1);
        std::string path="";
        for (size_t i=0;i<size-1;i++)
        {
            path+=arg.at(i);
        }
        try
        {
            this->edit(path, value);
        }
        catch (const invalid_argument& e)
        {
            cerr<<e.what()<<'\n';
        }
        
    }
    else if(type=="remove")
    {
        size_t size=arg.size();
        std::string path="";
        for (size_t i=0;i<size;i++)
        {
            path+=arg.at(i);
        }
        try
        {
            this->remove(path);
        }
        catch (const invalid_argument& e)
        {
            cerr<<e.what()<<'\n';
        }
    }
    else if(type=="create")
    {
        size_t size=arg.size();
        std::string value=arg.at(size-1);
        std::string path="";
        for (size_t i=0;i<size-1;i++)
        {
            path+=arg.at(i);
        }
        if (path=="")
        {
            throw invalid_argument("Invalid path or missing value!");
        }
        try
        {
            this->create(path, value);
        }
        catch (const invalid_argument& e)
        {
            cerr<<e.what()<<'\n';
        }
    }
    else if(type=="search")
    {
        size_t size=arg.size();
        std::string path="";
        for (size_t i=0;i<size;i++)
        {
            path+=arg.at(i);
        }
        try
        {
            this->search(path);
        }
        catch (const invalid_argument& e)
        {
            cerr<<e.what()<<'\n';
        }
    }
    else if(type=="move")
    {
        size_t size=arg.size();
        
        if (size!=2)
        {
            cerr<<"Please enter only two arguments!"<<'\n';
        }
        else
        {
            try
            {
                this->move(arg.at(0), arg.at(1));
            }
            catch (const invalid_argument& e)
            {
                cerr<<e.what()<<'\n';
            }
        }
        
    }
    else if(type=="save")
    {
        size_t size=arg.size();
        std::string option="";
        
        
        if (size>1)
        {
            cerr<<"Please enter one or no arguments!";
        }
        else
        {
            if (size==1)
            {
                option=arg.at(0);
            }
            try
            {
                this->save(option);
            }
            catch (const invalid_argument& e)
            {
                cerr<<e.what()<<'\n';
            }
        }
    }
    else if(type=="saveft")
    {
        size_t size=arg.size();
        std::string option="";
        
        
        if (size==2)
        {
            int from=stoi(arg.at(0));
            int to=stoi(arg.at(1));
            if (from<0||from>=to||to>=this->JSONElements.size())
            {
                cerr<<"Invalid range!";
                return;
            }
            else
            {
                try
                {
                    this->saveft(option, from, to);
                }
                catch (const invalid_argument& e)
                {
                    cerr<<e.what()<<'\n';
                }
            }
                
            
        }
        else if (size==3)
        {
            option=arg.at(0);
            int from=stoi(arg.at(1));
            int to=stoi(arg.at(2));
            if (from<0||from>=to||to>=this->JSONElements.size())
            {
                cerr<<"Invalid range!";
                return;
            }
            else
            {
                try
                {
                    this->saveft(option, from, to);
                }
                catch (const invalid_argument& e)
                {
                    cerr<<e.what()<<'\n';
                }
            }
            
        }
        else
        {
            cerr<<"Invalid arguments!";
        }
    }
    else if(type=="saveas")
    {
        size_t size=arg.size();
        std::string option="";
        std::string File="";
        
        
        if (size>2)
        {
            cerr<<"Please enter one or no arguments!";
        }
        else
        {
            if (size==1)
            {
                File=arg.at(0);
            }
            else if (size==2)
            {
                File=arg.at(0);
                option=arg.at(1);
            }
            try
            {
                this->saveas(File,option);
            }
            catch (const invalid_argument& e)
            {
                cerr<<e.what()<<'\n';
            }
        }
    }
    else if(type=="saveasft")
    {
        size_t size=arg.size();
        std::string option="";
        std::string File="";
        
        
        if (size==3)
        {
            File=arg.at(0);
            int from=stoi(arg.at(1));
            int to=stoi(arg.at(2));
            if (from<0||from>=to||to>=this->JSONElements.size())
            {
                cerr<<"Invalid range!";
                return;
            }
            else
            {
                try
                {
                    this->saveasft(File,option, from, to);
                }
                catch (const invalid_argument& e)
                {
                    cerr<<e.what()<<'\n';
                }
            }
                
            
        }
        else if (size==4)
        {
            File=arg.at(0);
            option=arg.at(1);
            int from=stoi(arg.at(2));
            int to=stoi(arg.at(3));
            if (from<0||from>=to||to>=this->JSONElements.size())
            {
                cerr<<"Invalid range!";
                return;
            }
            else
            {
                try
                {
                    this->saveasft(File,option, from, to);
                }
                catch (const invalid_argument& e)
                {
                    cerr<<e.what()<<'\n';
                }
            }
            
        }
        else
        {
            cerr<<"Invalid arguments!";
        }
    }
    else if(type=="savesearched")
    {
        size_t size=arg.size();
        std::string File="";
        
        
        if (size>1)
        {
            cerr<<"Please enter one argument!";
        }
        else
        {
            if (size==1)
            {
                File=arg.at(0);
            }
            try
            {
                this->savesearched(File);
            }
            catch (const invalid_argument& e)
            {
                cerr<<e.what()<<'\n';
            }
        }
    }
    else if(type=="savesearchedat")
    {
        size_t size=arg.size();
        std::string File="";
        std::string index="";
        
        
        if (size>2)
        {
            cerr<<"Please enter only two arguments!";
        }
        else
        {
            if (size==2)
            {
                File=arg.at(0);
                index=arg.at(1);
            }
            try
            {
                int Index=stoi(index);
                this->savesearchedat(File, Index);
            }
            catch (const invalid_argument& e)
            {
                cerr<<e.what()<<'\n';
            }
        }
    }
    else if(type=="printsearched")
    {
        size_t size=arg.size();
        
        if (size!=0)
        {
            cerr<<"Please don't enter ant arguments!";
        }
        else
        {
            if (size==0)
            {
                try
                {
                    this->printsearched();
                }
                catch (const invalid_argument& e)
                {
                    cerr<<e.what()<<'\n';
                }
            }
        }
    }
    else if(type=="printsearchedat")
    {
        size_t size=arg.size();
        std::string index="";
        
        
        if (size!=1)
        {
            cerr<<"Please enter only one argument!";
        }
        else
        {
            if (size==1)
            {
                index=arg.at(0);
            }
            try
            {
                int Index=stoi(index);
                this->printsearchedat(Index);
            }
            catch (const invalid_argument& e)
            {
                cerr<<e.what()<<'\n';
            }
        }
    }
    else
    {
        throw invalid_argument("Invalid command!");
    }
}

JSONContainer::Iterator::Iterator(JSONElement* element):pntr(element)
{}

JSONContainer::Iterator& JSONContainer::Iterator::operator++()
{
    ++pntr;
    return *this;
}

JSONContainer::Iterator JSONContainer::Iterator::operator++(int)
{
    Iterator curr(*this);
    ++(*this);
    return curr;
}

bool JSONContainer::Iterator::operator==(const Iterator & other) const
{
    return pntr==other.pntr;
}

bool JSONContainer::Iterator::operator!=(const Iterator &other) const
{
    return !(pntr == other.pntr);
}

 const JSONElement& JSONContainer::Iterator::operator*() const
{
    return *pntr;
}

 JSONElement& JSONContainer::Iterator::operator*()
{
   return *pntr;
}

JSONElement* JSONContainer::Iterator::operator->()
{
    return pntr;
}

JSONContainer::Iterator JSONContainer::begin()
{
    return Iterator(&this->JSONElements.at(0));
}

JSONContainer::Iterator JSONContainer::end()
{
    size_t size=this->JSONElements.size();
    return Iterator(&(this->JSONElements.at(0))+size);
}
