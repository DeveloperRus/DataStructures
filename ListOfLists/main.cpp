#include "ListOfLists.h"

int main() {
    ListOfLists lists;
    std::ifstream input("../test.txt");
    std:: ofstream output("../answer.txt");
    Interpreter(input, lists, output);
    return 0;
}