#ifndef JSONContainer_hpp
#define JSONContainer_hpp

#include "JSONReader.hpp"
#include "JSONWriter.hpp"
#include "JSONElement.hpp"
/**
 * @brief Класът JSONContainer съдържа информацията от прочетения JSON файл и методи, отговарящи за изпълнението на командите, подавани от потребителя.
 */
class JSONContainer
{
private:
    /**
     * @brief Символен низ, който съдържа информацията от файла, записана без никакви разстояния.
     */
    std::string JSON;
    /**
     * @brief Символен низ, който съдържа името на файла, който е прочетен.
     */
    std::string JSONFilePath;
    /**
     * @brief Масив от елементи
     */
    vector<JSONElement> JSONElements;
    /**
     * @brief Масив от търсените  елементи
     */
    vector<JSONElement> Searched;
    /**
     * @brief Инстанция на JSONReader с цел четене и валидиране на данните
     */
    JSONReader reader;
    /**
     * @brief Инстанция на JSONWriter с цел запис на данните
     */
    JSONWriter writer;
    /**
     * @brief Връща масив от символни низове, представящи път към даден елемент
     * @param element символен низ с указан път към елемент
     * @return масив от символни низове, указващи пътя към елемемент
     */
    vector<std::string> GetPath(const std::string& element);
    /**
     * @brief Булев метод, който по дадено име на елемент, показва дали той съществува.
     * @param element символен низ с име на  елемент
     */
    bool FindElement(const std::string& element);
    /**
     * @brief По подаден път към елемент променя неговата стойност. Ако такъв елемент не бъде намерен, хвърля изключение.
     * Ако е намерен елементът се извикват съответните фънкции спрямо неговия тип.
     * @see EditByPath
     * @param element символен низ с указан път към елемент
     * @param Value нова стойност
     */
    void EditByPath(const std::string& element,const std::string& Value);
    /**
     * @brief Изтрива по подаден път елемент.  Ако такъв елемент не бъде намерен, хвърля изключение.
     * Ако е намерен елементът се извикват съответните фънкции спрямо неговия тип.
     * @see RemoveByPathObject
     * @see RemoveByPathArray
     * @param path масив от символни низове, указващи пътя към елемемент
     * @param PathIndex променлива от тип size_t, подадена като псевдоним, която следи на кое ниво е пътят
     */
    void RemoveByPath(vector<std::string>& path,size_t& PathIndex);
    /**
     * @brief Намира рекурсивно по подаден път елемент и го записва в масива с търсени елементи, извиквайки функцията SearchByPath от класа JSONElement. Ако такъв елемент не бъде намерен, хвърля изключение.
     * @see SearchByPath
     * @param path масив от символни низове, указващи пътя към елемемент
     * @param PathIndex променлива от тип size_t, подадена като псевдоним, която следи на кое ниво е пътят
     */
    void SearchByPath(vector<std::string>& path,size_t& PathIndex);
    /**
     * @brief Създава празен елемент и извиква за него функцията CreateByPath от JSONElement. После го добавя в масива с елементи.
     * @see CreateByPath
     * @param path масив от символни низове, указващи пътя към елемемент
     * @param Value стойността на новия елемент
     * @param PathIndex променлива от тип size_t, подадена като псевдоним, която следи на кое ниво е пътят
     */
    void CreateByPath(vector<std::string>& path,const std::string& Value,size_t& PathIndex);
    /**
     * @brief Извиква функцията UpdateValue от класа JSONElement за всеки елемент.
     */
    void UpdateValue();
    /**
     * @brief Намира на кой индекс се намира елемент
     * @param name символен низ с името на елемента
     * @return индекса на елемента
     */
    size_t getIndex(const std::string& name);
    /**
     * @brief Извиква функцията CountAllElements от класа JSONElement за всеки елемент, който съдържа елементи е себе си.
     */
    size_t CountAllJSONElements();
    
    
    
public:
    /**
     * @brief Конструктор по подразбиране, който задава стойности на името на файла и на информацията от него празния низ
     */
    JSONContainer();
    /**
     * @brief Метод, който по подадено име на файл прозита съдържанието и проверява дали е валиден спрямо синтаксиса на JSON. Ако е валиден, се записва информацията от него като се извиква метода setJSON
     * @param JSONFilePath име на файла
     * @see setJSON
     */
    void JSONContainerFill(const string& JSONFilePath);
    /**
     * @brief Извлича името и стойността на всеки един елемент и го записва в масива JSONElements.
     */
    void setJSON();
    /**
     * @brief Принтира всички елементи като използва функциите CallPrintWithSpaces и Print от класа JSONElement
     * @see CallPrintWithSpaces
     * @see Print
     */
    void print() const;
    /**
     * @brief Принтира всички търсени елементи като използва функциите CallPrintWithSpaces и Print от класа JSONElement
     * @see CallPrintWithSpaces
     * @see Print
     */
    void printsearched() const;
    /**
     * @brief Принтира търсен елемент на подадена позиция като използва функцията Print от класа JSONElement. Ако подаденият индекс е невалиден, се хвърля изключение.
     * @param index индекс на елемента, който са бъде принтиран
     * @see Print
     */
    void printsearchedat(const size_t index) const;
    /**
     * @brief Проверява дали даден път до елемент е валиден и дали зададената новоа стойност е валидна. Ако синтаксисът спрямо JSON е спазен, се променя стойността на зададения елемент с новата, извиквайки метода EditByPath, ако не е, се хвърля изключение с информация за проблема.
     * @param element символен низ, указващ пълния път до елемент
     * @param value символен низ с новата стойност
     * @see EditByPath
     */
    void edit(const std::string& element,const std::string& value);
    /**
     * @brief Проверява дали по даден път до елемент, той съществува. Ако е намерен, той бива изтрит с помощта на метода RemoveByPath
     * @param element символен низ, указващ пълния път до елемент
     * @see RemoveByPath
     */
    void remove(const std::string& element);
    /**
     * @brief Проверява дали даденият елемент вече съществува и ако да, се въобщава като се хвърля изключение. Ако елементът не съществува и неговата стойност е валидна, се извиква методът CreateByPath.
     * @param name символен низ, указващ пълния път до елемент
     * @param value символен низ с новата стойност
     * @see CreateByPath
     */
    void create(const std::string& name,const std::string& value);
    /**
     * @brief Проверява дали търсеният елемент съществува. Ако той бъде намерен се записват всички елементи с дадения ключ. Ако е подаден пълен път до елемент, се записва само елемента с помощта на метода SearchByPath
     * @param key ключ или път към елемент
     * @see SearchByPath
     */
    void search(const std::string& key);
    /**
     * @brief Проверява дали търсените два елемента съществуват. Ако те бъдат намерени се копира стойността от fom към to с метода edit
     * @param from ключ към елемент от който да бъде преместването на стойността
     * @param to ключ към елемент към който да бъде преместването на стойността
     * @see edit
     */
    void move(const std::string& from,const std::string& to);
    /**
     * @brief Запазва информацията на JSON обекта спрямо избраната опция във файла, от който е бил прочетен. Ако е избрана опцията minimal, запазването се извършва без празни разстояние, в противен случай с отмествания и нови редове, с цел по-добра четивност.
     * @param option символен низ, указващ избраната опция
     * @see WriteWithoutSpaces
     * @see WriteWithSpaces
     */
    void save(const std::string& option) const;
    /**
     * @brief Запазва информацията на JSON обекта спрямо избраната опция в нов файл. Ако е избрана опцията minimal, запазването се извършва без празни разстояние, в противен случай с отмествания и нови редове, с цел по-добра четивност.
     * @param FilePath файл, в който да бъде запазен обекта
     * @param option символен низ, указващ избраната опция
     * @see WriteWithoutSpaces
     * @see WriteWithSpaces
     */
    void saveas(const std::string& FilePath,const std::string& option) const;
    /**
     * @brief Запазва информацията на JSON обекта спрямо избраната опция във файла, от който е бил прочетен, като се задава от кой елемент да започне запазването и до кой да приключи. Ако е избрана опцията minimal, запазването се извършва без празни разстояние, в противен случай с отмествания и нови редове, с цел по-добра четивност.
     * @param option символен низ, указващ избраната опция
     * @param from индекс на елемента, от който да започне запазването
     * @param to индекс на елемента ,до който да се извършва запазването
     * @see WriteWithoutSpaces
     * @see WriteWithSpaces
     */
    void saveft(const std::string& option, int from,int to) const;
    /**
     * @brief Запазва информацията на JSON обекта спрямо избраната опция в нов файл, като се задава от кой елемент да започне запазването и до кой да приключи. Ако е избрана опцията minimal, запазването се извършва без празни разстояние, в противен случай с отмествания и нови редове, с цел по-добра четивност.
     * @param FilePath файл, в който да бъде запазен обекта
     * @param option символен низ, указващ избраната опция
     * @param from индекс на елемента, от който да започне запазването
     * @param to индекс на елемента ,до който да се извършва запазването
     * @see WriteWithoutSpaces
     * @see WriteWithSpaces
     */
    void saveasft(const std::string& FilePath,const std::string& option,int from,int to) const;
    /**
     * @brief Запазва масива с търсените елементи във файл като използва функцията Print от класа JSONElement. 
     * @param FilePath файл, в който да бъде запазен обекта
     * @see Print
     */
    void savesearched(const std::string& FilePath) const;
    /**
     * @brief Запазва търсен елемент на подадена позиция във файл като използва функцията Print от класа JSONElement. Ако подаденият индекс е невалиден, се хвърля изключение.
     * @param FilePath файл, в който да бъде запазен обекта
     * @param index индекс на елемента, който са бъде принтиран
     * @see Print
     */
    void savesearchedat(const std::string& FilePath,const size_t index) const;
    /**
     * @brief Проверява дали е празен JSON контейнерът.
     */
    bool IsEmpty() const;
    /**
     * @brief Принтира името на файла, от който е извършено четенето
     */
    void PrintFilePath() const;
    /**
     * @brief Намира дали по подаден път към елемент, той съшествува. Методът се използва за проверка в другите методи, изискващи проверка дали даден елемент съществува.
     * @param element път до елемент
     */
    bool FindElementByPath(const std::string& element);
    /**
     * @brief Оператор, който по подаден индекс на елемент, проверява дали има елемент на тази позиция в масива с търсени елементи и го връша псевдоним към него.
     * @param index индекс на елемент
     * @return псевдоним към елемент с търсения индекс
     */
    JSONElement& operator[](int index);
    /**
     * @brief Извлича и обработва входните аргументи и ги подава на съответната команда. Ако има възникнали грешки, методът сигнализира със съобщение, описващо проблема.
     */
    void CommandExcecutor(const std::string& command);
    /**
     * @brief Клас итератор, който служи за итериране налементите от масива JSONElements.
     */
    class Iterator
    {
        friend class JSONContainer;
    private:
        /**
         * @brief Указател към JSON елемент
         */
        JSONElement* pntr;
        /**
         * @brief Частен конструктор, който пренасочва указателя на итератора към подадения елемент
         * @param element елемент, към който да сочи
         */
        Iterator(JSONElement* element);
    public:
        /**
         * @brief Постфиксен оператор ++, който измества оператора с една позиция
         */
        Iterator& operator++();
        /**
         * @brief Префиксен оператор ++, който измества оператора с една позиция
         */
        Iterator operator++(int);
        /**
         * @brief Оператор ==, който сравнява дали два итератора сочат към един и същ елемент
         * @param other итератор за сравнение
         */
        bool operator == (const Iterator& other)const;
        /**
         * @brief Оператор ==, който сравнява дали два итератора не сочат към един и същ елемент
         * @param other итератор за сравнение
         */
        bool operator != (const Iterator& other)const;
        /**
         * @brief Оператор *, който връща константен псевдоним към елемента
         */
        const JSONElement& operator*() const;
        /**
         * @brief Оператор *, който връща псевдоним към елемента
         */
        JSONElement& operator*();
        /**
         * @brief Оператор ->, който връща указател към елемента
         */
        JSONElement* operator->();
    };
    /**
     * @brief Метод, който връща итератор към началото на масива JSONElements
     */
    Iterator begin();
    /**
     * @brief Метод, който връща итератор към края на масива JSONElements
     */
    Iterator end();

};

#endif /* JSONContainer_hpp */
