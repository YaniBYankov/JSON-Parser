#ifndef ValueObject_hpp
#define ValueObject_hpp

#include "Value.hpp"
#include "ValueChar.hpp"
#include "ValueString.hpp"
#include "ValueNumber.hpp"
#include "ValueBool.hpp"
#include "ValueArray.hpp"
#include "JSONElement.hpp"

class JSONElement;
/**
 * @brief Наследява класа Value и представя обект.
 */
class ValueObject:public Value
{
private:
    /**
     * @brief Масив от обекти от тип JSONElement. В тях се съдържа информацията за елементите на обекта.
     */
    vector<JSONElement> elements;
    /**
     * @brief Частен метод, който копира информацията от друг представител на класа.
     * @param other друг обект от ValueОbject, чиито стойности ще се копират
     */
    void copy(const ValueObject& other);
public:
    /**
     * @brief Конструктор по подразбиране, задаващ празен низ.
     */
    ValueObject();
    /**
     * @brief Конструктор, който подаден символен създава обекти от тип JSONElement и ги запазва в масива elements.
     * @param string символен низ, съдържащ елементите.
     */
    ValueObject(const std::string& string);
    /**
     * @brief Копиращ конструктор, който създава обект копие, използвайки метода copy.
     * @param other обект, който ще бъде използван за създаване на копието.
     */
    ValueObject(const ValueObject& other);
    /**
     * @brief Оператор, който присвоява стойност на друг обект от ValueОbject.
     * @param other обект, който ще бъде използван за присвояването.
     * @return псевдоним към обекта, на който сме присвоили дадената стойност.
     */
    ValueObject& operator=(const ValueObject& other);
    /**
     * @brief Деструктор.
     */
    virtual ~ValueObject();
    /**
     * @brief Виртуален метод, който връща указател(сочещ към обект от тип Value) към съответния обект.
     * @return указател към представител от клас Value
     */
    virtual Value* clone() const;
    /**
     * @brief Виртуален метод, който задава стойност на член данната value от базовия клас съответно символен низ, конкатенация от елементите на обекта разделени със запетая.
     */
    virtual void UpdateValue();
    /**
     * @brief Виртуален метод, който добавя нов елемент в масива от елементи.
     * @param add елементът, който ще се добави.
     */
    virtual void SetValue(JSONElement& add);
    /**
     * @brief Виртуален метод, който извлича контейнерът, съдържащ стойностите на обекта.
     * @return Методът връща указател към масива със стойности, което позволява тяхната промяна.
     */
    virtual vector<JSONElement>* GetElements();
    /**
     * @brief Виртуален метод, който проверява дали има елементи със стойносъ други елементи.
     * @return булева стойност, указваща дали има елементи, който се съдържат в други елементи
     */
    virtual bool CheckForNestedElements();
};


#endif /* ValueObject_hpp */
