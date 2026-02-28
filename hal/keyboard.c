#include <hal.h>

// 键盘中断处理函数（在 main.cpp 中定义）
extern void keyboard_handler(void);

static const char scancode_to_char[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

void keyboard_init(void) {
    // 启用键盘中断（PIC 中已开 IRQ1）
    // 可选：设置键盘 LED 等
}