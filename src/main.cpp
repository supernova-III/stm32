#include "gpio.h"

int main() {
  GPIO_Enable();

  GPIO_ConfigureOutputA(GPIO_PinPos::_2, GPIO_OutputType::PushPull);

  return 0;
}
