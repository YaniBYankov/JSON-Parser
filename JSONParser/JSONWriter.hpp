#ifndef JSONWriter_hpp
#define JSONWriter_hpp
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#include "JSONElement.hpp"

/**
 * @brief Класът JSONWriter записва информацията от JSONContainer във файл спрямо синтаксиса на JSON
 */
class JSONWriter
{
public:
    /**
     * @brief Записва информацията ,след успешно отваряне на файл, с минимален обем, без излишни празни позиции.
     * @param JSONFilePath низ с името на файла, на който ще се записва.
     * @param elements контейнер с елементите, които ще бъдат записани.
     * @param from индекс, от който да започне записването последователно,
     * @param to индекс, до който да продължи записването.
     */
    void WriteWithoutSpaces(const std::string& JSONFilePath,const vector<JSONElement>& elements,int from,int to)const;
    /**
     * @brief Записва информацията ,след успешно отваряне на файл, подравнено с отмествания и нови редове, с цел по-добра четивност
     * @param JSONFilePath низ с името на файла, на който ще се записва.
     * @param elements контейнер с елементите, които ще бъдат записани.
     * @param from индекс, от който да започне записването последователно,
     * @param to индекс, до който да продължи записването.
     */
    void WriteWithSpaces(const std::string& JSONFilePath,const vector<JSONElement>& elements,int from,int to) const;
};

#endif /* JSONWriter_hpp */
