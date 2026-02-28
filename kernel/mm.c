#include <kernel/mm.h>
#include <hal.h>

// 假设物理内存 32MB，从 0x100000 (1MB) 开始可用（避开内核自身）
#define MEMORY_START 0x100000   // 1MB
#define MEMORY_SIZE  (32 * 1024 * 1024)  // 32MB
#define PAGE_SIZE    4096
#define PAGE_COUNT   (MEMORY_SIZE / PAGE_SIZE)

static uint8_t bitmap[PAGE_COUNT / 8];

// 简单 memset 实现，避免依赖库
static void memset(void* dest, uint8_t val, uint32_t count) {
    uint8_t* d = (uint8_t*)dest;
    while (count--) *d++ = val;
}

void mm_init(void) {
    memset(bitmap, 0, sizeof(bitmap));
    // 保留内核占用的页面（假设内核在 1MB 以内，但我们从 1MB 开始分配，所以不需要额外保留）
    // 如果需要保护内核代码，可以根据链接脚本计算并设置位图
}

void* alloc_page(void) {
    for (uint32_t i = 0; i < PAGE_COUNT; i++) {
        uint32_t byte = i / 8;
        uint8_t  bit = i % 8;
        if (!(bitmap[byte] & (1 << bit))) {
            bitmap[byte] |= (1 << bit);
            return (void*)(MEMORY_START + i * PAGE_SIZE);
        }
    }
    return 0;  // 无可用页
}

void free_page(void* page) {
    uint32_t addr = (uint32_t)page;
    if (addr < MEMORY_START || addr >= MEMORY_START + MEMORY_SIZE)
        return;  // 地址无效
    uint32_t i = (addr - MEMORY_START) / PAGE_SIZE;
    uint32_t byte = i / 8;
    uint32_t bit = i % 8;
    bitmap[byte] &= ~(1 << bit);
}