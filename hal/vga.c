// hal/vga.c
#include <hal/vga.h>
#include <hal/io.h>

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static uint16_t* vga_buffer;
static uint8_t   vga_row, vga_col;
static uint8_t   vga_color = 0x0F;  // °×µ×ºÚ×Ö

void vga_init(void) {
    vga_buffer = (uint16_t*)VGA_ADDRESS;
    vga_row = vga_col = 0;
    for (int y = 0; y < VGA_HEIGHT; y++)
        for (int x = 0; x < VGA_WIDTH; x++)
            vga_buffer[y * VGA_WIDTH + x] = (vga_color << 8) | ' ';
}

void vga_putchar(char c) {
    if (c == '\n') {
        vga_col = 0;
        if (++vga_row == VGA_HEIGHT) vga_row = 0;
        return;
    }
    vga_buffer[vga_row * VGA_WIDTH + vga_col] = (vga_color << 8) | c;
    if (++vga_col == VGA_WIDTH) {
        vga_col = 0;
        if (++vga_row == VGA_HEIGHT) vga_row = 0;
    }
}

void vga_write(const char* str) {
    while (*str) vga_putchar(*str++);
}