#ifndef HAL_H
#define HAL_H

#include <types.h>

/* io.c */
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);

/* vga.c */
void vga_init(void);
void vga_putchar(char c);
void vga_write(const char* str);

/* gdt.c */
void gdt_init(void);

/* idt.c */
void idt_init(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

/* pic.c */
void pic_remap(void);
void pic_send_eoi(uint8_t irq);

/* timer.c */
void timer_init(uint32_t frequency);

/* keyboard.c */
void keyboard_init(void);

#endif