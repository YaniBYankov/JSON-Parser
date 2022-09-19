#ifndef JSONReader_hpp
#define JSONReader_hpp
#include "JSONvaildation.hpp"

/**
 * @brief Класът JSONReader прочита и валидира информацията от подадения файл спрямо синтаксиса на JSON
 */
class JSONReader {
private:
    /**
     * @brief Валидация спрямо синтаксиса на JSON.
     */
    JSONvalidation validation;
    
    /**
     * @brief Премахва празните разстояния преди първият срещнат символ
     */
    void removeSpacesFront(string& string);
    /**
     * @brief Премахва празните разстояния в самия текст
     */
    void removeSpacesIn(string& string);
    /**
     * @brief Премахва празните разстояния след първият срещнат символ
     */
    void removeSpacesBack(string& string);
    
    
public:
    /**
     * @brief Премахва празните разстояния, използвайки частните членове функции
     */
    void removeSpaces(string& string);
    
    /**
     * @brief Прочита файла от подадения. Ако четенето е успешно, запазва информацията в символен низ и премахва всички празни места.
     * @param JSONfilepath низ с името на файла, от който ще се чете.
     * @return прочетената информация, записана в символен низ без празни разстояния.
     */
    string ReadJSON( const string& JSONfilepath);
    
    /**
     * @brief Проверява дали подаденият символен низ е валиден спрямо формата на JSON извиквайки метода IsValidJSON от класа JSONValidation.
     * @see IsValidJSON
     * @param JSON низ, който да се валидира .
     * @return Булева стойност.
     */
    bool isValid(const string& JSON) const;
};


#endif /* JSONReader_hpp */
