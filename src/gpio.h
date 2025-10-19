#pragma once
#include "utils.h"

struct _GPIO {
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

extern _GPIO& GPIOA;
extern _GPIO& GPIOB;
