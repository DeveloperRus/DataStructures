#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>
#include <fstream>

/**
 * Узел дерева
 * @tparam Type - тип хранимого ключа
 */
template <class Type>
struct Node {
    Type key;             // ключ
    Node* left;           // указатель на левое поддерево
    Node* right;          // указатель на правое поддерево
    long long int height; // высота дерева от данного узла
};

/**
 * AVLTree
 * @tparam Type - тип хранимых ключей
 * @tparam Compare - компаратор для упорядочивания элементов
 */
template <class Type, class Compare = std::less<Type>>
class AVLTree {
public:

    /**
     * Конструктор по умолчанию
     */
    AVLTree() {
        head = nullptr;
        size = 0;
    }

    /**
     * Вставка ключа в дерево
     * @param key - ключ
     */
    void insert(const Type key){
        insertNode(head, key); // Вызов вспомогательной фунции для рекурсии по узлам
    }

    /**
     * Удаления ключа из дерева
     * @param key - ключ
     */
    void remove(const Type key){
        deleteNode(head, key); // Вызов вспомогательной фунции для рекурсии по узлам
    }

    /**
     * Проверка на существования ключа
     * @param key ключ
     * @return результат проверки
     */
    bool exist(const Type key) {
        return existNode(head, key) != nullptr; // Проверка на существование с рекурсией
    }

private:
    /** Указатель на корень дерева */
    Node<Type>* head;
    /** Размер дерева */
    size_t size;
    /** Компаратор для упорядочивания элемментов */
    Compare compare;

    /**
     * Следующий по возрастанию элемент в дереве
     * @param node узел
     * @return
     */
    Node<Type>* next(Node<Type>* node) {
        Node<Type>* current = node->right;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    /**
     * Высота дерева от данного узла
     * @param node узел
     * @return высота
     */
    long long int height(const Node<Type>* const node) const {
        return node == nullptr ? 0 : node->height;
    }

    /**
     * Характеристика баланса дерева от данного узла (разность высот его поддеревьев)
     * @param node узел
     * @return разность высот
     */
    long long int getBalance(const Node<Type>* const node) const {
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }

    /**
     * Малый левый поворот
     * @param node узел у которого выполняем поворот
     */
    void leftRotate(Node<Type>*& node) {
        Node<Type>* result = node->right;
        Node<Type>* tmp = result->left;

        // Изменяем потомков
        result->left = node;
        node->right = tmp;

        // Изменяем высоту
        node->height = std :: max(height(node->left), height(node->right)) + 1;
        result->height = std :: max(height(result->left), height(result->right)) + 1;

        // Присваивание нового корня
        node = result;
    }

    /**
     * Малый правый поворот
     * @param node узел у которого выполняем поворот
     */
    void rightRotate(Node<Type>*& node) {
        Node<Type>* result = node->left;
        Node<Type>* tmp = result->right;

        // Изменяем потомков
        result->right = node;
        node->left = tmp;

        //  Изменяем высоту
        node->height = std :: max(height(node->left), height(node->right)) + 1;
        result->height = std :: max(height(result->left), height(result->right)) + 1;

        // Присваивание нового корня
        node = result;
    }

    /**
     * Рекурсивная вставка ключа
     * @param node вершина поддерева куда производится вставка
     * @param key вставляемый ключ
     */
    void insertNode(Node<Type>*& node, const Type key) {
        /* Если не существует узла */
        if (node == nullptr) {
            node = new Node<Type>;
            node->key   = key;
            node->left   = nullptr;
            node->right  = nullptr;
            node->height = 1;
        }

        // Спускамся вниз по дереву
        if (key < node->key)
            insertNode(node->left, key);
        else if (key > node->key)
            insertNode(node->right, key);

        node->height = 1 + std :: max(height(node->left), height(node->right));


        long long int balance = getBalance(node);

        // Определение нужного поворота
        if (balance > 1 && key < node->left->key) {
            rightRotate(node);
            return;
        }
        if (balance < -1 && key > node->right->key) {
            leftRotate(node);
            return;
        }
        if (balance > 1 && key > node->left->key) {
            leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            rightRotate(node->right);
            return leftRotate(node);
        }
    }

    /**
     * Рекурсивное удаление ключа
     * @param node вершина поддерева откуда производится удаление
     * @param key удаляемый ключ
     */
    void deleteNode(Node<Type>*& node, Type key) {
        if (node == nullptr)
            return;

        if ( key < node->key )
            deleteNode(node->left, key);
        else if( key > node->key )
            deleteNode(node->right, key);
        else {
            // Удаление ключа
            if( (node->left == nullptr) || (node->right == nullptr) ) {
                Node<Type> *temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp;

                delete temp;
            } else {
                Node<Type>* temp = next(node);

                node->key = temp->key;

                deleteNode(node->right, temp->key);
            }
        }

        if (node == nullptr)
            return;

        node->height = 1 + std :: max(height(node->left), height(node->right));

        long long int balance = getBalance(node);

        // Определение нужного поворота
        if (balance > 1 && getBalance(node->left) >= 0) {
            rightRotate(node);
            return;
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            leftRotate(node->left);
            rightRotate(node);
            return;
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            leftRotate(node);
            return;
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            rightRotate(node->right);
            leftRotate(node);
            return;
        }
    }

    Node<Type>* existNode(Node<Type> *&node, const Type key) {
        if (node == nullptr)
            return nullptr;
        if (node->key == key)
            return node;
        if (node->key > key)
            return existNode(node->left, key);
        else
            return existNode(node->right, key);
    }
};

#endif //AVLTREE_AVLTREE_H
