#include "common.h"

std::bitset<2> GetPinMode(GPIO_PinPos pin, RegisterBitset moder) {
  constexpr auto register_bits = sizeof(Register) * 8;
  const auto moder_bit_pos = 2 * uint32_t(pin);

  const auto mode_bit_0 = moder[moder_bit_pos];
  const auto mode_bit_1 = moder[moder_bit_pos + 1] << 1;
  return mode_bit_1 | mode_bit_0;
}