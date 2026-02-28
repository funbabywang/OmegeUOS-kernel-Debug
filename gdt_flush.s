
; gdt_flush.s
global gdt_flush
gdt_flush:
    mov eax, [esp+4]    ; 获取 gdt_ptr 指针
    lgdt [eax]          ; 加载 GDT
    mov ax, 0x10        ; 数据段选择子
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush     ; 远跳转刷新 CS
.flush:
    ret