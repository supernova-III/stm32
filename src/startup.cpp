#include <stddef.h>
#include <stdint.h>

#include "utils.h"
#include "rcc.h"
#include "gpio.h"

static auto& FPU_CPACR =
    *reinterpret_cast<volatile uint32_t* const>(0xE000ED88);

// Enables FPU
static void EnableFPU() {
  FPU_CPACR |= (0b1111 << 20);
}

void SystemInit() {
  EnableFPU();
}

extern size_t _sidata;
extern size_t _sdata;
extern size_t _edata;
extern size_t _sbss;
extern size_t _ebss;

void MemoryInit() {
  // copying .data to SRAM
  const size_t data_size = &_edata - &_sdata;
  auto* dst = reinterpret_cast<size_t*>(&_sdata);
  for (size_t i = 0; i < data_size; ++i) {
    dst[i] = (&_sidata)[i];
  }

  // zeroing out the bss
  const size_t bss_size = &_ebss - &_sbss;
  dst = reinterpret_cast<size_t*>(&_sbss);
  for (size_t i = 0; i < bss_size; ++i) {
    dst[i] = 0;
  }
}

extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);
extern void (*__preinit_array_start[])(void);
extern void (*__preinit_array_end[])(void);

void __libc_init_array() {
  const size_t preinit_array_count =
      __preinit_array_end - __preinit_array_start;
  const size_t init_array_count = __init_array_end - __init_array_start;

  for (size_t i = 0; i < preinit_array_count; ++i) {
    __preinit_array_start[i]();
  }

  for (size_t i = 0; i < init_array_count; ++i) {
    __init_array_start[i]();
  }
}

extern void main();

void DefaultHandler() {
  while (true) {
    __asm volatile("nop");
  }
}

void ResetHandler() {
  SystemInit();
  MemoryInit();

  __libc_init_array();

  main();

  DefaultHandler();
}

using InterruptHandler = void (*)();
extern "C" void _estack();

InterruptHandler interrupt_handlers[]
    __attribute__((section(".isr_vector"))) = {
        _estack,        ResetHandler,
        DefaultHandler,  // NMI_Handler
        DefaultHandler,  // HardFault_Handler
        DefaultHandler,  // MemManage_Handler
        DefaultHandler,  // BusFault_Handler
        DefaultHandler,  // UsageFault_Handler
        DefaultHandler,  // Reserved_
        DefaultHandler,  // Reserved_
        DefaultHandler,  // Reserved_
        DefaultHandler,  // Reserved_
        DefaultHandler,  // SVC_Handler
        DefaultHandler,  // DebugMon_Handler
        DefaultHandler,  // Reserved_
        DefaultHandler,  // PendSV_Handler
        DefaultHandler,  // SysTick_Handler
        DefaultHandler,  // Window WatchDog
        DefaultHandler,  // PVD through EXTI Line detection
        DefaultHandler,  // Tamper and TimeStamps through the EXTI line
        DefaultHandler,  // RTC Wakeup through the EXTI line
        DefaultHandler,  // FLASH
        DefaultHandler,  // RCC
        DefaultHandler,  // EXTI Line0
        DefaultHandler,  // EXTI Line1
        DefaultHandler,  // EXTI Line2
        DefaultHandler,  // EXTI Line3
        DefaultHandler,  // EXTI Line4
        DefaultHandler,  // DMA1 Stream 0
        DefaultHandler,  // DMA1 Stream 1
        DefaultHandler,  // DMA1 Stream 2
        DefaultHandler,  // DMA1 Stream 3
        DefaultHandler,  // DMA1 Stream 4
        DefaultHandler,  // DMA1 Stream 5
        DefaultHandler,  // DMA1 Stream 6
        DefaultHandler,  // ADC1, ADC2 and ADC3s
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // External Line[9:5]s
        DefaultHandler,  // TIM1 Break and TIM9
        DefaultHandler,  // TIM1 Update and TIM10
        DefaultHandler,  // TIM1 Trigger and Commutation and TIM11
        DefaultHandler,  // TIM1 Capture Compare
        DefaultHandler,  // TIM2
        DefaultHandler,  // TIM3
        DefaultHandler,  // TIM4
        DefaultHandler,  // I2C1 Event
        DefaultHandler,  // I2C1 Error
        DefaultHandler,  // I2C2 Event
        DefaultHandler,  // I2C2 Error
        DefaultHandler,  // SPI1
        DefaultHandler,  // SPI2
        DefaultHandler,  // USART1
        DefaultHandler,  // USART2
        DefaultHandler,  // Reserved
        DefaultHandler,  // External Line[15:10]s
        DefaultHandler,  // RTC Alarm (A and B) through EXTI Line
        DefaultHandler,  // USB OTG FS Wakeup through EXTI line
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // DMA1 Stream7
        DefaultHandler,  // Reserved
        DefaultHandler,  // SDIO
        DefaultHandler,  // TIM5
        DefaultHandler,  // SPI3
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // DMA2 Stream 0
        DefaultHandler,  // DMA2 Stream 1
        DefaultHandler,  // DMA2 Stream 2
        DefaultHandler,  // DMA2 Stream 3
        DefaultHandler,  // DMA2 Stream 4
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // USB OTG FS
        DefaultHandler,  // DMA2 Stream 5
        DefaultHandler,  // DMA2 Stream 6
        DefaultHandler,  // DMA2 Stream 7
        DefaultHandler,  // USART6
        DefaultHandler,  // I2C3 event
        DefaultHandler,  // I2C3 error
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // FPU
        DefaultHandler,  // Reserved
        DefaultHandler,  // Reserved
        DefaultHandler,  // SPI4
        DefaultHandler   // SPI5
};
