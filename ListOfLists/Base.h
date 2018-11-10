#ifndef LISTOFLISTS_BASE_H
#define LISTOFLISTS_BASE_H

#include <iostream>
#include <fstream>

/**
 * Базовый класс для обеспечения полиморфизма
 */
class Base {
public:
    virtual ~Base() = default;

    /**
     * Функция для определения типа списка
     * @return - возвращает тип списка
     */
    virtual const int getType() const = 0;

    /**
     * Вставка ключа в начало списка
     * @param key - вставляемый ключ
     */
    virtual void insert(const std :: string& key) = 0;

    /**
     * Вставка ключа по позиции
     * @param position - позиция
     * @param key - вставляемый ключ
     */
    virtual void insert(int position, const std :: string& key) = 0;

    /**
     * Сливание двух списков
     * @param list - сливаемый список
     */
    virtual void insert(Base* list) = 0;

    /**
     * Удаления узла списка
     * @return - возврат значения его ключа
     */
    virtual std::string deleteKey() = 0;

    /**
     * Функция определения размера списка
     * @return - возвращает размер
     */
    virtual int getSize() const = 0;

    /**
     * Функция вывода списка
     * @param output - поток вывода
     */
    virtual void getList(std::ofstream& output) const = 0;

    /**
     * Функция для удаления всех вхождений ключа
     * @param key - удаляемый ключ
     */
    virtual void deleteFrom(int position) = 0;

    /**
     * Функция для удлаения всего списка
     */
    virtual void deleteAll() = 0;
};

#endif //LISTOFLISTS_BASE_H
