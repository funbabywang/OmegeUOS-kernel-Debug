; Multiboot 头
section .multiboot
align 4
    dd 0x1BADB002              ; 魔数
    dd 0x00                     ; 标志
    dd -(0x1BADB002 + 0x00)     ; 校验和

section .text
global start
extern kernel_main             ; 内核入口（C++ 函数）

start:
    ; 设置栈指针（栈位于 BSS 段）
    mov esp, stack_top

    ; 调用内核主函数
    call kernel_main

.halt:
    cli
    hlt
    jmp .halt

section .bss
align 16
stack_bottom:
    resb 16384                  ; 16 KB 栈空间
stack_top: