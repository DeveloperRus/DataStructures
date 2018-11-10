//
// Created by Apple on 23.05.2018.
//

#include "RingDoubleLinkedList.h"

RingDoubleLinkedList::RingDoubleLinkedList() {
    head = nullptr;
    tail = head;
    size = 0;
}

const int RingDoubleLinkedList::getType() const {
    return type;
}

void RingDoubleLinkedList::insert(const std::string &key) {
    if (head == nullptr) {
        auto *tmp = new NodeRingDoubleLinkedList;
        tmp->next = tmp;
        tmp->prev = tmp;
        tmp->line = key;
        head = tmp;
        tail = tmp;
        size++;
        return;
    }

    auto *tmp = new NodeRingDoubleLinkedList;
    tmp->next = head;
    head->prev = tmp;
    tmp->prev = tail;
    tail->next = tmp;
    tmp->line = key;
    head = tmp;
    size++;
}

void RingDoubleLinkedList::insert(int position, const std::string &key) {
    NodeRingDoubleLinkedList *currentNode = head;

    position %= (size + 1); // зацикливание

    for (int i = 1; i < position - 1; i++) // ищем узел до нужного нам узла
        currentNode = currentNode->next;

    if (position == 1) {
        insert(key); // вставка в начало
    } else {
        auto *temp = new NodeRingDoubleLinkedList;
        temp->next = currentNode->next;
        currentNode->next->prev = temp;
        currentNode->next = temp;
        temp->prev = currentNode;
        temp->line = key;
        size++;
    }
}

void RingDoubleLinkedList::insert(Base *list) {
    auto *tmp = dynamic_cast<RingDoubleLinkedList *>(list);

    tail->next = tmp->head;
    tmp->head->prev = tail;
    head->prev = tmp->tail;
    tmp->tail->next = head;
    tail = tmp->tail;
    size += tmp->size;
}

int RingDoubleLinkedList::getSize() const {
    return size;
}

void RingDoubleLinkedList::getList(std::ofstream &output) const {
    if(head == nullptr) {
        output << "NOTHING";
        return;
    }
    NodeRingDoubleLinkedList *tmp = head;
    output << "|" << tmp->line << "|";
    tmp = tmp->next;
    while (tmp != head) {
        output << "<->";
        output << "|" << tmp->line << "|";
        tmp = tmp->next;
    }
    output << "<->...";
}

void RingDoubleLinkedList::deleteAll() {
    NodeRingDoubleLinkedList* current = head;
    tail->next = nullptr;

    while(current != nullptr) {
        head = head->next;
        delete current;
        current = head;
    }
    head = nullptr;
    tail = nullptr;
}

void RingDoubleLinkedList::deleteFrom(int position) {
    NodeRingDoubleLinkedList *currentNode = head;

    position %= (size + 1); // зацикливание

    for (int i = 1; i < position; i++) // ищем узел до нужного нам узла
        currentNode = currentNode->next;

    if (currentNode == head) {
        NodeRingDoubleLinkedList* tmp = head;
        head = head->next;
        head->prev = tail;
        tail->next = head;
        delete tmp;
        return;
    }

    if (tail == currentNode) {
        tail->prev->next = head;
        tail = tail->prev;
        head->prev = tail;
        delete currentNode;
        return;
    }

    currentNode->prev->next = currentNode->next;
    currentNode->next->prev = currentNode->prev;
    delete currentNode;
}

std::string RingDoubleLinkedList::deleteKey() {
    std::string tmp = head->line;
    NodeRingDoubleLinkedList* t = head;
    head = head->next;
    tail = nullptr;
    delete t;
    size--;
    return tmp;
}
