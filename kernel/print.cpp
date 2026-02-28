#include <kernel/print.h>
#include <hal.h>

namespace kernel {
    void Console::print(const char* str) {
        vga_write(str);
    }

    void Console::print(char c) {
        vga_putchar(c);
    }
}