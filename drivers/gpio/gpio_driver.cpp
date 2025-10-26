#include "gpio_driver.h"

void GPIO_Driver_ConfigureOutput(
    _GPIO_Port* port, GPIO_PinPos pin_pos, GPIO_OutputType output_type) {
  const auto pin_pos_u32 = static_cast<uint32_t>(pin_pos);
  // Set output mode for the given pin
  port->MODER |= 0b01 << (2 * pin_pos_u32);
  // Set output type
  switch (output_type) {
    case GPIO_OutputType::PushPull: {
      port->OTYPER &= ~(1 << pin_pos_u32);
    } break;
    case GPIO_OutputType::OpenDrain: {
      port->OTYPER |= 1 << pin_pos_u32;
    } break;
  }
}

void GPIO_Driver_ConfigureInput(
    _GPIO_Port* port, GPIO_PinPos pin_pos, GPIO_InputType input_type) {
  const auto pin_pos_u32 = static_cast<uint32_t>(pin_pos);
  // Set input mode for the given pin
  port->MODER &= ~(1 << (2 * pin_pos_u32));
  // Set input type
  switch (input_type) {
    case GPIO_InputType::Floating: {
      port->PUPDR &= ~(1 << (2 * pin_pos_u32));
    } break;
    case GPIO_InputType::PullUp: {
      port->PUPDR |= 1 << (2 * pin_pos_u32);
    } break;
    case GPIO_InputType::PullDown: {
      port->PUPDR &= ~(0b11 << (2 * pin_pos_u32));
      port->PUPDR |= (0b10 << (2 * pin_pos_u32));
    } break;
  }
}

void GPIO_Driver_ConfigureAlternate(
    _GPIO_Port* port, GPIO_PinPos pin_pos, GPIO_AlternateType alternate_type) {
  const auto alternate_type_u32 = static_cast<uint32_t>(alternate_type);
  const auto pin_pos_u32 = static_cast<uint32_t>(pin_pos);
  // Set alternate mode for the given pin
  port->MODER &= ~(0b11 << (2 * pin_pos_u32));
  port->MODER |= (0b10 << (2 * pin_pos_u32));

  // Set alternate type
  if (pin_pos_u32 <= 7) {
    port->AFRL &= ~(0b1111 << (4 * pin_pos_u32));
    port->AFRL |= alternate_type_u32 << (4 * pin_pos_u32);
  } else {
    port->AFRH &= ~(0b1111 << (4 * pin_pos_u32));
    port->AFRH |= alternate_type_u32 << (4 * pin_pos_u32);
  }
}

void GPIO_Driver_ConfigureAnalog(_GPIO_Port* port, GPIO_PinPos pin_pos) {
  const auto pin_pos_u32 = static_cast<uint32_t>(pin_pos);
  // Set analog mode for the given pin
  port->MODER |= 0b11 << (2 * pin_pos_u32);
}
