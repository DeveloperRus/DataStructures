#include "ListOfLists.h"

ListOfLists::ListOfLists() {
    head = nullptr;
    size = 0;
}

void ListOfLists::insert(Base *list) {
    // Стандартный алгоритм вставки в циклически двусвязный список
    auto* x = new NodeListOfLists;
    if (head == nullptr) {
        size++;
        x->head = list;
        x->next = x;
        x->prev = x;
        head = x;
        return;
    }
    size++;
    x->head = list;
    x->next = head;
    x->prev = head->prev;
    head->prev->next = x;
    head = x;
}

void ListOfLists::insert(int position, Base *list) {
    // Стандартный алгоритм вставки в циклически двусвязный список
    NodeListOfLists* tmp = head;

    for (int i = 1; i < position; i++)
        tmp = tmp->next;

    if(tmp->head->getType() == list->getType()) {
        tmp->head->insert(list);
        return;
    }

    while(list->getSize() != 0) {
        tmp->head->insert(list->deleteKey());
    }

}

void ListOfLists::insert(int position, int positionList, const std::string &key) {
    NodeListOfLists* tmp = head; // временная переменная для пробега по основному списку

    for (int i = 0; i < position - 1; i++) // ищем нужный узел
        tmp = tmp->next;

    tmp->head->insert(positionList, key);
}

void ListOfLists::getList(std::ofstream &output) const {
    NodeListOfLists* tmp = head;
    output << 1 << "->";
    tmp->head->getList(output);
    output << std::endl;
    tmp = tmp->next;
    for (int i = 2; tmp != head; i++) {
        output << "|" << std::endl;
        output << i << "->";
        tmp->head->getList(output);
        output << std::endl;
        tmp = tmp->next;
    }
}

void ListOfLists::deleteFrom(int position, int positionList) {
    NodeListOfLists* current = head; // временная переменная для пробега по основному списку

    position %= (size + 1); // зацикливание

    for (int i = 1; i < position; i++) // ищем нужный узел
        current = current->next;

    current->head->deleteFrom(positionList);
}

void ListOfLists::deleteAll(int position) {
    NodeListOfLists* current = head; // временная переменная для пробега по основному списку

    position %= (size + 1); // зацикливание

    for (int i = 1; i < position; i++) // ищем нужный узел
        current = current->next;

    current->head->deleteAll();
}
