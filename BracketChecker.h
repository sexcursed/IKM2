#ifndef BRACKET_CHECKER_H
#define BRACKET_CHECKER_H

#include "CustomStructures.h"
#include <string>

struct BracketInfo {
    char bracket;
    int position;
};

// Функции валидации и проверки
void validateInput(const std::string& str);
int checkBracketSequence(const CustomCharList& list);

// Новые функции генерации и работы с файлами
std::string generateRandomBrackets(size_t length);
std::string readFromFile(const std::string& filename);

#endif
