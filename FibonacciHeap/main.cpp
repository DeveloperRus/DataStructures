#include <iostream>
#include <fstream>
#include <queue>
#include "FibonacciHeap.h"

struct Vertex;

/**
 * Ребро графа
 */
struct Edge {
    /** Вес ребра */
    long long int weight;
    /** Начало ребра */
    Node<Vertex>* beginVertex;
    /** Конец ребра */
    Node<Vertex>* finishVertex;
    /** Следующее инцидентное ребро */
    Edge* nextEdge;

};

/**
 * Вершина графа
 */
struct Vertex {
    /** Номер вершины в графе */
    size_t vertexNumber = 0;
    /** Расстояние до этой вершины до заданной (В начале бесконечность) */
    long long int distance = LLONG_MAX;
    /** Указатель на начало списка инцидентных ребер */
    Edge* listEdges = nullptr;

    /**
     * Перезагрузка оператора "<" для возможности
     * упорядочивания элементов в куче, так как
     * std::less использует оператор сравнения
     * при желании можно изменить компаратор
     * @param rhs
     * @return
     */
    bool operator<(const Vertex& rhs) const {
        return this->distance < rhs.distance;
    }
};

/**
 * Граф на основе списка ребер
 */
class Graph {
public:

    /**
     * Конструктор Графа с параметрами
     * @param quantityVertex - колличество вершин в графе
     * @param oriented - ориентированный ли граф
     */
    Graph(const size_t quantityVertex, bool oriented) : quantityVertex(quantityVertex), oriented(oriented) {
        vertexes = new Node<Vertex> [quantityVertex + 1];
        quantityEdge = 0;

        for (size_t i = 0; i < quantityVertex + 1; ++i) {
            vertexes[i].key.vertexNumber = i;
        }
    }

    /**
     * Вставка ребра в граф
     * @param beginVertex - начало ребра
     * @param finishVertex - конец ребра
     * @param weight - вес ребра
     */
    void insertEdge(const size_t beginVertex, const size_t finishVertex, const long long int weight) {
        auto edge = new Edge();

        // Присвоение указателей на нужные вершины
        edge->beginVertex = &vertexes[beginVertex];
        edge->finishVertex = &vertexes[finishVertex];
        edge->weight = weight;

        // Вставка ребра в начало списка ребер
        if (vertexes[beginVertex].key.listEdges == nullptr) {
            edge->nextEdge = nullptr;
            vertexes[beginVertex].key.listEdges = edge;
        }
        else {
            edge->nextEdge = vertexes[beginVertex].key.listEdges;
            vertexes[beginVertex].key.listEdges = edge;
        }

        // Если граф неориентированный, то повторная вставка ребра
        // но с другим началом и концом
        if (!oriented) {
            auto edge2 = new Edge();
            edge2->beginVertex = &vertexes[finishVertex];
            edge2->finishVertex = &vertexes[beginVertex];
            edge2->weight = weight;

            if (vertexes[finishVertex].key.listEdges == nullptr) {
                edge2->nextEdge = nullptr;
                vertexes[finishVertex].key.listEdges = edge2;
            }
            else {
                edge2->nextEdge = vertexes[finishVertex].key.listEdges;
                vertexes[finishVertex].key.listEdges = edge2;
            }
        }

        quantityEdge++;
    }

    /**
     * Алгоритм Дейкстры
     * Расстояние от заданной вершины до каждой
     * @param beginVertex - заданная вершина
     * @param output - файл для вывода результата
     */
    void Dijkstra(size_t beginVertex, std::ofstream& output) {
        FibonacciHeap<Vertex> heap;
        Edge* current = vertexes[beginVertex].key.listEdges;

        // Массив который характеризует в каком состоянии
        // находятся вершины
        // 0 - Не рассматривали - White
        // 1 - в куче (в обработке) - Gray
        // 2 - обработана - Black
        // Используем char для экономии памяти
        auto mark = new char[quantityVertex + 1];
        for (size_t j = 0; j < quantityVertex + 1; ++j) {
            mark[j] = 0;
        }

        vertexes[beginVertex].key.distance = 0;
        mark[beginVertex] = 2;

        while(current != nullptr) {
            if (mark[current->finishVertex->key.vertexNumber] == 1) {
                if (current->weight < current->finishVertex->key.distance) {
                    auto tmp = new Vertex;

                    // Запоминаем информацию у прошлого ключа
                    // чтобы сохранить корректность алгоритма
                    (*tmp).vertexNumber = current->finishVertex->key.vertexNumber;
                    (*tmp).distance = current->weight;
                    (*tmp).listEdges = current->finishVertex->key.listEdges;

                    heap.decreaseKey((*tmp), current->finishVertex);
                }
            }
            else if (mark[current->finishVertex->key.vertexNumber] == 0) {
                current->finishVertex->key.distance = current->weight;
                heap.insert(current->finishVertex);
                mark[current->finishVertex->key.vertexNumber] = 1;
            }

            current = current->nextEdge;
        }

        while(heap.getSize() != 0) {
            Node<Vertex>* currentNode = heap.extractMin();

            mark[currentNode->key.vertexNumber] = 2;
            current = currentNode->key.listEdges;

            while(current != nullptr) {
                if (mark[current->finishVertex->key.vertexNumber] == 0) {
                    current->finishVertex->key.distance = currentNode->key.distance + current->weight;
                    heap.insert(current->finishVertex);
                    mark[current->finishVertex->key.vertexNumber] = 1;
                }
                else if (mark[current->finishVertex->key.vertexNumber] == 1) {
                    if (current->weight < current->finishVertex->key.distance) {
                        auto tmp = new Vertex;

                        // Запоминаем информацию у прошлого ключа
                        // чтобы сохранить корректность алгоритма
                        (*tmp).vertexNumber = current->finishVertex->key.vertexNumber;
                        (*tmp).distance = current->weight + currentNode->key.distance;
                        (*tmp).listEdges = current->finishVertex->key.listEdges;

                        heap.decreaseKey(*tmp, current->finishVertex);
                    }
                }

                current = current->nextEdge;
            }
        }

        // Выводим результат в файл
        for (size_t i = 1; i < quantityVertex + 1; ++i) {
            output << vertexes[i].key.distance << " ";
        }
    }

private:
    /** Массив вершин */
    Node<Vertex>* vertexes;
    /** Колличество вершин */
    size_t quantityVertex;
    /** Коллиечство ребер */
    size_t quantityEdge;
    /** Оринтированный ли граф */
    bool oriented;
};

int main() {
    size_t n, m, beginVertex, finishVertex;
    long long int weight;

    std::ifstream input("pathbgep.in");
    input >> n >> m;

    Graph graph(n, false);

    for (size_t i = 0; i < m; ++i) {
        input >> beginVertex >> finishVertex >> weight;
        graph.insertEdge(beginVertex, finishVertex, weight);
    }

    std::ofstream output("pathbgep.out");
    graph.Dijkstra(1, output);

    return 0;
}