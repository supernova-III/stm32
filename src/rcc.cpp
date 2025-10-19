#include "rcc.h"

static constexpr uint32_t RCC_BASE_ADDR = 0x4002'3800ul;
_RCC& RCC = *reinterpret_cast<_RCC*>(RCC_BASE_ADDR);
