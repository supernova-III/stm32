#include <bitset>
#include <ranges>
#include <random>
#include <gtest/gtest.h>

#include "common.h"
#include "gpio_common.h"
#include "gpio_driver.h"

namespace {

struct GPIO_ConfigureOutput_TestParam {
  GPIO_PinPos pos;
  static inline constexpr uint32_t expected_output_mode = 0b01;
  static inline constexpr uint32_t expected_otype_push_pull = 0b0;
  static inline constexpr uint32_t expected_otype_open_drain = 0b1;
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

auto GetPinsExcluding(GPIO_PinPos pos) {
  return std::views::iota(
             uint32_t(GPIO_PinPos::_0), uint32_t(GPIO_PinPos::_15)) |
         std::views::filter([pos](uint32_t x) { return x != uint32_t(pos); }) |
         std::views::transform([](uint32_t x) { return GPIO_PinPos(x); });
}

uint32_t GenerateRandomRegister() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);
  return dist(gen);
}

uint32_t GetOutputType(GPIO_PinPos pin, RegisterBitset otyper) {
  return otyper[uint32_t(pin)];
}

struct OutputTypeTestCase {
  GPIO_OutputType output_type;
  uint32_t expected_otype_bit;
};

}  // namespace

TEST_P(GPIO_ConfigureOutputTest, GPIO_ConfigureOutputTest_PushPull) {
  constexpr OutputTypeTestCase output_types[]{
      {GPIO_OutputType::PushPull, 0b0}, {GPIO_OutputType::OpenDrain, 0b1}};

  const auto param = GetParam();

  for (const auto& output_type : output_types) {
    _GPIO_Port port{};
    port.MODER = GenerateRandomRegister();
    port.OTYPER = GenerateRandomRegister();

    const auto moder_before = port.MODER;
    const auto otyper_before = port.OTYPER;
    GPIO_Driver_ConfigureOutput(&port, param.pos, output_type.output_type);
    const auto moder_after = port.MODER;
    const auto otyper_after = port.OTYPER;

    std::bitset<2> mode = GetPinMode(param.pos, port.MODER);
    constexpr std::bitset<2> expected =
        GPIO_ConfigureOutput_TestParam::expected_output_mode;

    const auto otype = GetOutputType(param.pos, port.OTYPER);

    // Check that the state is set
    EXPECT_EQ(mode, expected) << "<=== " << "pin: " << uint32_t(param.pos)
                              << " mode: " << mode << " expected: " << expected
                              << " moder: " << RegisterBitset(port.MODER);
    EXPECT_EQ(otype, output_type.expected_otype_bit);

    // Check idempotency
    GPIO_Driver_ConfigureOutput(&port, param.pos, GPIO_OutputType::PushPull);
    mode = GetPinMode(param.pos, port.MODER);
    EXPECT_EQ(mode, expected) << "<=== " << "pin: " << uint32_t(param.pos)
                              << " mode: " << mode << " expected: " << expected
                              << " moder: " << RegisterBitset(port.MODER);

    EXPECT_EQ(otype, output_type.expected_otype_bit);

    auto range = GetPinsExcluding(param.pos);
    // Check that other pins are untouched
    for (const auto pos : range) {
      const auto mode_before =
          GetPinMode(static_cast<GPIO_PinPos>(pos), moder_before);
      const auto mode_after =
          GetPinMode(static_cast<GPIO_PinPos>(pos), moder_after);
      const auto otype_before = GetOutputType(pos, otyper_before);
      const auto otype_after = GetOutputType(pos, otyper_after);
      EXPECT_EQ(mode_before, mode_after)
          << "<==== mode of the pin " << uint32_t(pos)
          << " should not have been changed";
      EXPECT_EQ(otype_before, otype_after);
    }
  }
}

INSTANTIATE_TEST_SUITE_P(
    GPIO_ConfigureOutputTests, GPIO_ConfigureOutputTest,
    ::testing::ValuesIn(kTestData));
