#ifndef MM_H
#define MM_H

#include <types.h>

/* 物理内存管理 */
void pmm_init(uint32_t mem_start, uint32_t mem_size);
void* pmm_alloc_page(void);
void pmm_free_page(void* page);

/* 虚拟内存管理（分页）*/
void vmm_init(void);
void vmm_map_page(uint32_t virt, uint32_t phys, uint32_t flags);
void vmm_unmap_page(uint32_t virt);

/* Slab 分配器 */
void slab_init(void);
void* kmalloc(uint32_t size);
void kfree(void* ptr);

#endif