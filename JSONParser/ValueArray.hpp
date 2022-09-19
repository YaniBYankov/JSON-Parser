#ifndef ValueArray_hpp
#define ValueArray_hpp

#include "Value.hpp"
/**
 * @brief Наследява класа Value и представя масив от стойности.
 */
class ValueArray:public Value
{
private:
    /**
     * @brief Масив от символни низове, представящи стойностите в масива като текст.
     */
    vector<std::string> array;
    /**
     * @brief Масив от обекти от тип JSONElement. В тях се съдържа информацията за стойността на елементите на масива, а името е името на масива, в който са.
     */
    vector<JSONElement> values;
    /**
     * @brief Частен метод, който копира информацията от друг представител на класа.
     * @param other друг обект от ValueArray, чиито стойности ще се копират
     */
    void copy(const ValueArray& other);
public:
    /**
     * @brief Конструктор по подразбиране, задаващ празен низ.
     */
    ValueArray();
    /**
     * @brief Конструктор, който подаден символен разпределя стойностите в array и създава обекти от тип JSONElement със съответстващите им стойности и ги запазва в масива values.
     * @param string символен низ, съдържащ стойностите на масива.
     */
    ValueArray(const std::string& string);
    /**
     * @brief Копиращ конструктор, който създава обект копие, използвайки метода copy.
     * @param other обект, който ще бъде използван за създаване на копието.
     */
    ValueArray(const ValueArray& other);
    /**
     * @brief Оператор, който присвоява стойност на друг обект от ValueArray.
     * @param other обект, който ще бъде използван за присвояването.
     * @return псевдоним към обекта, на който сме присвоили дадената стойност.
     */
    ValueArray& operator=(const ValueArray& other);
    /**
     * @brief Деструктор.
     */
    virtual ~ValueArray();
    /**
     * @brief Виртуален метод, който извлича контейнерът, съдържащ стойностите на масива.
     * @return Методът връща указател към масива със стойности, което позволява тяхната промяна.
     */
    virtual vector<JSONElement>* GetElements();
    /**
     * @brief Виртуален метод, който задава стойност на член данната value от базовия клас съответно символен низ, конкатенация от стойностите на масива разделени със запетая.
     */
    virtual void UpdateValue();
    /**
     * @brief Виртуален метод, който връща указател(сочещ към обект от тип Value) към съответния обект.
     * @return указател към представител от клас Value
     */
    virtual Value* clone() const;
};

#endif /* ValueArray_hpp */
