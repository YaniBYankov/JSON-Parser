#ifndef JSONvaildation_hpp
#define JSONvaildation_hpp
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Класът JSONvalidation валидира информацията от подадения символен низ спрямо синтаксиса на JSON
 */
class JSONvalidation
{
private:
    /**
     * @brief Проверява дали стойността е от тип символ и дали е валидна.
     * @param JSON символен низ за проверка
     * @param lenght дължина на симвония низ
     * @param index променлива от тип size_t подадена по референция, следяща кой подред е разглежданият символ от символния низ JSON
     * @return връща булева стойност, която ако е истина, подаденият низ е валиден, ако е лъжа- невалиден.
     */
    bool isValidChar(const string& JSON,size_t lenght,size_t& index) const;
    /**
     * @brief Проверява дали стойността е от тип символен низ  и дали е валидна.
     * @param JSON символен низ за проверка
     * @param lenght дължина на симвония низ
     * @param index променлива от тип size_t подадена по референция, следяща кой подред е разглежданият символ от символния низ JSON
     * @return връща булева стойност, която ако е истина, подаденият низ е валиден, ако е лъжа- невалиден.
     */
    bool isValidString(const string& JSON,size_t lenght,size_t& index) const;
    /**
     * @brief Проверява дали стойността е число и дали е валидна.
     * @param JSON символен низ за проверка
     * @param lenght дължина на симвония низ
     * @param index променлива от тип size_t подадена по референция, следяща кой подред е разглежданият символ от символния низ JSON
     * @return връща булева стойност, която ако е истина, подаденият низ е валиден, ако е лъжа- невалиден.
     */
    bool isValidNumber(const string& JSON,size_t lenght,size_t& index) const;
    /**
     * @brief Проверява дали стойността е масив и дали е валидна.
     * @param JSON символен низ за проверка
     * @param lenght дължина на симвония низ
     * @param index променлива от тип size_t подадена по референция, следяща кой подред е разглежданият символ от символния низ JSON
     * @return връща булева стойност, която ако е истина, подаденият низ е валиден, ако е лъжа- невалиден.
     */
    bool isValidArray(const string& JSON,size_t lenght,size_t& index) const;
    /**
     * @brief Проверява дали стойността е от булев тип и дали е валидна.
     * @param JSON символен низ за проверка
     * @param lenght дължина на симвония низ
     * @param index променлива от тип size_t подадена по референция, следяща кой подред е разглежданият символ от символния низ JSON
     * @return връща булева стойност, която ако е истина, подаденият низ е валиден, ако е лъжа- невалиден.
     */
    bool isValidBool(const string& JSON,size_t lenght,size_t& index) const;
    /**
     * @brief Проверява дали стойността е  валидно име на обект спрямо синтаксиса на JSON.
     * @param JSON символен низ за проверка
     * @param lenght дължина на симвония низ
     * @param index променлива от тип size_t подадена по референция, следяща кой подред е разглежданият символ от символния низ JSON
     * @return връща булева стойност, която ако е истина, подаденият низ е валиден, ако е лъжа- невалиден.
     */
    bool isValidName(const string& JSON,size_t lenght,size_t& index) const;
    /**
     * @brief Проверява дали стойността е  валидна стойност на обект спрямо синтаксиса на JSON.
     * @param JSON символен низ за проверка
     * @param lenght дължина на симвония низ
     * @param index променлива от тип size_t подадена по референция, следяща кой подред е разглежданият символ от символния низ JSON
     * @return връща булева стойност, която ако е истина, подаденият низ е валиден, ако е лъжа- невалиден.
     */
    bool isValidValue(const string& JSON,size_t lenght,size_t& index) const;
    
    /**
     * @brief Връща символен низ, представляващ обект спрямо синтаксиса на JSON.
     * @param JSON символен низ за проверка
     * @param lenght дължина на симвония низ
     * @param index променлива от тип size_t подадена по референция, следяща кой подред е разглежданият символ от символния низ JSON
     * @return символен низ, представляващ обект
     */
    string getObject(const string& JSON,size_t lenght,size_t& index) const;
public:
    
    /**
     * @brief Проверява дали символен низ, представляващ обект спрямо синтаксиса на JSON, е валиден като използва частните членове функции.
     * @param JSON символен низ за проверка
     * @return връща булева стойност, която ако е истина, подаденият низ е валиден, ако е лъжа- невалиден.
     */
    bool IsValidJSON (const string& JSON) const;
};

#endif /* JSONvaildation_hpp */
