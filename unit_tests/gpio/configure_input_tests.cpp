#include <bitset>
#include <format>
#include <gtest/gtest.h>

#include "gpio_driver.h"

struct TestData {
  GPIO_PinPos pin;
  Register moder;
  Register floating;
  Register pull_up;
  Register pull_down;
};

TEST(GPIO, ConfigureInputSingle) {
  // clang-format off
  const TestData test_data[] = {
    {
      .pin = GPIO_PinPos::_0,
      .moder =      0b11'11'11'11'11'11'11'11'11'11'11'11'11'11'11'00,
      .floating =   0b11'11'11'11'11'11'11'11'11'11'11'11'11'11'11'00,
      .pull_up =    0b11'11'11'11'11'11'11'11'11'11'11'11'11'11'11'01,
      .pull_down =  0b11'11'11'11'11'11'11'11'11'11'11'11'11'11'11'10,
    },
    {
      .pin = GPIO_PinPos::_1,
      .moder =      0b11'11'11'11'11'11'11'11'11'11'11'11'11'11'00'11,
      .floating =   0b11'11'11'11'11'11'11'11'11'11'11'11'11'11'00'11,
      .pull_up =    0b11'11'11'11'11'11'11'11'11'11'11'11'11'11'01'11,
      .pull_down =  0b11'11'11'11'11'11'11'11'11'11'11'11'11'11'10'11,
    },
    {
      .pin = GPIO_PinPos::_2,
      .moder =      0b11'11'11'11'11'11'11'11'11'11'11'11'11'00'11'11,
      .floating =   0b11'11'11'11'11'11'11'11'11'11'11'11'11'00'11'11,
      .pull_up =    0b11'11'11'11'11'11'11'11'11'11'11'11'11'01'11'11,
      .pull_down =  0b11'11'11'11'11'11'11'11'11'11'11'11'11'10'11'11,
    },
    {
      .pin = GPIO_PinPos::_3,
      .moder =      0b11'11'11'11'11'11'11'11'11'11'11'11'00'11'11'11,
      .floating =   0b11'11'11'11'11'11'11'11'11'11'11'11'00'11'11'11,
      .pull_up =    0b11'11'11'11'11'11'11'11'11'11'11'11'01'11'11'11,
      .pull_down =  0b11'11'11'11'11'11'11'11'11'11'11'11'10'11'11'11,
    }
  };
  // clang-format on
  _GPIO_Port port{};

  for (const auto& sample : test_data) {
    port.MODER = 0xFF'FF'FF'FF;
    port.PUPDR = 0xFF'FF'FF'FF;
    GPIO_Driver_ConfigureInput(&port, sample.pin, GPIO_InputType::Floating);
    EXPECT_EQ(port.MODER, sample.moder);
    EXPECT_EQ(port.PUPDR, sample.floating);

    port.MODER = 0xFF'FF'FF'FF;
    port.PUPDR = 0xFF'FF'FF'FF;
    GPIO_Driver_ConfigureInput(&port, sample.pin, GPIO_InputType::PullUp);
    EXPECT_EQ(port.MODER, sample.moder);
    EXPECT_EQ(port.PUPDR, sample.pull_up);

    port.MODER = 0xFF'FF'FF'FF;
    port.PUPDR = 0xFF'FF'FF'FF;
    GPIO_Driver_ConfigureInput(&port, sample.pin, GPIO_InputType::PullDown);
    EXPECT_EQ(port.MODER, sample.moder);
    EXPECT_EQ(port.PUPDR, sample.pull_down);
  }
}
