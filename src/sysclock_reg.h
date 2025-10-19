#pragma once
#include <stdint.h>

#include "utils.h"

inline auto STK_CTRL = MEM_ADDRESS(0xE000'E010ul);
inline auto STK_LOAD = MEM_ADDRESS(0xE000'E014ul);
inline auto STK_VAL = MEM_ADDRESS(0xE000'E018ul);
