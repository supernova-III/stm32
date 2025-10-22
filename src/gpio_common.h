#pragma once
#include <stdint.h>

enum struct GPIO_OutputType : uint32_t {
  PushPull = 0,
  OpenDrain = 1
};

enum struct GPIO_InputType : uint32_t {
  Floating,
  PullUp = 0b01,
  PullDown = 0b10
};

enum struct GPIO_AlternateType : uint32_t {
  AF0,
  AF1,
  AF2,
  AF3,
  AF4,
  AF5,
  AF6,
  AF7,
  AF8,
  AF9,
  AF10,
  AF11,
  AF12,
  AF13,
  AF14,
  AF15
};

enum struct GPIO_PinPos : uint32_t {
  _0,
  _1,
  _2,
  _3,
  _4,
  _5,
  _6,
  _7,
  _8,
  _9,
  _10,
  _11,
  _12,
  _13,
  _14,
  _15,
};
