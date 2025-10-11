#include <stdint.h>

int main() {
  auto* ptr = reinterpret_cast<uint32_t*>(0x123);
  return 0;
}
