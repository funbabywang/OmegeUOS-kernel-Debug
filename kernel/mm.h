#ifndef KERNEL_MM_H
#define KERNEL_MM_H

void mm_init(void);
void* alloc_page(void);
void free_page(void* page);

#endif