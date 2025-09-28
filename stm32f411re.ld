MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

_sidata = LOADADDR(.data);

SECTIONS 
{
  .isr_vector ORIGIN(FLASH) :
  {
    KEEP(*(.isr_vector))
  } >FLASH

  .text ALIGN(4):
  {
    *(.text*)
    *(.rodata*)
  } >FLASH


  .data : AT(_sidata)
  {
    _sdata = .;
    *(.data*)
    _edata = .;
  } >SRAM
  
  .bss :
  {
    _sbss = .;
    *(.bss*)
    *(COMMON)
    _ebss = .;
  } >SRAM
}
