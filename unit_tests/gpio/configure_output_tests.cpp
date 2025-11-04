#include <bitset>
#include <gtest/gtest.h>

#include "common.h"
#include "gpio_common.h"
#include "gpio_driver.h"

namespace {
struct GPIO_ConfigureOutput_TestParam {
  GPIO_PinPos pos;
  static inline constexpr auto expected_output_mode = 0b01ul;
  static inline constexpr auto expected_input_mode = 0b00ul;
};

class GPIO_ConfigureOutputTest
    : public ::testing::TestWithParam<GPIO_ConfigureOutput_TestParam> {};

constexpr GPIO_ConfigureOutput_TestParam kTestData[] = {
    {GPIO_PinPos::_0},  {GPIO_PinPos::_1},  {GPIO_PinPos::_2},
    {GPIO_PinPos::_3},  {GPIO_PinPos::_4},  {GPIO_PinPos::_5},
    {GPIO_PinPos::_6},  {GPIO_PinPos::_7},  {GPIO_PinPos::_8},
    {GPIO_PinPos::_9},  {GPIO_PinPos::_10}, {GPIO_PinPos::_11},
    {GPIO_PinPos::_12}, {GPIO_PinPos::_13}, {GPIO_PinPos::_14},
    {GPIO_PinPos::_15}

};

}  // namespace

TEST_P(GPIO_ConfigureOutputTest, GPIO_ConfigureOutputTest_PushPull) {
  const auto param = GetParam();

  _GPIO_Port port{};
  const auto moder_before = port.MODER;
  GPIO_Driver_ConfigureOutput(&port, param.pos, GPIO_OutputType::PushPull);
  const auto moder_after = port.MODER;

  std::bitset<2> mode = GetPinMode(param.pos, port.MODER);
  const std::bitset<2> expected =
      GPIO_ConfigureOutput_TestParam::expected_output_mode;

  // Check that the state is set
  EXPECT_EQ(mode, expected)
      << "<=== mode: " << mode << " expected: " << expected
      << " moder: " << RegisterBitset(port.MODER);

  // Check idempotency
  mode = GetPinMode(param.pos, port.MODER);
  EXPECT_EQ(mode, expected)
      << "<=== mode: " << mode << " expected: " << expected
      << " moder: " << RegisterBitset(port.MODER);

  // Check that other pins are untouched
  for (uint32_t i = 0; i < uint32_t(param.pos); ++i) {
    const auto mode_before =
        GetPinMode(static_cast<GPIO_PinPos>(i), moder_before);
    const auto mode_after =
        GetPinMode(static_cast<GPIO_PinPos>(i), moder_after);
    EXPECT_EQ(mode_before, mode_after)
        << "<==== mode of the pin " << i << " should not have been changed";
  }

  for (uint32_t i = uint32_t(param.pos) + 1; i <= uint32_t(GPIO_PinPos::_15);
       ++i) {
    const auto mode_before =
        GetPinMode(static_cast<GPIO_PinPos>(i), moder_before);
    const auto mode_after =
        GetPinMode(static_cast<GPIO_PinPos>(i), moder_after);
    EXPECT_EQ(mode_before, mode_after)
        << "<==== mode of the pin " << i << " should not have been changed";
  }
}

INSTANTIATE_TEST_SUITE_P(
    GPIO_ConfigureOutputTests, GPIO_ConfigureOutputTest,
    ::testing::ValuesIn(kTestData));
