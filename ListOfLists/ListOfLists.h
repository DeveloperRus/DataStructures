#ifndef LISTOFLISTS_LISTOFLISTS_H
#define LISTOFLISTS_LISTOFLISTS_H

#include "SimplyLinkedList.h"
#include "RingSimplyLinkedList.h"
#include "DoubleLinkedList.h"
#include "RingDoubleLinkedList.h"

/**
 * Узел главного списка (списка списков)
 */
struct NodeListOfLists {
    Base *head;            // Указатель на голову вложенного списка
    NodeListOfLists *next; // Указатель на следующий узел структуры
    NodeListOfLists *prev; // Указатель на предыдущий узел структуры
};

/**
 * Список списков
 */
class ListOfLists {
public:
    /**
     * Конструктор по умолчанию
     */
    ListOfLists();

    /**
     * Вставка в начало списка
     * @param list
     */
    void insert(Base* list);

    /**
     * Вставвка в список по позиции
     * @param position позиция
     * @param list вставляемый лист
     */
    void insert(int position, Base* list);

    /**
     * Вставка ключа в подсписок по позициям
     * @param position позиция списка в основном списке
     * @param positionList позиция ключа в вставляемом списке
     * @param key ключ
     */
    void insert(int position, int positionList, const std :: string& key);

    /**
     * Вывод подсписка в поток вывода по заданному формату
     * @param output поток вывода
     */
    void getList(std::ofstream& output) const;

    /**
     * Удаление ключа по позициям
     * @param position позиция списка
     * @param positionList позиция ключа в подсписке
     */
    void deleteFrom(int position, int positionList);

    /**
     * Удаление всех ключей из подсписка
     * @param position
     */
    void deleteAll(int position);

private:
    int size; // Колличество подсписков
    NodeListOfLists *head;
};

/**
 * Интерпритация входного файла по формату указанном в README.md
 * и вывод результата в выходной
 */
void Interpreter(std::ifstream&, ListOfLists&, std::ofstream&);

#endif //LISTOFLISTS_LISTOFLISTS_H
