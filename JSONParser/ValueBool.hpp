#ifndef ValueBool_hpp
#define ValueBool_hpp

#include "Value.hpp"
/**
 * @brief Наследява класа Value и представя булева стойност.
 */
class ValueBool:public Value
{
private:
    /**
     * @brief Символен низ, който ще съдържа съответната булева стойност.
     */
    std::string boolean;
    /**
     * @brief Частен метод, който копира информацията от друг представител на класа.
     * @param other друг обект от ValueBool, чиито стойности ще се копират
     */
    void copy(const ValueBool& other);
public:
    /**
     * @brief Конструктор по подразбиране, задаващ празен низ.
     */
    ValueBool();
    /**
     * @brief Конструктор, който подаден символен низ записва в boolean.
     * @param string символен низ
     */
    ValueBool(const std::string& string);
    /**
     * @brief Копиращ конструктор, който създава обект копие, използвайки метода copy.
     * @param other обект, който ще бъде използван за създаване на копието.
     */
    ValueBool(const ValueBool& other);
    /**
     * @brief Оператор, който присвоява стойност на друг обект от ValueBool.
     * @param other обект, който ще бъде използван за присвояването.
     * @return псевдоним към обекта, на който сме присвоили дадената стойност.
     */
    ValueBool& operator=(const ValueBool& other);
    /**
     * @brief Деструктор.
     */
    virtual ~ValueBool();
    /**
     * @brief Виртуален метод, който връща указател(сочещ към обект от тип Value) към съответния обект.
     * @return указател към представител от клас Value
     */
    virtual Value* clone() const;
};


#endif /* ValueBool_hpp */
