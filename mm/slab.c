#include <mm/mm.h>

// Slab 分配器框架（未实现）
void slab_init(void)
{
    // 初始化缓存
}

void* kmalloc(uint32_t size)
{
    // 简易实现：直接分配页
    if (size > 4096)
        return 0;
    return pmm_alloc_page();
}

void kfree(void* ptr) { pmm_free_page(ptr); }