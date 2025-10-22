#include "gpio_driver.h"
#include "rcc.h"

#include "gpio.h"

static constexpr uint32_t GPIOA_BASE_ADDR = 0x4002'0000ul;
static constexpr uint32_t GPIOB_BASE_ADDR = 0x4002'0400ul;

static _GPIO_Port* GPIO_PortA = (_GPIO_Port*)GPIOA_BASE_ADDR;
static _GPIO_Port* GPIO_PortB = (_GPIO_Port*)GPIOB_BASE_ADDR;

void GPIO_Enable() {
  RCC.AHB1ENR |= 0x3ul;
}

void GPIO_Disable() {
  RCC.AHB1ENR &= ~0x3ul;
}

void GPIO_ConfigureOutputA(GPIO_PinPos pin, GPIO_OutputType output_type) {
  GPIO_Driver_ConfigureOutput(GPIO_PortA, pin, output_type);
}

void GPIO_ConfigureOutputB(GPIO_PinPos pin, GPIO_OutputType output_type) {
  GPIO_Driver_ConfigureOutput(GPIO_PortB, pin, output_type);
}

void GPIO_ConfigureInputA(GPIO_PinPos pin, GPIO_InputType input_type) {
  GPIO_Driver_ConfigureInput(GPIO_PortA, pin, input_type);
}

void GPIO_ConfigureInputB(GPIO_PinPos pin, GPIO_InputType input_type) {
  GPIO_Driver_ConfigureInput(GPIO_PortB, pin, input_type);
}

void GPIO_ConfigureAlternateA(GPIO_PinPos pin, GPIO_AlternateType alternate) {
  GPIO_Driver_ConfigureAlternate(GPIO_PortA, pin, alternate);
}

void GPIO_ConfigureAlternateB(GPIO_PinPos pin, GPIO_AlternateType alternate) {
  GPIO_Driver_ConfigureAlternate(GPIO_PortB, pin, alternate);
}

void GPIO_ConfigureAnalogA(GPIO_PinPos pin) {
  GPIO_Driver_ConfigureAnalog(GPIO_PortA, pin);
}

void GPIO_ConfigureAnalogB(GPIO_PinPos pin) {
  GPIO_Driver_ConfigureAnalog(GPIO_PortB, pin);
}
