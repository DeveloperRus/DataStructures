#ifndef LISTOFLISTS_RINGDOUBLELINKEDLIST_H
#define LISTOFLISTS_RINGDOUBLELINKEDLIST_H

#include "Base.h"

/**
 * Узел кольцевого двусвязного списка
 */
struct NodeRingDoubleLinkedList {
    std::string line;
    NodeRingDoubleLinkedList *next;
    NodeRingDoubleLinkedList *prev;
};

/*
 * Кольцевой двусвязный список
 */
class RingDoubleLinkedList : public Base {
public:
    /**
     * Конструктор по умолчанию
     */
    RingDoubleLinkedList();

    /**
     * Получения типа списка
     * @return
     */
    const int getType() const override;

    /**
     * Вставка ключа в список
     * @param key вставляемый ключ
     */
    void insert(const std::string &key) override;;

    /**
     * Вставка ключа по позиции
     * @param position позиция
     * @param key ключ
     */
    void insert(int position, const std::string &key) override;;

    /**
     * Подвешивание списков друг к другу
     * @param list подвешиваемый список
     */
    void insert(Base *list) override;;

    /**
     * Получить размер списка
     * @return размер списка
     */
    int getSize() const override;;

    /**
     * Вывести список в заданном формате в выходной поток
     * @param output выходной поток
     */
    void getList(std::ofstream &output) const override;;

    /**
     * Удаление всех ключей
     */
    void deleteAll() override;;

    /**
     * Удаление ключа по позиции
     * @param position позиция
     */
    void deleteFrom(int position) override;

private:
    static const char type = 3;    // Тип списка
    NodeRingDoubleLinkedList *head;
    NodeRingDoubleLinkedList *tail;
    int size;

    std::string deleteKey() override;
};

#endif //LISTOFLISTS_RINGDOUBLELINKEDLIST_H
