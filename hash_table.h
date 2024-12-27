#pragma once
#include "Token.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

class HashTable {
private:
    struct Node {
        Token token;
        Node* next;
        Node(const Token& t) : token(t), next(nullptr) {}
    };

    Node** table;
    size_t size = 0;
    int count = 0;

    size_t hashFunction(const std::string& key) const {
        unsigned long hash = 317;
        int c;
        const char* s = key.c_str();

        while ((c = *s++)) {
            hash = ((hash << 5) + hash) + c;
        }
        return (hash) % size;
    }

    void rehash() {
        size_t newSize = size * 2;
        while (!isPrime(newSize)) {
            newSize++;
        }

        Node** newTable = new Node * [newSize]();
        for (size_t i = 0; i < newSize; ++i) {
            newTable[i] = nullptr;
        }

        size_t oldSize = size;
        size = newSize;

        for (size_t i = 0; i < oldSize; ++i) {
            Node* current = table[i];
            while (current) {
                Node* next = current->next;
                size_t newIndex = hashFunction(current->token.getLexem());
                while (newTable[newIndex] != nullptr) {
                    newIndex = (newIndex + 1) % newSize;
                }
                newTable[newIndex] = current;
                current->next = nullptr;

                current = next;
            }
        }

        delete[] table;
        table = newTable;
    }

    bool isPrime(size_t n) const {
        if (n <= 1) return false;
        for (size_t i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }


public:

    HashTable() {
        size = 101;
        table = new Node * [size];
        for (size_t i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {}

    void insert(const Token& token) {
        if (count >= size * 0.5) {
            rehash();
        }
        size_t index = hashFunction(token.value);
        while (table[index] != nullptr) {
            if (table[index]->token.value == token.value) {
                return;
            }
            index = (index + 1) % size;
        }

        Node* newNode = new Node(token);
        table[index] = newNode;
        count++;

    }

    Token* find(const std::string& key) {
        size_t index = hashFunction(key);
        Node* current = table[index];
        while (current) {
            if (current->token.value == key) {
                return &current->token;
            }
            current = current->next;
        }
        return nullptr;
    }

    void print() const {
        ofstream outputFile("output.txt");
        if (!outputFile.is_open()) {
            cerr << "Пробема открытия файла!" << endl;
            return;
        }

        outputFile << "Тип лексемы | Лексема    | Индекс в хеш-табице" << endl;
        for (size_t i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current) {
                if (current->token.getLexemType() == "ERRORS") {
                    outputFile << setw(11) << current->token.getLexemType() << " | "
                        << setw(10) << current->token.value << " | " << endl;
                    current = current->next;
                }
                else {
                    outputFile << setw(11) << current->token.getLexemType() << " | "
                        << setw(10) << current->token.value << " | " << i << endl;
                    current = current->next;
                }
            }
        }
        outputFile.close();
    }
};