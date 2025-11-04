#pragma once
#include <bitset>

#include "utils.h"
#include "gpio_common.h"

constexpr auto kRegisterBits = sizeof(Register) * 8;
using RegisterBitset = std::bitset<kRegisterBits>;

std::bitset<2> GetPinMode(GPIO_PinPos pin, RegisterBitset moder);
