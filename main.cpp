#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "CustomStructures.h"
#include "BracketChecker.h"

void processSequence(const std::string& inputStr) {
  std::cout << "\nАнализируемая строка: " << inputStr << "\n";
  validateInput(inputStr);

  CustomCharList charList;
  for (char c : inputStr) {
    charList.append(c);
  }

  int result = checkBracketSequence(charList);
  if (result == 0) {
    std::cout << ">>> РЕЗУЛЬТАТ: Корректная скобочная последовательность!\n";
  } else {
    std::cout << ">>> РЕЗУЛЬТАТ: Нарушение на позиции: " << result << "\n";
  }
}

int main() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  int mainChoice = 0;

  while (true) {
    std::cout << "\n=========================================\n";
    std::cout << "      МЕНЮ УПРАВЛЕНИЯ ПРОЕКТОМ\n";
    std::cout << "=========================================\n";
    std::cout << "1. Проверить скобочную последовательность\n";
    std::cout << "2. Выйти\n";
    std::cout << "Выберите пункт: ";
    
    if (!(std::cin >> mainChoice)) {
      std::cin.clear(); std::cin.ignore(10000, '\n'); continue;
    }

    if (mainChoice == 2) break;
    if (mainChoice != 1) continue;

    // Подменю способов ввода
    std::cout << "\n--- Выберите способ ввода данных ---\n";
    std::cout << "1) Ручной ввод строки\n";
    std::cout << "2) Генерация случайной строки (рандом)\n";
    std::cout << "3) Чтение из файла\n";
    std::cout << "Ваш выбор: ";
    
    int inputChoice = 0;
    std::cin >> inputChoice;
    std::cin.ignore(10000, '\n');

    try {
      std::string strForAnalysis = "";

      if (inputChoice == 1) {
        std::cout << "Введите строку: ";
        std::getline(std::cin, strForAnalysis);
      } 
      else if (inputChoice == 2) {
        size_t len;
        std::cout << "Введите желаемую длину строки: ";
        std::cin >> len;
        strForAnalysis = generateRandomBrackets(len);
      } 
      else if (inputChoice == 3) {
        std::string filename;
        std::cout << "Введите имя файла (например, test.txt): ";
        std::getline(std::cin, filename);
        strForAnalysis = readFromFile(filename);
      } 
      else {
        std::cout << "Неверный способ ввода.\n";
        continue;
      }

      processSequence(strForAnalysis);
    }
    catch (const std::exception& e) {
      std::cerr << "\n[ОШИБКА]: " << e.what() << "\n";
    }
  }
  return 0;
}
