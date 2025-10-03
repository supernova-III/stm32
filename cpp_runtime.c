#include <stddef.h>

extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);
extern void (*__preinit_array_start[])(void);
extern void (*__preinit_array_end[])(void);

void __libc_init_array() {
  const size_t preinit_array_count = __preinit_array_end - __preinit_array_start;
  const size_t init_array_count = __init_array_end - __init_array_start;

  for (size_t i = 0; i < preinit_array_count; ++i) {
    __preinit_array_start[i]();
  }

  for (size_t i = 0; i < init_array_count; ++i) {
    __init_array_start[i]();
  }
}


