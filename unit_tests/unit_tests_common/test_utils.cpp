#include "test_utils.h"
#include <bitset>

std::string InsertSeparators(uint32_t reg, uint32_t pos) {
  std::bitset<sizeof(uint32_t) * 8> bitset{reg};

  auto string = bitset.to_string();
  auto result = std::string();
  result.reserve(string.size() + string.size() / pos);

  for (size_t i = 0; i < string.size(); i += pos) {
    result.append(string, i, pos);
    result.push_back('\'');
  }

  if (!result.empty()) {
    result.pop_back();
  }
  return result;
}
