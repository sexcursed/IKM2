#ifndef BRACKET_EXCEPTION_H
#define BRACKET_EXCEPTION_H

#include <stdexcept>
#include <string>

enum class ErrorType {
    InvalidInput,   // Некорректные символы во вводе
    InvalidLength,  // Неверная длина для генератора
    FileNotFound,   // Файл не найден
    NotAFile,       // Указан путь к папке вместо файла
    MenuError,      // Ошибка выбора пункта меню
    StackUnderflow, // Ошибка пустого стека
    ListOutOfRange  // Выход за границы списка
};

class BracketException : public std::runtime_error {
private:
    ErrorType type;

public:
    BracketException(ErrorType errorType, const std::string& message)
        : std::runtime_error(message), type(errorType) {}

    ErrorType getType() const { return type; }
};

#endif
