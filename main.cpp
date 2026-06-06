#include <ctime>
#include <cstdlib>
#include "Interface.h"

int main() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  
  Interface app;
  app.run();
  
  return 0;
}
