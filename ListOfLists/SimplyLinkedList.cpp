#include "SimplyLinkedList.h"

SimplyLinkedList::SimplyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

const int SimplyLinkedList::getType() const {
    return type;
}

void SimplyLinkedList::insert(const std::string &key) {
    if (head == nullptr) {
        auto *tmp = new NodeSimplyLinkedList;
        tmp->next = nullptr;
        tmp->line = key;
        head = tmp;
        tail = tmp;
        size++;
        return;
    }

    auto *tmp = new NodeSimplyLinkedList;
    tmp->next = head;
    tmp->line = key;
    head = tmp;
    size++;
}

void SimplyLinkedList::insert(int position, const std::string &key) {
    NodeSimplyLinkedList *currentNode = head;

    position %= (size + 1); // зацикливание

    for (int i = 1; i < position - 1; i++) // ищем узел до нужного нам узла
        currentNode = currentNode->next;

    if (position == 1) {
        insert(key); // вставка в начало
    }
    else {
        auto *temp = new NodeSimplyLinkedList;
        temp->next = currentNode->next;
        currentNode->next = temp;
        temp->line = key;
        size++;
    }
}

void SimplyLinkedList::insert(Base *list) {
    auto * tmp = dynamic_cast<SimplyLinkedList*>(list);

    tail->next = tmp->head;
    tail = tmp->tail;
    size += tmp->size;
}

int SimplyLinkedList::getSize() const {
    return size;
}

void SimplyLinkedList::getList(std::ofstream &output) const {
    if(head == nullptr) {
        output << "NOTHING";
        return;
    }
    NodeSimplyLinkedList* tmp = head;
    output << "|" << tmp->line << "|";
    tmp = tmp->next;
    while(tmp != nullptr) {
        output << "->";
        output << "|" << tmp->line << "|";
        tmp = tmp->next;
    }
}

void SimplyLinkedList::deleteFrom(int position) {
    NodeSimplyLinkedList *currentNode = head;
    NodeSimplyLinkedList* currentPrev = nullptr;

    position %= (size + 1); // зацикливание

    for (int i = 1; i < position; i++) {// ищем узел до нужного нам узла
        currentPrev = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == head) {
        NodeSimplyLinkedList* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }

    if (tail == currentNode)
        tail = currentPrev;

    currentPrev->next = currentNode->next;
    delete currentNode;
}

void SimplyLinkedList::deleteAll() {
    NodeSimplyLinkedList* current = head;

    while(current != nullptr) {
        head = head->next;
        delete current;
        current = head;
    }
    head = nullptr;
    tail = nullptr;
}

std::string SimplyLinkedList::deleteKey() {
    std::string tmp = head->line;
    NodeSimplyLinkedList* t = head;
    head = head->next;
    tail = nullptr;
    delete t;
    size--;
    return tmp;
}
