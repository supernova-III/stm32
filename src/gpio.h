#pragma once
#include "gpio_common.h"

void GPIO_Enable();
void GPIO_Disable();

void GPIO_ConfigureInputA(GPIO_PinPos pin, GPIO_InputType input_type);
void GPIO_ConfigureInputB(GPIO_PinPos pin, GPIO_InputType input_type);
void GPIO_ConfigureOutputA(GPIO_PinPos pin, GPIO_OutputType output_type);
void GPIO_ConfigureOutputB(GPIO_PinPos pin, GPIO_OutputType output_type);
void GPIO_ConfigureAlternateA(GPIO_PinPos pin, GPIO_AlternateType alternate);
void GPIO_ConfigureAlternateB(GPIO_PinPos pin, GPIO_AlternateType alternate);
void GPIO_ConfigureAnalogA(GPIO_PinPos pin);
void GPIO_ConfigureAnalogB(GPIO_PinPos pin);
