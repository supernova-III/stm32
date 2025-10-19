#include "gpio.h"

static constexpr uint32_t GPIOA_BASE_ADDR = 0x4002'0000ul;
static constexpr uint32_t GPIOB_BASE_ADDR = 0x4002'0400ul;

_GPIO& GPIOA = *reinterpret_cast<_GPIO*>(GPIOA_BASE_ADDR);
_GPIO& GPIOB = *reinterpret_cast<_GPIO*>(GPIOB_BASE_ADDR);
