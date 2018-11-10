#include "DoubleLinkedList.h"

DoubleLinkedList::DoubleLinkedList() {
    head = nullptr;
    tail = head;
    size = 0;
}

const int DoubleLinkedList::getType() const {
    return type;
}

void DoubleLinkedList::insert(const std::string &key) {
    if (head == nullptr) {
        auto *tmp = new NodeDoubleLinkedList;
        tmp->next = nullptr;
        tmp->prev = nullptr;
        tmp->line = key;
        head = tmp;
        tail = tmp;
        size++;
        return;
    }

    auto *tmp = new NodeDoubleLinkedList;
    tmp->next = head;
    head->prev = tmp;
    tmp->prev = nullptr;
    tmp->line = key;
    head = tmp;
    size++;
}

void DoubleLinkedList::insert(int position, const std::string &key) {
    NodeDoubleLinkedList* currentNode = head;

    position %= (size + 1); // зацикливание

    for (int i = 1; i < position - 1; i++) // ищем узел до нужного нам узла
        currentNode = currentNode->next;

    if (position == 1) {
        insert(key); // вставка в начало
    }
    else {
        auto *temp = new NodeDoubleLinkedList;
        temp->next = currentNode->next;
        currentNode->next->prev = temp;
        currentNode->next = temp;
        temp->prev = currentNode;
        temp->line = key;
        size++;
    }
}

void DoubleLinkedList::insert(Base *list) {
    auto * tmp = dynamic_cast<DoubleLinkedList*>(list);

    tail->next = tmp->head;
    tmp->head->prev = tail;
    tail = tmp->tail;
    size += tmp->size;
}

int DoubleLinkedList::getSize() const {
    return size;
}

void DoubleLinkedList::getList(std::ofstream &output) const {
    if(head == nullptr) {
        output << "NOTHING";
        return;
    }
    NodeDoubleLinkedList* tmp = head;
    output << "|" << tmp->line << "|";
    tmp = tmp->next;
    while(tmp != nullptr) {
        output << "<->";
        output << "|" << tmp->line << "|";
        tmp = tmp->next;
    }
}

void DoubleLinkedList::deleteAll() {
    NodeDoubleLinkedList* current = head;

    while(current != nullptr) {
        head = head->next;
        delete current;
        current = head;
    }
    head = nullptr;
    tail = nullptr;
}

void DoubleLinkedList::deleteFrom(int position) {
    NodeDoubleLinkedList *currentNode = head;

    position %= (size + 1); // зацикливание

    for (int i = 1; i < position; i++) // ищем узел до нужного нам узла
        currentNode = currentNode->next;

    if (currentNode == head) {
        NodeDoubleLinkedList* tmp = head;
        head = head->next;
        head->prev = nullptr;
        delete tmp;
        return;
    }

    if (tail == currentNode) {
        tail->prev->next = nullptr;
        tail = tail->prev;
        delete currentNode;
        return;
    }

    currentNode->prev->next = currentNode->next;
    currentNode->next->prev = currentNode->prev;
    delete currentNode;
}

std::string DoubleLinkedList::deleteKey() {
    std::string tmp = head->line;
    NodeDoubleLinkedList* t = head;
    head = head->next;
    tail = nullptr;
    delete t;
    size--;
    return tmp;
}
