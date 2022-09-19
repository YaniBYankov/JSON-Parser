#ifndef Value_hpp
#define Value_hpp

#include <cstring>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class JSONElement;

/**
 * @brief Класът Value е абстрактен клас, който представлява стойността на даден обект. Съдържа символен низ със съответната стойност.
 */
class Value
{
protected:
    /**
     * @brief value е символен низ, чиято роля е да съдържа текст със стойността на даден обект. Член данната е защитена с цел наследяващите Value класове да имат достъп до нея.
     */
    std::string value;
public:
    /**
     * @brief Конструктор по подразбиране, който не приема никакви аргументи и задава стойност на член данната value празен низ.
     */
    Value();
    /**
     * @brief Конструктор, ма който се подава като параметър символен низ и се записва в член данната value.
     * @param value символен низ, който да бъде зададен като стойност.
     */
    Value(const std::string& value);
    /**
     * @brief Чисто виртуален метод, който няма имплементация в базовия клас Value, но всеки негов наследник го имплементира, като връща указател към съответния обект.
     * @return указател към представител от клас Value
     */
    virtual Value* clone() const=0;
    /**
     * @brief Константен метод, връщат низа, съдържащ стойността на даден обект като текст.
     * @return символен низ
     */
    string getValue() const;
    /**
     * @brief Виртуален деструктор.
     */
    virtual ~Value();
    
    /**
     * @brief Задава стойност на value.
     * @param ValueString символен низ, който да бъде зададен като стойност.
     */
    void SetValueString(const std::string& ValueString);
    /**
     * @brief Виртуалне метод, който няма имплементация от базовия клас, но наследниците ValueArray и ValueObject го имплементират.
     * @see ValueArray
     * @see ValueObject
     */
    virtual void UpdateValue();
    
    /**
     * @brief Виртуалне метод, който няма имплементация от базовия клас, но ValueObject го имплементира.
     * @param add елемент, който да бъде добавен.
     * @see ValueObject
     */
    virtual void SetValue(JSONElement& add);
    /**
     * @brief Виртуалне метод, предназначен наследниците ValueArray и ValueObject да го имплементират.
     * @see ValueArray
     * @see ValueObject
     * @return Указател към масив от елементи JSONElement
     */
    virtual vector<JSONElement>* GetElements();
    
    /**
     * @brief Виртуалне метод, предназначен класът ValueObject да го имплементира.
     * @see ValueObject
     * @return булева стойност, указваща дали има елементи, който се съдържат в други елементи
     */
    virtual bool CheckForNestedElements();
};


#endif /* Value_hpp */
