#ifndef KERNEL_PRINT_H
#define KERNEL_PRINT_H

namespace kernel {
    class Console {
    public:
        static void print(const char* str);
        static void print(char c);
    };
}

#endif