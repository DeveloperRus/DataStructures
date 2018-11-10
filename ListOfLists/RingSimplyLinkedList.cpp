#include "RingSimplyLinkedList.h"

RingSimplyLinkedList::RingSimplyLinkedList() {
    head = nullptr;
    tail = head;
    size = 0;
}

const int RingSimplyLinkedList::getType() const {
    return type;
}

void RingSimplyLinkedList::insert(const std::string &key) {
    auto * tmp = new NodeRingSimplyLinkedList;
    if(head == nullptr) {
        tmp->line = key;
        tmp->next = tmp;
        head = tmp;
        tail = tmp;
        size++;
        return;
    }
    tmp->line = key;
    tmp->next = head;
    tail->next = tmp;
    head = tmp;
    size++;
}

void RingSimplyLinkedList::insert(int position, const std::string &key) {
    NodeRingSimplyLinkedList* currentNode = head;

    position %= (size + 1); // зацикливание

    for (int i = 1; i < position - 1; i++) // ищем узел до нужного нам узла
        currentNode = currentNode->next;

    if (position == 1) {
        insert(key); // вставка в начало
    }
    else {
        auto *temp = new NodeRingSimplyLinkedList;
        temp->next = currentNode->next;
        currentNode->next = temp;
        temp->line = key;
        size++;
    }
}

void RingSimplyLinkedList::insert(Base *list) {
    auto * tmp = dynamic_cast<RingSimplyLinkedList*>(list);

    tail->next = tmp->head;
    tmp->tail->next = head;
    tail = tmp->tail;
    size += tmp->size;
}

int RingSimplyLinkedList::getSize() const {
    return size;
}

void RingSimplyLinkedList::getList(std::ofstream &output) const {
    if(head == nullptr) {
        output << "NOTHING";
        return;
    }
    NodeRingSimplyLinkedList* tmp = head;
    output << "|" << tmp->line << "|";
    tmp = tmp->next;
    while(tmp != head) {
        output << "->";
        output << "|" << tmp->line << "|";
        tmp = tmp->next;
    }
    output << "->...";
}

void RingSimplyLinkedList::deleteFrom(int position) {
    NodeRingSimplyLinkedList *currentNode = head;
    NodeRingSimplyLinkedList* currentPrev = nullptr;

    position %= (size + 1); // зацикливание

    for (int i = 1; i < position; i++) {// ищем узел до нужного нам узла
        currentPrev = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == head) {
        NodeRingSimplyLinkedList* tmp = head;
        head = head->next;
        tail->next = head;
        delete tmp;
        return;
    }

    if (tail == currentNode)
        tail = currentPrev;

    currentPrev->next = currentNode->next;
    delete currentNode;
}

void RingSimplyLinkedList::deleteAll() {
    NodeRingSimplyLinkedList* current = head;
    tail->next = nullptr;

    while(current != nullptr) {
        head = head->next;
        delete current;
        current = head;
    }
    head = nullptr;
    tail = nullptr;
}

std::string RingSimplyLinkedList::deleteKey() {
    std::string tmp = head->line;
    NodeRingSimplyLinkedList* t = head;
    head = head->next;
    tail = nullptr;
    delete t;
    size--;
    return tmp;
}
