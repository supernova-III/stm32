#include "gpio_driver.h"

void GPIO_Driver_ConfigureOutput(
    _GPIO_Port* port, GPIO_PinPos pin, GPIO_OutputType output_type) {
  const auto pin_pos = static_cast<uint32_t>(pin);
  // Reset current mode
  port->MODER &= ~(0b11 << (2 * pin_pos));
  // Set output mode for the given pin
  port->MODER |= 0b01 << (2 * pin_pos);
  // Set output type
  switch (output_type) {
    case GPIO_OutputType::PushPull: {
      port->OTYPER &= ~(1 << pin_pos);
    } break;
    case GPIO_OutputType::OpenDrain: {
      port->OTYPER |= 1 << pin_pos;
    } break;
  }
}

void GPIO_Driver_ConfigureInput(
    _GPIO_Port* port, GPIO_PinPos pin, GPIO_InputType input_type) {
  const auto pin_pos = static_cast<uint32_t>(pin);
  // Set input mode for the given pin
  port->MODER &= ~(0b11 << (2 * pin_pos));
  // Set input type
  // Reset it first
  port->PUPDR &= ~(0b11 << (2 * pin_pos));
  switch (input_type) {
    case GPIO_InputType::Floating: {
    } break;
    case GPIO_InputType::PullUp: {
      port->PUPDR |= 0b01 << (2 * pin_pos);
    } break;
    case GPIO_InputType::PullDown: {
      port->PUPDR |= (0b10 << (2 * pin_pos));
    } break;
  }
}

void GPIO_Driver_ConfigureAlternate(
    _GPIO_Port* port, GPIO_PinPos pin, GPIO_AlternateType alternate_type) {
  const auto alternate_type_u32 = static_cast<uint32_t>(alternate_type);
  const auto pin_pos = static_cast<uint32_t>(pin);
  // Set alternate mode for the given pin
  port->MODER &= ~(0b11 << (2 * pin_pos));
  port->MODER |= (0b10 << (2 * pin_pos));

  // Set alternate type
  if (pin_pos <= 7) {
    port->AFRL &= ~(0b1111 << (4 * pin_pos));
    port->AFRL |= alternate_type_u32 << (4 * pin_pos);
  } else {
    port->AFRH &= ~(0b1111 << (4 * pin_pos));
    port->AFRH |= alternate_type_u32 << (4 * pin_pos);
  }
}

void GPIO_Driver_ConfigureAnalog(_GPIO_Port* port, GPIO_PinPos pin) {
  const auto pin_pos = static_cast<uint32_t>(pin);
  // Set analog mode for the given pin
  port->MODER |= 0b11 << (2 * pin_pos);
}

uint32_t GPIO_Driver_OutputRead(_GPIO_Port* port, GPIO_PinPos pin) {
  const auto pin_pos = static_cast<uint32_t>(pin);
  const uint32_t result = (port->ODR >> pin_pos) & 1ul;
  return result;
}

void GPIO_Driver_OutputWrite(
    _GPIO_Port* port, GPIO_PinPos pin, uint32_t value) {
  const auto pin_pos = static_cast<uint32_t>(pin);
  const auto mask = 1ul << pin_pos;
  if (value) {
    port->ODR |= mask;
  } else {
    port->ODR &= ~mask;
  }
}

void GPIO_Driver_OutputWriteAtomic(
    _GPIO_Port* port, GPIO_PinPos pin, uint32_t value) {
  const auto pin_pos = static_cast<uint32_t>(pin);
  const auto mask = 1ul << pin_pos;
  if (value) {
    port->BSRR |= mask;
  } else {
    port->BSRR &= ~mask;
  }
}

uint32_t GPIO_Driver_InputRead(_GPIO_Port* port, GPIO_PinPos pin) {
  const auto pin_pos = static_cast<uint32_t>(pin);
  const uint32_t result = (port->IDR >> pin_pos) & 1ul;
  return result;
}
