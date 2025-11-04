#pragma once
#include "utils.h"
#include "gpio_common.h"

struct _GPIO_Port {
  Register MODER;
  Register OTYPER;
  Register OSPEEDR;
  Register PUPDR;
  Register IDR;
  Register ODR;
  Register BSRR;
  Register LCKR;
  Register AFRL;
  Register AFRH;
};

void GPIO_Driver_ConfigureOutput(
    _GPIO_Port* port, GPIO_PinPos pin, GPIO_OutputType output_type);

void GPIO_Driver_ConfigureInput(
    _GPIO_Port* port, GPIO_PinPos pin, GPIO_InputType input_type);

void GPIO_Driver_ConfigureAlternate(
    _GPIO_Port* port, GPIO_PinPos pin, GPIO_AlternateType alternate);

void GPIO_Driver_ConfigureAnalog(_GPIO_Port* port, GPIO_PinPos pin);

uint32_t GPIO_Driver_OutputRead(_GPIO_Port* port, GPIO_PinPos pin);
void GPIO_Driver_OutputWrite(_GPIO_Port* port, GPIO_PinPos pin, uint32_t value);
void GPIO_Driver_OutputWriteAtomic(
    _GPIO_Port* port, GPIO_PinPos pin, uint32_t value);

uint32_t GPIO_Driver_InputRead(_GPIO_Port* port, GPIO_PinPos pin);
