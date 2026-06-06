#include "Interface.h"
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include "CustomStructures.h"
#include "BracketChecker.h"
#include "BracketException.h"

namespace fs = std::filesystem;

const std::string Interface::RESET   = "\033[0m";
const std::string Interface::RED     = "\033[31m";
const std::string Interface::GREEN   = "\033[32m";
const std::string Interface::MAGENTA  = "\033[35m";
const std::string Interface::CYAN    = "\033[36m";
const std::string Interface::BOLD    = "\033[1m";

void Interface::clearScreen() const {
#if defined(_WIN32) || defined(_WIN64)
  std::system("cls");
#else
  std::system("clear");
#endif
}

void Interface::waitForEnter() const {
    std::cout << "\nНажмите Enter, чтобы продолжить...";
    std::cin.get();
}

void Interface::processSequence(const std::string& inputStr) const {
  validateInput(inputStr);

  CustomCharList charList;
  for (char c : inputStr) {
    charList.append(c);
  }

  int result = checkBracketSequence(charList);
  
  if (result == 0) {
    std::cout << "\nАнализируемая строка: " << GREEN << inputStr << RESET << "\n";
    std::cout << GREEN << BOLD << ">>> РЕЗУЛЬТАТ: Корректная скобочная последовательность!\n" << RESET;
  } else {
    std::cout << "\nАнализируемая строка: ";
    size_t errIndex = static_cast<size_t>(result - 1);
    
    if (errIndex < inputStr.length()) {
      std::cout << CYAN << inputStr.substr(0, errIndex) << RESET;
      std::cout << RED << BOLD << "->" << inputStr[errIndex] << "<-" << RESET;
      std::cout << CYAN << inputStr.substr(errIndex + 1) << RESET << "\n";
    } else {
      std::cout << CYAN << inputStr << RESET << RED << BOLD << " [ожидался закрывающий символ]" << RESET << "\n";
    }
    
    std::cout << RED << BOLD << ">>> РЕЗУЛЬТАТ: Нарушение на позиции: " << result << "\n" << RESET;
  }
}

bool Interface::runInputSubmenu(std::string& outStrForAnalysis) {
    int inputChoice = 0;
    bool inputSuccess = false;

    do {
      std::cout << CYAN << "\n--- Выберите способ ввода данных ---\n" << RESET;
      std::cout << "1) Ручной ввод строки\n";
      std::cout << "2) Генерация случайной строки (рандом)\n";
      std::cout << "3) Чтение из файла\n";
      std::cout << "4) Вернуться в главное меню\n";
      std::cout << "Ваш выбор: ";
      
      if (!(std::cin >> inputChoice)) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        clearScreen();
        std::cout << RED << BOLD << "[ОШИБКА]: Неверный ввод. Введите число от 1 до 4.\n" << RESET;
        continue;
      }
      std::cin.ignore(10000, '\n');

      if (inputChoice == 4) {
        clearScreen();
        return false; 
      }

      try {
        if (inputChoice == 1) {
          std::cout << "Введите строку: ";
          std::getline(std::cin, outStrForAnalysis);
          inputSuccess = true;
        } 
        else if (inputChoice == 2) {
          size_t len;
          std::cout << "Введите желаемую длину строки: ";
          if (!(std::cin >> len)) {
            std::cin.clear(); std::cin.ignore(10000, '\n');
            throw BracketException(ErrorType::InvalidLength, "Некорректная длина строки. Введите число.");
          }
          std::cin.ignore(10000, '\n');
          outStrForAnalysis = generateRandomBrackets(len);
          inputSuccess = true;
        } 
        else if (inputChoice == 3) {
          std::string filename;
          std::cout << "Введите имя файла (например, test.txt): ";
          std::getline(std::cin, filename);

          if (!fs::exists(filename)) {
            throw BracketException(ErrorType::FileNotFound, "Файл '" + filename + "' не существует или путь указан неверно.");
          }
          if (fs::is_directory(filename)) {
            throw BracketException(ErrorType::NotAFile, "Указанный путь является папкой, а не файлом.");
          }

          outStrForAnalysis = readFromFile(filename);
          inputSuccess = true;
        } 
        else {
          clearScreen();
          std::cout << RED << BOLD << "[ОШИБКА]: Неверный пункт подменю. Выберите от 1 до 4.\n" << RESET;
        }
      }
      catch (const std::exception& e) {
        clearScreen();
        std::cerr << RED << BOLD << "[ОШИБКА ВВОДА]: " << e.what() << "\n" << RESET;
      }

    } while (!inputSuccess && inputChoice != 4);

    return inputSuccess;
}

void Interface::run() {
  int mainChoice = 0;
  clearScreen();

  while (true) {
    std::cout << MAGENTA << "=========================================\n" << RESET;
    std::cout << MAGENTA << BOLD << "                   МЕНЮ\n" << RESET;
    std::cout << MAGENTA << "=========================================\n" << RESET;
    std::cout << "1. Проверить скобочную последовательность\n";
    std::cout << "2. Выйти\n";
    std::cout << "Выберите пункт: ";
    
    if (!(std::cin >> mainChoice)) {
      std::cin.clear(); std::cin.ignore(10000, '\n'); 
      clearScreen();
      std::cout << RED << BOLD << "[ОШИБКА]: Неверный ввод. Выберите 1 или 2.\n\n" << RESET;
      continue;
    }

    if (mainChoice == 2) break;
    if (mainChoice != 1) {
      clearScreen();
      std::cout << RED << BOLD << "[ОШИБКА]: Такого пункта меню нет.\n\n" << RESET;
      continue;
    }

    std::string strForAnalysis = "";
    if (runInputSubmenu(strForAnalysis)) {
      clearScreen(); 
      try {
        processSequence(strForAnalysis);
        waitForEnter();
        clearScreen();
      }
      catch (const std::exception& e) {
        clearScreen();
        std::cerr << RED << BOLD << "[ОШИБКА АНАЛИЗА]: " << e.what() << "\n" << RESET;
        waitForEnter();
        clearScreen();
      }
    }
  }
}
