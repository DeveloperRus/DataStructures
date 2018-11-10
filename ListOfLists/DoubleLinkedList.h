#ifndef LISTOFLISTS_DOUBLELINKEDLIST_H
#define LISTOFLISTS_DOUBLELINKEDLIST_H

#include "Base.h"

/**
 * Узел двусвязного списка
 */
struct NodeDoubleLinkedList {
    std::string line;
    NodeDoubleLinkedList *next;
    NodeDoubleLinkedList *prev;
};

/**
 * Двусвязный список
 */
class DoubleLinkedList : public Base {
public:
    /**
     * Конструктор по умолчанию
     */
    DoubleLinkedList();

    /**
     * Тип списка (хранится в статической переменной)
     * @return
     */
    const int getType() const override;

    /**
     * Вставка ключа в начало списка
     * @param key ключ
     */
    void insert(const std :: string& key) override;;

    /**
     * Вставка ключа по позиции
     * @param position позиция
     * @param key ключ
     */
    void insert(int position, const std :: string& key) override;;

    /**
     * Подвешивание списка к исходному
     * @param list Подвешиваемый список
     */
    void insert(Base* list) override;;

    /**
     * Размер списка
     * @return размер
     */
    int getSize() const override;;

    /**
     * Вывод списка в поток вывода
     * @param output поток вывода
     */
    void getList(std::ofstream& output) const override;;

    /**
     * Удаление всех элементов из списка
     */
    void deleteAll() override;;

    /**
     * Удаление ключа по позиции
     * @param position позиция
     */
    void deleteFrom(int position) override;

private:
    static const char type = 2; // Переменная для типа списка
    NodeDoubleLinkedList *head;
    NodeDoubleLinkedList *tail;
    int size;

    std::string deleteKey() override;
};

#endif //LISTOFLISTS_DOUBLELINKEDLIST_H
