#pragma once
#include "utils.h"

struct _RCC {
  Register CR;
  Register PLLCFGR;
  Register CFGR;
  Register CIR;
  Register AHB1RSTR;
  Register AHB2RSTR;
  Register __reserved0[2];
  Register APB1RSTR;
  Register APB2RSTR;
  Register __reserved1[2];
  Register AHB1ENR;
  Register AHB2ENR;
  Register __reserved3[2];
  Register APB1ENR;
  Register APB2ENR;
  Register __reserved4[2];
  Register AHB1LPENR;
  Register AHB2LPENR;
  Register __reserved5[2];
  Register APB1LPENR;
  Register APB2LPENR;
  Register __reserved6[2];
  Register BDCR;
  Register CSR;
  Register __reserved7[2];
  Register SSCGR;
  Register PLLI2SCFGR;
  Register __reserved8;
  Register DCKCFGR;
};

extern _RCC &RCC;
