#ifndef FIBONACCIHEAP_FIBONACCIHEAP_H
#define FIBONACCIHEAP_FIBONACCIHEAP_H

#include <functional>
#include <cmath>

/**
 * Узел кучи
 * @tparam Type - тип хранимого ключа
 */
template <typename Type>
struct Node {
    /** Хранимый ключ */
    Type key;
    /** Указатель на родительский узел */
    Node* parent;
    /** Указатель на один из дочерних узлов */
    Node* child;
    /** Указатель на левый узел того же предка */
    Node* left;
    /** Указатель на правый узел того же предка */
    Node* right;
    /** Степень вершины */
    size_t degree;
    /** Был ли удален ребенок в процессе изменения ключа этой вершины */
    bool mark;
};

/**
 * Контейнер "куча Фибоначи"
 * @tparam Type - тип хранимых ключей
 * @tparam Compare - компаратор для упорядочивания элементов
 */
template <class Type, class Compare = std::less<Type>>
class FibonacciHeap {
public:

    /**
     * Констркутор по умолчанию
     */
    FibonacciHeap() {
        head = nullptr;
        size = 0;
    };

    /**
     * Вставка узла в кучу
     * @param node - узел
     */
    void insert(Node<Type>* node) {
        if(size == 0) {
            head = node;
            head->left = node;
            head->right = node;
        }
        else {
            Node<Type>* previousRight = head->right; // Запоминаем соседний правый элемент

            // Меняем указатели для вставки узла
            head->right = node;
            node->left = head;
            node->right = previousRight;
            previousRight->left = node;
        }

        if (compare(node->key, head->key))
            head = node;


        // Очищаем данные узла, так как этот узел мог
        // находиться в какой либо куче, сохранив предыдущие указатели,
        // что привело бы к неправильной работе нашей кучи.
        node->parent = nullptr;
        node->child = nullptr;
        node->degree = 0;
        node->mark = false;

        size++;
    }

    /**
     * Функция для просмотра приоритетного узла
     * @return - указатель на приоритетный узел
     */
    Node<Type>* getMin() const {
        return head;
    }

    /**
     * Сливание двух куч
     * @param heap - сливаемая куча
     */
    void merge(FibonacciHeap* heap) {
        if (heap == nullptr || heap->size == 0)
            return;

        if (size == 0) {
            this->head = heap->head;
            this->size = heap->size;
        }
        else {
            unionLists(head, heap->head);
            size += heap->size;
            if (compare(heap->head->key, head->key))
                head = heap->head;
        }

        heap = nullptr;
    }

    /**
     * Функция для извлечения приоритетного узла
     * @return - указатель на приоритетный узел
     */
    Node<Type>* extractMin() {
        if(head == nullptr)
            return nullptr;

        Node<Type>* previousMin = head; // Запоминаем указатель на текущий минимальный ключ

        unionLists(head, head->child, true);

        head->left->right = head->right;
        head->right->left = head->left;
        head->child = nullptr;
        head = previousMin->right;
        size--;

        if(size == 0) {
            head = nullptr;
            return previousMin;
        }

        consolidate();

        return previousMin;
    }

    /**
     * Уплотнение списка корней до тех пор,
     * пока все корни не будут иметь различные
     * значния degree
     */
    void consolidate() {
        if(head == nullptr)
            return;

        // Создание вспомогательного массива,
        // для которого выполняется свойство:
        // если array[i] = Node, то Node.degree = i
        double f = 1.61803;
        auto sizeArray = static_cast<size_t>(ceil(log2(size) / log2(f)));
        auto array = new Node<Type>*[sizeArray + 3];

        for (int i = 0; i < sizeArray + 3; ++i)
            array[i] = nullptr;

        Node<Type>* current = head;     // Указатель для пробега по списку
        Node<Type>* current2 = nullptr; // Вспомогательный указатель для проверки обхода всего списка

        bool flag = true;
        while(flag) {
            size_t index = current->degree;

            while(array[index] != nullptr) {
                Node<Type>* tmp = array[index];

                if(tmp == current) {
                    break;
                }
                else if(compare(tmp->key, current->key)) {
                    // Смена указателей местами
                    // чтобы текущий был приоритетней
                    Node<Type>* pt = current;
                    current = tmp;
                    tmp = pt;
                }

                link(tmp, current);
                array[index++] = nullptr;
            }

            array[current->degree] = current;
            current2 = current->right;

            flag = false;
            while(current2 != current){
                // Так как в нашем списке не может лежать несколько узлов
                // с одинаковой степенью, то это служит критерием,
                // что мы обошли не весь список
                if(array[current2->degree] != current2) {
                    flag = true;
                    current = current2;
                    break;
                }
                current2 = current2->right;
            }
        }

        head = nullptr;

        for (long int i = sizeArray + 2; i >= 0; i--) {
            if(array[i] == nullptr) {
                continue;
            }
            else if(head == nullptr) {
                head = array[i];
            }
            else if(!compare(head->key, array[i]->key)){
                head = array[i];
            }
        }
    }

