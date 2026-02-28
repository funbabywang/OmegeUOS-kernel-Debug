#include <hal.h>

#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

#define ICW1_INIT     0x11
#define ICW4_8086     0x01

void pic_remap(void) {
    // 初始化主片和从片
    outb(PIC1_CMD, ICW1_INIT);
    outb(PIC2_CMD, ICW1_INIT);

    // 设置偏移量：主片 IRQ0-7 映射到 32-39，从片 IRQ8-15 映射到 40-47
    outb(PIC1_DATA, 0x20);  // 主片偏移 32
    outb(PIC2_DATA, 0x28);  // 从片偏移 40

    // 级联设置
    outb(PIC1_DATA, 0x04);  // 主片 IRQ2 连接从片
    outb(PIC2_DATA, 0x02);  // 从片级联 ID

    // 设置 8086 模式
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    // 屏蔽所有中断（后续按需开启）
    outb(PIC1_DATA, 0xFD);  // 屏蔽除 IRQ1（键盘）外的所有主片中断
    outb(PIC2_DATA, 0xFF);  // 屏蔽所有从片中断
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC2_CMD, 0x20);
    }
    outb(PIC1_CMD, 0x20);
}