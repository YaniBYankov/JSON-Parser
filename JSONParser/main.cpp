#include "JSONvaildation.hpp"
#include "JSONContainer.hpp"
#include "JSONReader.hpp"

void Menu()
{
    cout<<"MENU"<<'\n';
    cout<<'\n';
    cout<<"* print -------------------------> Prints the JSON file!"<<'\n';
    cout<<"* search <key> ------------------> Searchs for the object under the given key or path and saves it!"<<'\n';
    cout<<"* edit <object path> <value> ----> Edits the object value with the given one!"<<'\n';
    cout<<"* create <object path> <value> --> Creates a new object with the given value unless it already exists!"<<'\n';
    cout<<"* remove <object path> ----------> Removes the object unless it doesnt exists!"<<'\n';
    cout<<"* move <from> <to> --------------> Moves the value from \"from\" to \"to\"!"<<'\n';
    cout<<"* save <option> -----------------> Saves the JSON file in the file it's being opened!"<<'\n';
    cout<<"* saveft <option> <from> <to> ---> Saves the JSON file in the file it's being opened!"<<'\n';
    cout<<"* saveas <file> <option> --------> Saves the JSON file in new or existing file!"<<'\n';
    cout<<"                                   ! If option is \"minimal\" there would be no spaces between characters\n                                    when the file is saved!"<<'\n';
    cout<<"* saveasft <option> <from> <to> -> Saves the JSON file in the file it's being opened!"<<'\n';
    cout<<"* printsearched -----------------> Prints the searched objects!"<<'\n';
    cout<<"* printsearchedat <index> -------> Prints the searched objects at index!"<<'\n';
    cout<<"* savesearched <file> -----------> Saves the searched objects in a new or existing file!"<<'\n';
    cout<<"* savesearchedat <file> <index> -> Saves the searched objects at index in a new or existing file!"<<'\n';
    cout<<"* menu --------------------------> Shows MENU!"<<'\n';
    cout<<"* exit --------------------------> Exits the program!"<<'\n';
}
void run()
{
    JSONContainer container;
    while (container.IsEmpty())
    {
        std::string JSONFilePath="";
        cout<<"Enter JSONFilePath to open: ";
        getline(cin, JSONFilePath);
        if (JSONFilePath=="exit")
        {
            return ;
        }
        try {
            container.JSONContainerFill(JSONFilePath);

        } catch (const invalid_argument& e) {
            cerr<<e.what()<<'\n';
        }
    }

    cout<<'\n';
    container.PrintFilePath();
    cout<<'\n';
    Menu();
    while (true)
    {
        std::string command;
        cout<<'\n';
        cout<<"Enter command: ";
        getline(cin, command);
        if (command=="menu")
        {
            Menu();
        }
        else if (command=="exit")
        {
            break;
        }
        else
        {
            try
            {
                container.CommandExcecutor(command);
            }
            catch (const invalid_argument& e)
            {
                cerr<<e.what()<<'\n';;
            }

        }

    }
}

int main() {
    run();
    JSONContainer container;
    while (container.IsEmpty())
    {
        std::string JSONFilePath="";
        cout<<"Enter JSONFilePath to open: ";
        getline(cin, JSONFilePath);
        if (JSONFilePath=="exit")
        {
            return 0;
        }
        try {
            container.JSONContainerFill(JSONFilePath);

        } catch (const invalid_argument& e) {
            cerr<<e.what()<<'\n';
        }
    }

    cout<<'\n';
    container.PrintFilePath();
    cout<<'\n';
    Menu();
    while (true)
    {
        std::string command;
        cout<<'\n';
        cout<<"Enter command: ";
        getline(cin, command);
        if (command=="exit")
        {
            break;
        }
        else
        {
            try
            {
                container.CommandExcecutor(command);
            }
            catch (const invalid_argument& e)
            {
                cerr<<e.what()<<'\n';;
            }
        }

    }
    return 0;
}
