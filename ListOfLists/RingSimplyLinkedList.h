#ifndef LISTOFLISTS_RINGSIMPLYLINKEDLIST_H
#define LISTOFLISTS_RINGSIMPLYLINKEDLIST_H

#include "Base.h"

/**
 * Узел кольцевого односвязного списка
 */
struct NodeRingSimplyLinkedList {
    std::string line;
    NodeRingSimplyLinkedList *next;
};

/**
 * Кольцевой двусвязный список
 */
class RingSimplyLinkedList : public Base {
public:
    /**
     * Конструктор по умолчанию
     */
    RingSimplyLinkedList();

    /**
     * Получить тип списка
     * @return тип спика
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
     * Подвешивание одного списка к другому
     * @param list подвешиваемый список
     */
    void insert(Base* list) override;;

    /**
     * Получить размер списка
     * @return размер списка
     */
    int getSize() const override;;

    /**
     * Вывести список в заданном формате в поток вывода
     * @param output поток вывода
     */
    void getList(std::ofstream& output) const override;;

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
    static const char type = 1;     // Тип списка
    NodeRingSimplyLinkedList *head;
    NodeRingSimplyLinkedList *tail;
    int size;

    std::string deleteKey() override;;
};

#endif //LISTOFLISTS_RINGSIMPLYLINKEDLIST_H
