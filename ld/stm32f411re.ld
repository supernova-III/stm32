MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS 
{
  .isr_vector ORIGIN(FLASH) :
  {
    KEEP(*(.isr_vector))
  } >FLASH

  .text ALIGN(4):
  {
    *(.text)
    *(.rodata)
  } >FLASH

  _sidata = .;

  .data : AT(_sidata)
  {
    _sdata = .;
    *(.data)
    _edata = .;
  } >SRAM
  
  .bss :
  {
    _sbss = .;
    *(.bss)
    *(COMMON)
    _ebss = .;
  } >SRAM

  .init_array :
  {
    __init_array_start = .;
    KEEP(*(.init_array*))
    __init_array_end = .;
  } > FLASH

  .preinit_array :
  {
    __preinit_array_start = .;
    KEEP(*(.preinit_array*))
    __preinit_array_end = .;
  } > FLASH
}
