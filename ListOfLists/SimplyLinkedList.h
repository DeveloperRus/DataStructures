#ifndef LISTOFLISTS_SIMPLYLINKEDLIST_H
#define LISTOFLISTS_SIMPLYLINKEDLIST_H

#include "Base.h"

/**
 * Узел односвязного списка
 */
struct NodeSimplyLinkedList {
    std::string line;
    NodeSimplyLinkedList *next;
};

/**
 * Односвязный список
 */
class SimplyLinkedList : public Base {
public:
    /**
     * Конструктор по умолчанию
     */
    SimplyLinkedList();

    /**
     * Получить тип списка
     * @return тип списка
     */
    const int getType() const override;

    /**
     * Вставка ключа в начало списка
     * @param key ключ
     */
    void insert(const std::string &key) override;

    /**
     * Вставка ключа по позиции
     * @param position позиция
     * @param key ключ
     */
    void insert(int position, const std::string &key) override;

    /**
     * Подвешивание одного листа к другому
     * @param list подвешиваемый лист
     */
    void insert(Base* list) override;

    /**
     * Получение размера списка
     * @return размер
     */
    int getSize() const override;

    /**
     * Вывод списка в заданном формате в выходной поток
     * @param output выходной поток
     */
    void getList(std::ofstream& output) const override;

    /**
     * Удаление ключа по позиции
     * @param position позиция
     */
    void deleteFrom(int position) override;

    /**
     * Удаление всех ключей
     */
    void deleteAll() override;;

private:
    static const char type = 0; // Тип списка
    NodeSimplyLinkedList* head;
    NodeSimplyLinkedList* tail;
    int size;

    std::string deleteKey() override;
};

#endif //LISTOFLISTS_SIMPLYLINKEDLIST_H
