// hal/vga.h
#ifndef HAL_VGA_H
#define HAL_VGA_H

#include <types.h>

void vga_init(void);
void vga_putchar(char c);
void vga_write(const char* str);

#endif