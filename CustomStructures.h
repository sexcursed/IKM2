#ifndef CUSTOM_STRUCTURES_H
#define CUSTOM_STRUCTURES_H

#include <stdexcept>
#include <cstddef>
#include "BracketException.h"

// Шаблонный класс динамического Стека на базе связного списка
template <typename T>
class CustomStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val, Node* n = nullptr) : data(val), next(n) {}
    };
    Node* topNode;
    size_t stackSize;

public:
    CustomStack() : topNode(nullptr), stackSize(0) {}
    
    ~CustomStack() { clear(); }

    // Запрет копирования во избежание некорректного дублирования указателей
    CustomStack(const CustomStack&) = delete;
    CustomStack& operator=(const CustomStack&) = delete;

    void push(const T& val) {
        topNode = new Node(val, topNode);
        stackSize++;
    }

    void pop() {
        if (isEmpty()) {
            throw BracketException(ErrorType::StackUnderflow, "Ошибка структуры: попытка удаления из пустого стека.");
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        stackSize--;
    }

    T top() const {
        if (isEmpty()) {
            throw BracketException(ErrorType::StackUnderflow, "Ошибка структуры: стек пуст.");
        }
        return topNode->data;
    }

    bool isEmpty() const { return topNode == nullptr; }
    size_t size() const { return stackSize; }
    
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// Собственный динамический список для хранения входных символов
class CustomCharList {
private:
    struct Node {
        char data;
        Node* next;
        Node(char val, Node* n = nullptr) : data(val), next(n) {}
    };
    Node* head;
    size_t listSize;

public:
    CustomCharList() : head(nullptr), listSize(0) {}
    ~CustomCharList() { clear(); }

    // Запрет копирования во избежание некорректного дублирования указателей
    CustomCharList(const CustomCharList&) = delete;
    CustomCharList& operator=(const CustomCharList&) = delete;

    void append(char val) {
        if (!head) {
            head = new Node(val);
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new Node(val);
        }
        listSize++;
    }

    char getAt(size_t index) const {
        if (index >= listSize) {
            throw BracketException(ErrorType::ListOutOfRange, "Ошибка: выход за границы списка.");
        }
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    size_t size() const { return listSize; }
    bool isEmpty() const { return head == nullptr; }
    
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        listSize = 0;
    }
};

#endif
