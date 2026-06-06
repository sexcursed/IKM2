#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

class Interface {
private:
  static const std::string RESET;
  static const std::string RED;
  static const std::string GREEN;
  static const std::string MAGENTA;
  static const std::string CYAN;
  static const std::string BOLD;

  void clearScreen() const;
  void waitForEnter() const;
  void processSequence(const std::string& inputStr) const;
  bool runInputSubmenu(std::string& outStrForAnalysis);

public:
  void run();
};

#endif
