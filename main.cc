#include "cache.h"

#include <iostream>

int main() {
  Cache<int, int> c(10);

  for (int i = 0; i < 100; ++i) {
    c.Put(i, i);
  }

  for (int i = 0; i < 100; ++i) {
    int v;
    if (c.Get(i, &v)) {
      std::cout << i << ": " << v << "\n";
    } else {
      std::cout << i << ": dropped\n";
    }
  }

  return 0;
}
