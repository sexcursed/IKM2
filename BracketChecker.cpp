#include "BracketChecker.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

void validateInput(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("Ошибка: введена пустая строка.");
    }
    for (char ch : str) {
        if (ch != '(' && ch != ')' && ch != '[' && ch != ']' && ch != '{' && ch != '}') {
            throw std::invalid_argument("Ошибка: строка содержит недопустимые символы. Разрешены только (), [], {}.");
        }
    }
}

int checkBracketSequence(const CustomCharList& list) {
    CustomStack<BracketInfo> stack;
    for (size_t i = 0; i < list.size(); ++i) {
        char ch = list.getAt(i);
        int currentPos = static_cast<int>(i) + 1;

        if (ch == '(' || ch == '[' || ch == '{') {
            stack.push({ch, currentPos});
        } 
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack.isEmpty()) return currentPos;

            char topBracket = stack.top().bracket;
            if ((ch == ')' && topBracket == '(') ||
                (ch == ']' && topBracket == '[') ||
                (ch == '}' && topBracket == '{')) {
                stack.pop();
            } else {
                return currentPos;
            }
        }
    }
    if (!stack.isEmpty()) return stack.top().position;
    return 0;
}

// 1. Способ ввода: Генерация случайной последовательности
std::string generateRandomBrackets(size_t length) {
    if (length == 0) return "";
    const char types[] = {'(', ')', '[', ']', '{', '}'};
    std::string result = "";
    for (size_t i = 0; i < length; ++i) {
        result += types[std::rand() % 6];
    }
    return result;
}

// 2. Способ ввода: Чтение из файла
std::string readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка: Не удалось открыть файл '" + filename + "'");
    }
    std::string result;
    std::getline(file, result); // Считываем первую строку файла
    file.close();
    return result;
}
