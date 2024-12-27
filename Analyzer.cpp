#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "hash_table.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла." << endl;
        return 1;
    }

    Lexer lexer(inputFile);
    lexer.getHashTable().print();

    inputFile.close();

    return 0;
}