#include <hal.h>

// 定时器中断处理函数（在 main.cpp 中定义）
extern void timer_handler(void);

void timer_init(uint32_t frequency) {
    // 计算 PIT 分频值：1193180 Hz / 频率
    uint32_t divisor = 1193180 / frequency;

    // 设置 PIT 通道 0 为模式 2（比率发生器）
    outb(0x43, 0x36);  // 通道0，先写低字节后高字节，模式3，二进制

    // 发送分频值
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}