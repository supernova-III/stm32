#include <bitset>
#include <format>
#include <gtest/gtest.h>

#include "gpio_driver.h"

struct TestData {
  GPIO_PinPos pos;
  GPIO_OutputType otype;
  Register expected_moder;
  Register expected_otyper;
};

namespace {

std::string InsertSeparators(uint32_t reg, uint32_t pos = 2) {
  std::bitset<sizeof(uint32_t) * 8> bitset{reg};

  auto string = bitset.to_string();
  auto result = std::string();
  result.reserve(string.size() + string.size() / pos);

  for (size_t i = 0; i < string.size(); i += pos) {
    result.append(string, i, pos);
    result.push_back('\'');
  }

  if (!result.empty()) {
    result.pop_back();
  }
  return result;
}

std::string TestDebugString(const _GPIO_Port& port, const TestData& test_data) {
  auto moder = InsertSeparators(port.MODER);
  auto otyper = InsertSeparators(port.OTYPER, 4);
  auto expected_moder = InsertSeparators(test_data.expected_moder);
  auto expected_otyper = InsertSeparators(test_data.expected_otyper, 4);
  auto res = std::format(
      "<==== pos = {}, otype = {}\n", uint32_t(test_data.pos),
      uint32_t(test_data.otype));
  res += std::format(
      "<==== expected moder = {}, expected otyper = {}\n", expected_moder,
      expected_otyper);
  res += std::format(
      "<==== actual   moder = {}, actual   otyper = {}", moder, otyper);
  return res;
}
}  // namespace

TEST(GPIO, ConfigureOutputSingle) {
  // clang-format off
  const TestData test_data[] = {
      {.pos=GPIO_PinPos::_0,  .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01,                                              .expected_otyper=0},
      {.pos=GPIO_PinPos::_1,  .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00,                                           .expected_otyper=0},
      {.pos=GPIO_PinPos::_2,  .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00,                                        .expected_otyper=0},
      {.pos=GPIO_PinPos::_3,  .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00,                                     .expected_otyper=0},
      {.pos=GPIO_PinPos::_4,  .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00,                                  .expected_otyper=0},
      {.pos=GPIO_PinPos::_5,  .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00,                               .expected_otyper=0},
      {.pos=GPIO_PinPos::_6,  .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00'00,                            .expected_otyper=0},
      {.pos=GPIO_PinPos::_7,  .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00'00'00,                         .expected_otyper=0},
      {.pos=GPIO_PinPos::_8,  .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00'00'00'00,                      .expected_otyper=0},
      {.pos=GPIO_PinPos::_9,  .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00'00'00'00'00,                   .expected_otyper=0},
      {.pos=GPIO_PinPos::_10, .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00,                .expected_otyper=0},
      {.pos=GPIO_PinPos::_11, .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00'00,             .expected_otyper=0},
      {.pos=GPIO_PinPos::_12, .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00'00'00,          .expected_otyper=0},
      {.pos=GPIO_PinPos::_13, .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00'00'00'00,       .expected_otyper=0},
      {.pos=GPIO_PinPos::_14, .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00'00'00'00'00,    .expected_otyper=0},
      {.pos=GPIO_PinPos::_15, .otype=GPIO_OutputType::PushPull,  .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00'00'00'00'00'00, .expected_otyper=0},

      {.pos=GPIO_PinPos::_0,  .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01,                                              .expected_otyper=0b1},
      {.pos=GPIO_PinPos::_1,  .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00,                                           .expected_otyper=0b10},
      {.pos=GPIO_PinPos::_2,  .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00,                                        .expected_otyper=0b100},
      {.pos=GPIO_PinPos::_3,  .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00,                                     .expected_otyper=0b1000},
      {.pos=GPIO_PinPos::_4,  .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00,                                  .expected_otyper=0b1000'0},
      {.pos=GPIO_PinPos::_5,  .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00,                               .expected_otyper=0b1000'00},
      {.pos=GPIO_PinPos::_6,  .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00'00,                            .expected_otyper=0b1000'000},
      {.pos=GPIO_PinPos::_7,  .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00'00'00,                         .expected_otyper=0b1000'0000},
      {.pos=GPIO_PinPos::_8,  .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00'00'00'00,                      .expected_otyper=0b1000'0000'0},
      {.pos=GPIO_PinPos::_9,  .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00'00'00'00'00,                   .expected_otyper=0b1000'0000'00},
      {.pos=GPIO_PinPos::_10, .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00,                .expected_otyper=0b1000'0000'000},
      {.pos=GPIO_PinPos::_11, .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00'00,             .expected_otyper=0b1000'0000'0000},
      {.pos=GPIO_PinPos::_12, .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00'00'00,          .expected_otyper=0b1000'0000'0000'0},
      {.pos=GPIO_PinPos::_13, .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00'00'00'00,       .expected_otyper=0b1000'0000'0000'00},
      {.pos=GPIO_PinPos::_14, .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00'00'00'00'00,    .expected_otyper=0b1000'0000'0000'000},
      {.pos=GPIO_PinPos::_15, .otype=GPIO_OutputType::OpenDrain, .expected_moder=0b01'00'00'00'00'00'00'00'00'00'00'00'00'00'00'00, .expected_otyper=0b1000'0000'0000'0000}

  };
  // clang-format on

  for (const auto& test_sample : test_data) {
    _GPIO_Port port{};
    GPIO_Driver_ConfigureOutput(&port, test_sample.pos, test_sample.otype);
    EXPECT_EQ(port.MODER, test_sample.expected_moder)
        << TestDebugString(port, test_sample);
    EXPECT_EQ(port.OTYPER, test_sample.expected_otyper)
        << TestDebugString(port, test_sample);
  }
}

TEST(GPIO, ConfigureOutputAllPins) {
  constexpr GPIO_PinPos positions[] = {
      GPIO_PinPos::_0,  GPIO_PinPos::_1,  GPIO_PinPos::_2,  GPIO_PinPos::_3,
      GPIO_PinPos::_4,  GPIO_PinPos::_5,  GPIO_PinPos::_6,  GPIO_PinPos::_7,
      GPIO_PinPos::_8,  GPIO_PinPos::_9,  GPIO_PinPos::_10, GPIO_PinPos::_11,
      GPIO_PinPos::_12, GPIO_PinPos::_13, GPIO_PinPos::_14, GPIO_PinPos::_15,
  };

  _GPIO_Port port{};
  for (const auto pin_pos : positions) {
    GPIO_Driver_ConfigureOutput(&port, pin_pos, GPIO_OutputType::PushPull);
  }

  EXPECT_EQ(port.MODER, 0b01'01'01'01'01'01'01'01'01'01'01'01'01'01'01'01ul);
  EXPECT_EQ(port.OTYPER & 0xF, 0);

  port = {};
  for (const auto pin_pos : positions) {
    GPIO_Driver_ConfigureOutput(&port, pin_pos, GPIO_OutputType::OpenDrain);
  }

  EXPECT_EQ(port.MODER, 0b01'01'01'01'01'01'01'01'01'01'01'01'01'01'01'01ul);
  EXPECT_EQ(port.OTYPER & 0xF, 0xF);
}
