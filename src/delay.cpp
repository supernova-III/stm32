#include "sysclock_reg.h"
#include "delay.h"

// WARNING: 16MHz clock rate assumed!
void ShortDelay(uint16_t ms) {
  // Disabling exceptions
  *STK_CTRL &= ~(1ul << 1);
  *STK_CTRL |= (1ul << 2);

  const uint8_t reload = (ms / 16000) - 1;
  constexpr uint32_t kZeroMask = 0xFF'00'00'00;

  // Loading reload value
  *STK_LOAD = (*STK_LOAD & kZeroMask) | reload;

  // Clearing current value
  *STK_VAL &= kZeroMask;

  // Firing countdown
  *STK_CTRL |= 1ul;

  // Busy wait
  while (*STK_CTRL & (1ul << 16) != 1);

  // Disabling counting
  *STK_CTRL &= ~1ul;
}
