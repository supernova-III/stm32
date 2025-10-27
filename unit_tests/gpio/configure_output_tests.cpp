#include <gtest/gtest.h>

#include "gpio_driver.h"

struct TestDataOutput {
  GPIO_PinPos pos;
  GPIO_OutputType otype;
  Register expected_moder;
  Register expected_otyper;
};

TEST(GPIO, ConfigureOutputSingle) {
  // clang-format off
  const TestDataOutput test_data[] = {
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
        << "<----------- pos = " << uint32_t(test_sample.pos);
    EXPECT_EQ(port.OTYPER, test_sample.expected_otyper)
        << "<----------- otype = " << uint32_t(test_sample.otype);
  }
}
