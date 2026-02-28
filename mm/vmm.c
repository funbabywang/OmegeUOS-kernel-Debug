#include <mm/mm.h>

// 虚拟内存管理占位（x86 分页）
void vmm_init(void)
{
    // 设置 CR3 等（待实现）
}

void vmm_map_page(uint32_t virt, uint32_t phys, uint32_t flags)
{
    // 填充页表（待实现）
}

void vmm_unmap_page(uint32_t virt)
{
    // 清空页表项
}