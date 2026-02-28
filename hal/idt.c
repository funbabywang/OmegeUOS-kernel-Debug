#include <hal.h>

typedef struct {
    uint16_t base_low;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

static idt_entry_t idt[256];
static idt_ptr_t   idt_ptr;

// 外部汇编中断入口（在 boot.asm 中定义）
extern void isr0(void);  extern void isr1(void);  extern void isr2(void);  extern void isr3(void);
extern void isr4(void);  extern void isr5(void);  extern void isr6(void);  extern void isr7(void);
extern void isr8(void);  extern void isr9(void);  extern void isr10(void); extern void isr11(void);
extern void isr12(void); extern void isr13(void); extern void isr14(void); extern void isr15(void);
extern void isr16(void); extern void isr17(void); extern void isr18(void); extern void isr19(void);
extern void isr20(void); extern void isr21(void); extern void isr22(void); extern void isr23(void);
extern void isr24(void); extern void isr25(void); extern void isr26(void); extern void isr27(void);
extern void isr28(void); extern void isr29(void); extern void isr30(void); extern void isr31(void);
extern void isr32(void); extern void isr33(void); extern void isr34(void); extern void isr35(void);
extern void isr36(void); extern void isr37(void); extern void isr38(void); extern void isr39(void);
extern void isr40(void); extern void isr41(void); extern void isr42(void); extern void isr43(void);
extern void isr44(void); extern void isr45(void); extern void isr46(void); extern void isr47(void);

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_init(void) {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    // 将所有中断门初始化为内核代码段 (0x08)，标志 0x8E（32位中断门，特权级0）
    uint32_t isr_addresses[48] = {
        (uint32_t)isr0,  (uint32_t)isr1,  (uint32_t)isr2,  (uint32_t)isr3,
        (uint32_t)isr4,  (uint32_t)isr5,  (uint32_t)isr6,  (uint32_t)isr7,
        (uint32_t)isr8,  (uint32_t)isr9,  (uint32_t)isr10, (uint32_t)isr11,
        (uint32_t)isr12, (uint32_t)isr13, (uint32_t)isr14, (uint32_t)isr15,
        (uint32_t)isr16, (uint32_t)isr17, (uint32_t)isr18, (uint32_t)isr19,
        (uint32_t)isr20, (uint32_t)isr21, (uint32_t)isr22, (uint32_t)isr23,
        (uint32_t)isr24, (uint32_t)isr25, (uint32_t)isr26, (uint32_t)isr27,
        (uint32_t)isr28, (uint32_t)isr29, (uint32_t)isr30, (uint32_t)isr31,
        (uint32_t)isr32, (uint32_t)isr33, (uint32_t)isr34, (uint32_t)isr35,
        (uint32_t)isr36, (uint32_t)isr37, (uint32_t)isr38, (uint32_t)isr39,
        (uint32_t)isr40, (uint32_t)isr41, (uint32_t)isr42, (uint32_t)isr43,
        (uint32_t)isr44, (uint32_t)isr45, (uint32_t)isr46, (uint32_t)isr47
    };

    for (int i = 0; i < 48; i++) {
        idt_set_gate(i, isr_addresses[i], 0x08, 0x8E);
    }

    // 加载 IDT（使用内联汇编）
    asm volatile("lidt (%0)" : : "r" (&idt_ptr));
}