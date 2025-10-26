#pragma once
#include "utils.h"
#include "gpio_common.h"

struct _GPIO_Port {
  volatile Register MODER;
  volatile Register OTYPER;
  volatile Register OSPEEDR;
  volatile Register PUPDR;
  volatile Register IDR;
  volatile Register ODR;
  volatile Register BSRR;
  volatile Register LCKR;
  volatile Register AFRL;
  volatile Register AFRH;
};

void GPIO_Driver_ConfigureOutput(
    _GPIO_Port* port, GPIO_PinPos pin, GPIO_OutputType output_type);

void GPIO_Driver_ConfigureInput(
    _GPIO_Port* port, GPIO_PinPos pin, GPIO_InputType input_type);

void GPIO_Driver_ConfigureAlternate(
    _GPIO_Port* port, GPIO_PinPos pin, GPIO_AlternateType alternate);

void GPIO_Driver_ConfigureAnalog(_GPIO_Port* port, GPIO_PinPos pin);
