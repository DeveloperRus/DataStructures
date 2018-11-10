#include "ListOfLists.h"

/**
 * Функция создания листа и записи в главный список
 * @param lists - главный список
 * @param command - строка содержащая название списка
 * @param position - позиция по которой вставляем побочный список,
 * если -1, то создаём новый узел главного списка
 */
void createList(ListOfLists& lists, std::string& command, int position = -1) {

    /* Если вставляем односвязный список */
    if (strstr(command.c_str(), "simpleLinkedList")) {
        std::string tmp; // переменная для хранения ключа
        auto* list = new SimplyLinkedList; // указатель на список
        const char* j = std::strchr(command.c_str(), ':') + 1; //  начало последовательности ключей

        while (j[0] == ' ') // ищем первый ключ
            j++;

        for(; j < command.c_str() + command.size(); j++) {
            if (j[0] == ' ') {
                (*list).insert(tmp); // вставляем ключ если он закончился
                tmp = ""; // обнуляем временную переренную
                while (j[0] == ' ') //  ищем новый ключ
                    j++;
                j--; // возвращаемся на шаг назад
                continue;
            }
            tmp += j[0]; // пока не закончился ключ
        }

        (*list).insert(tmp);
        if (position == -1)
            lists.insert(list);
        else
            lists.insert(position, list);
        return;
    }

    /* Если вставляем двусвязный список */
    if (strstr(command.c_str(), "doubleLinkedList")) {
        std::string tmp; // переменная для хранения ключа
        auto* list = new DoubleLinkedList;
        const char* j = std::strchr(command.c_str(), ':') + 1; //  начало последовательности ключей

        while (j[0] == ' ') // ищем первый ключ
            j++;

        for(; j < command.c_str() + command.size(); j++) {
            if (j[0] == ' ') {
                (*list).insert(tmp); // вставляем ключ если он закончился
                tmp = "";
                while (j[0] == ' ') //  ищем новый ключ
                    j++;
                j--; // возвращаемся на шаг назад
                continue;
            }
            tmp += j[0]; // пока не закончился ключ
        }

        (*list).insert(tmp);
        if (position == -1)
            lists.insert(list);
        else
            lists.insert(position, list);
        return;
    }

    /* Если вставляем кольцевой двусвязный список */
    if (strstr(command.c_str(), "ringDoubleLinkedList")) {
        std::string tmp; // переменная для хранения ключа
        auto* list = new RingDoubleLinkedList;
        const char* j = std::strchr(command.c_str(), ':') + 1; //  начало последовательности ключей

        while (j[0] == ' ') // ищем первый ключ
            j++;

        for(; j < command.c_str() + command.size(); j++) {
            if (j[0] == ' ') {
                (*list).insert(tmp); // вставляем ключ если он закончился
                tmp = "";
                while (j[0] == ' ') //  ищем новый ключ
                    j++;
                j--; // возвращаемся на шаг назад
                continue;
            }
            tmp += j[0]; // пока не закончился ключ
        }
        (*list).insert(tmp);

        if (position == -1)
            lists.insert(list);
        else
            lists.insert(position, list);
        return;
    }

    /* Если вставляем кольцевой односвязный список */
    if (strstr(command.c_str(), "ringSimpleLinkedList")) {
        std::string tmp; // переменная для хранения ключа
        auto* list = new RingSimplyLinkedList;
        const char* j = std::strchr(command.c_str(), ':') + 1; //  начало последовательности ключей

        while (j[0] == ' ') // ищем первый ключ
            j++;

        for(; j < command.c_str() + command.size(); j++) {
            if (j[0] == ' ') {
                (*list).insert(tmp); // вставляем ключ если он закончился
                tmp = "";
                while (j[0] == ' ') //  ищем новый ключ
                    j++;
                j--; // возвращаемся на шаг назад
                continue;
            }
            tmp += j[0]; // пока не закончился ключ
        }
        (*list).insert(tmp);
        if (position == -1)
            lists.insert(list);
        else
            lists.insert(position, list);
        return;
    }
}

/**
 * Интерпритация входного файла по заданному формату и вывод результата в выходной
 * @param input входной поток
 * @param lists главный список
 * @param output выходной поток
 */
void Interpreter(std::ifstream& input, ListOfLists& lists, std::ofstream& output) {
    std::string command;

    // Считывание команд и параметров независимо от количества пробелов между ними
    while(std::getline(input, command)) {
        if (strstr(command.c_str(), "insertList")) {
            createList(lists, command);
            continue;
        }

        else if (strstr(command.c_str(), "hangList")) {
            std :: string position;
            for (int i = 8;;) {
                while (command[i] == ' ') // проходим лишние пробелы
                    i++;
                while (command[i] != ' ') // Формируем число
                    position += command[i++];
                break;
            }
            createList(lists, command, atoi(position.c_str()));
            continue;
        }

        else if (command.find("insertKey") == 0) {
            std :: string position;
            std :: string position2;
            std :: string key;
            int i = 9;

            for (;;) {
                while (command[i] == ' ')
                    i++;
                while (command[i] != ' ')
                    position += command[i++];
                break;
            }

            for (;;) {
                while (command[i] == ' ')
                    i++;
                while (command[i] != ' ')
                    position2 += command[i++];
                break;
            }

            for (;i;) {
                while (command[i] == ' ' && i < command.size())
                    i++;
                while (command[i] != ' ' && i < command.size())
                    key += command[i++];
                break;
            }

            lists.insert(atoi(position.c_str()), atoi(position2.c_str()), key);
            continue;
        }

        else if (strstr(command.c_str(), "getLists")) {
            lists.getList(output);
            output << std::endl;
        }

        else if (strstr(command.c_str(), "deleteList")) {
            std :: string position;
            for (int i = 10;;) {
                while (command[i] == ' ')
                    i++;
                while (command[i] != ' ')
                    position += command[i++];
                break;
            }
            lists.deleteAll(atoi(position.c_str()));
            continue;
        }

        else if (strstr(command.c_str(), "deleteFrom")) {
            std :: string position;
            std :: string position2;
            int i = 10;

            for (;;) {
                while (command[i] == ' ')
                    i++;
                while (command[i] != ' ')
                    position += command[i++];
                break;
            }

            for (;;) {
                while (command[i] == ' ')
                    i++;
                while (command[i] != ' ')
                    position2 += command[i++];
                break;
            }

            lists.deleteFrom(atoi(position.c_str()), atoi(position2.c_str()));
            continue;
        }
    }
}