    /**
     * Увеличние приоритета ключа в узле
     * (Ключи меньшего приоритета игнорируются)
     * @param key - новое значение ключа
     * @param x - узел
     */
    void decreaseKey(const Type key, Node<Type>* x) {
        if(size == 0 ||  compare(x->key, key))
            return;
        x->key = key;

        Node<Type>* y = x->parent;

        // Вырезания узла X из списка детей его родителя
        // в случае если у него есть родитель и новый
        // ключ обладает большим приоритетом
        if(y != nullptr && compare(x->key, y->key)) {
            cut(x, y);
            cascadingCut(y);
        }

        if(compare(x->key, head->key))
            head = x;
    }

    /**
     * Getter получения размера кучи
     * @return - размер кучи (колличество элементов)
     */
    size_t getSize() const {
        return size;
    }

private:
    /** Указатель на приоритетный элемент. */
    Node<Type>* head;
    /** Колличество элементов в куче. */
    size_t size;
    /** Компаратор для упорядочивания элемментов. */
    Compare compare;

    /**
     * Объединение списков вершин
     * @param first  - первый список
     * @param second - второй список
     * @param flag - определяет, нужно ли удалять у второго списка
     * указатели на родителей вершин
     */
    void unionLists(Node<Type>* first, Node<Type>* second, bool flag = false) {
        if (second == nullptr || first == nullptr)
            return;

        if (flag) {
            Node<Type>* current = second->right; // Указатель для пробегания списка по соседним узлам

            while(current != second) {
                current->parent = nullptr;
                current = current->right;
            }
            current->parent = nullptr;
        }

        // Запоминаем текущие крайние узлы у списков
        Node<Type>* head1 = first;        // Голова первого списка
        Node<Type>* tail1 = first->left;  // Конец первого списка
        Node<Type>* head2 = second;       // Голова второго списка
        Node<Type>* tail2 = second->left; // Конец второго списка

        // Меняем указатели местами для слияния
        tail1->right = head2;
        head2->left = tail1;
        head1->left = tail2;
        tail2->right = head1;
    }

    /**
     * Связывание узла first со списком детей вершины second
     * @param first
     * @param second
     */
    void link(Node<Type>* first, Node<Type>* second) {
        // Забываем про узел first в списке
        // к которому он принадлежит
        first->right->left = first->left;
        first->left->right = first->right;

        // Забываем соседних вершин у узла first
        // (Изолируем его от других)
        first->right = first;
        first->left = first;
        first->mark = false;

        // Сливаем узел first со списком детей
        // узла second, делая его родителем first
        first->parent = second;
        if(second->child == nullptr)
            second->child = first;
        else
            unionLists(second->child, first);
        second->degree += 1;
    }

    /**
     * Вырезание узла из списка
     * @param x - вырезаемаый узел
     * @param y - родитель узла X
     */
    void cut(Node<Type>* x, Node<Type>* y) {

        // Забываем у узла Y про ребенка X
        y->child = x->right;
        if(x == x->right)
            y->child = nullptr;
        y->degree--;

        // Забываем соседних вершин у узла X
        // (Изолируем его от других)
        x->left->right = x->right;
        x->right->left = x->left;
        x->right = x;
        x->left = x;
        x->parent = nullptr;
        x->mark = false;

        unionLists(head, x); // Вставляем вырезанную вершину и ее поддерево в корневой список
    }

    /**
     * Каскадное вырезание (Рекурсия)
     * @param y - узел
     */
    void cascadingCut(Node<Type>* y) {
        Node<Type>* z = y->parent;

        if (z == nullptr) {
            return;
        }
        else if (!y->mark) {
            y->mark = true;
        }
        else {
            cut(y, z);
            cascadingCut(z);
        }
    }

};

#endif //FIBONACCIHEAP_FIBONACCIHEAP_H
