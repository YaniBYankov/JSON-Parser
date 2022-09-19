#ifndef ValueChar_hpp
#define ValueChar_hpp

#include "Value.hpp"

/**
 * @brief Наследява класа Value и представя стойност от символен тип.
 */
class ValueChar:public Value
{
private:
    /**
     * @brief Променлива от символен тип, която ще съдържа един символ.
     */
    char character;
    /**
     * @brief Частен метод, който копира информацията от друг представител на класа.
     * @param other друг обект от ValueChar, чиито стойности ще се копират
     */
    void copy(const ValueChar& other);
public:
    /**
     * @brief Конструктор по подразбиране.
     */
    ValueChar();
    /**
     * @brief Конструктор, който при подаден символен низ извлича символа, съдържащ се в него, и го записва в character.
     * @param string символен низ
     */
    ValueChar(const std::string& string);
    /**
     * @brief Копиращ конструктор, който създава обект копие, използвайки метода copy.
     * @param other обект, който ще бъде използван за създаване на копието.
     */
    ValueChar(const ValueChar& other);
    /**
     * @brief Оператор, който присвоява стойност на друг обект от ValueChar.
     * @param other обект, който ще бъде използван за присвояването.
     * @return псевдоним към обекта, на който сме присвоили дадената стойност.
     */
    ValueChar& operator=(const ValueChar& other);
    /**
     * @brief Деструктор.
     */
    virtual ~ValueChar();
    
    /**
     * @brief Виртуален метод, който връща указател(сочещ към обект от тип Value) към съответния обект.
     * @return указател към представител от клас Value
     */
    virtual Value* clone() const;
};


#endif /* ValueChar_hpp */
