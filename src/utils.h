#pragma once
#include <stdint.h>

#define MEM_ADDRESS(x) reinterpret_cast<volatile uint32_t *const>(x)
