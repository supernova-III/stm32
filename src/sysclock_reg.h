#pragma once
#include <stdint.h>

#define MEM_ADDRESS(x) reinterpret_cast<volatile uint32_t* const>(x)

inline auto STK_CTRL = MEM_ADDRESS(0xE000'E010ul);
inline auto STK_LOAD = MEM_ADDRESS(0xE000'E014ul);
inline auto STK_VAL = MEM_ADDRESS(0xE000'E018ul);
