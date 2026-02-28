#include <hal/vga.h> // 用于演示输出
#include <input/input.h>

static void keyboard_event_handler(struct input_event* ev)
{
    // 简单处理：在屏幕上显示按键字符
    if (ev->type == EV_KEY_DOWN) {
        char c = (char)ev->code; // 假设 code 是 ASCII 或扫描码映射
        vga_putchar(c);
    }
}

void keyboard_init_generic(void) { input_register_device(keyboard_event_handler); }