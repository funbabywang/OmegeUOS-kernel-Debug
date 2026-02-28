#include <mm/mm.h>
#include <string.h> // 假设有自实现 memset

#define PAGE_SIZE 4096

static uint32_t mem_start;
static uint32_t mem_pages;
static uint8_t* bitmap;

// 简单位图初始化
void pmm_init(uint32_t start, uint32_t size)
{
    mem_start = start;
    mem_pages = size / PAGE_SIZE;
    bitmap = (uint8_t*)start; // 将位图放在内存开头（简化）
    memset(bitmap, 0, mem_pages / 8);
}

void* pmm_alloc_page(void)
{
    for (uint32_t i = 0; i < mem_pages; i++) {
        uint32_t byte = i / 8;
        uint8_t bit = i % 8;
        if (!(bitmap[byte] & (1 << bit))) {
            bitmap[byte] |= (1 << bit);
            return (void*)(mem_start + i * PAGE_SIZE);
        }
    }
    return 0;
}

void pmm_free_page(void* page)
{
    uint32_t addr = (uint32_t)page;
    if (addr < mem_start || addr >= mem_start + mem_pages * PAGE_SIZE)
        return;
    uint32_t i = (addr - mem_start) / PAGE_SIZE;
    uint32_t byte = i / 8;
    uint8_t bit = i % 8;
    bitmap[byte] &= ~(1 << bit);
}