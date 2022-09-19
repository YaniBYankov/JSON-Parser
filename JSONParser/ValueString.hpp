#ifndef ValueString_hpp
#define ValueString_hpp

#include "Value.hpp"

/**
 * @brief Наследява класа Value и представя символен низ.
 */
class ValueString:public Value
{
private:
    /**
     * @brief Символен низ, който ще съдържа съответния текст.
     */
    std::string string;
    /**
     * @brief Частен метод, който копира информацията от друг представител на класа.
     * @param other друг обект от ValueString, чиито стойности ще се копират
     */
    void copy(const ValueString& other);
public:
    /**
     * @brief Конструктор по подразбиране, задаващ празен низ.
     */
    ValueString();
    /**
     * @brief Конструктор, който подаден символен низ записва в string..
     * @param string символен низ
     */
    ValueString(const std::string& string);
    /**
     * @brief Копиращ конструктор, който създава обект копие, използвайки метода copy.
     * @param other обект, който ще бъде използван за създаване на копието.
     */
    ValueString(const ValueString& other);
    /**
     * @brief Оператор, който присвоява стойност на друг обект от ValueString.
     * @param other обект, който ще бъде използван за присвояването.
     * @return псевдоним към обекта, на който сме присвоили дадената стойност.
     */
    ValueString& operator=(const ValueString& other);
    /**
     * @brief Деструктор.
     */
    virtual ~ValueString();
    /**
     * @brief Виртуален метод, който връща указател(сочещ към обект от тип Value) към съответния обект.
     * @return указател към представител от клас Value
     */
    virtual Value* clone() const;
};

#endif /* ValueString_hpp */
