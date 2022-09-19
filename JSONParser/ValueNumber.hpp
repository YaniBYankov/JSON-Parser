#ifndef ValueNumber_hpp
#define ValueNumber_hpp

#include "Value.hpp"
/**
 * @brief Наследява класа Value и представя число.
 */
class ValueNumber:public Value
{
private:
    /**
     * @brief Символен низ, който ще съдържа съответното число.
     */
    std::string number;
    /**
     * @brief Частен метод, който копира информацията от друг представител на класа.
     * @param other друг обект от ValueNumber, чиито стойности ще се копират
     */
    void copy(const ValueNumber& other);
public:
    /**
     * @brief Конструктор по подразбиране, задаващ празен низ.
     */
    ValueNumber();
    /**
     * @brief Конструктор, който подаден символен низ записва в number.
     * @param string символен низ
     */
    ValueNumber(const std::string& string);
    /**
     * @brief Копиращ конструктор, който създава обект копие, използвайки метода copy.
     * @param other обект, който ще бъде използван за създаване на копието.
     */
    ValueNumber(const ValueNumber& other);
    /**
     * @brief Оператор, който присвоява стойност на друг обект от ValueNumber.
     * @param other обект, който ще бъде използван за присвояването.
     * @return псевдоним към обекта, на който сме присвоили дадената стойност.
     */
    ValueNumber& operator=(const ValueNumber& other);
    /**
     * @brief Деструктор.
     */
    virtual ~ValueNumber();
    /**
     * @brief Виртуален метод, който връща указател(сочещ към обект от тип Value) към съответния обект.
     * @return указател към представител от клас Value
     */
    virtual Value* clone() const;
};


#endif /* ValueNumber_hpp */
