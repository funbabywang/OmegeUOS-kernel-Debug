#include <hal.h>
#include <kernel/print.h>

// 内存管理
#include <mm/mm.h>

// 网络
#include <net/net.h>

// 驱动框架
#include <driver.h>
#include <input/keyboard.h>
#include <usb/uhci.h>
#include <usb/usb-keyboard.h>
#include <usb/usb.h>

// 包管理
#include <apt/apt.h>

// 文件系统
#include <fs.h>
#include <vfs.h>

// 命令行
#include <cmd.h>

using kernel::Console;

// 键盘映射表（供 irq_handler 使用）
static const char scancode_to_char[] = {
    0,    0,   '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',  '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',  '[', ']', '\n', 0,
    'a',  's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,   '\\', 'z',
    'x',  'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,   '*',  0,   ' '};

// 中断处理函数（由汇编调用）
extern "C" void irq_handler(uint32_t int_no)
{
    if (int_no >= 32 && int_no <= 47) {
        uint8_t irq = int_no - 32;
        switch (irq) {
            case 0: // 定时器
                // 可在此处增加 tick 计数
                break;
            case 1: // 键盘
            {
                uint8_t scancode = inb(0x60);
                if (!(scancode & 0x80)) { // 按键按下
                    char c = 0;
                    if (scancode < sizeof(scancode_to_char))
                        c = scancode_to_char[scancode];
                    if (c)
                        vga_putchar(c);
                }
                break;
            }
        }
        pic_send_eoi(irq);
    }
}

// C 接口包装，使汇编可以调用
extern "C" void kernel_main()
{
    // === HAL 初始化 ===
    vga_init();
    vga_write("Omege UOS Kernel starting...\n");

    gdt_init();
    idt_init();
    pic_remap();
    timer_init(100); // 100Hz
    keyboard_init();

    asm volatile("sti"); // 开启中断

    vga_write("HAL initialized.\n");

    // === 内存管理初始化 ===
    pmm_init(0x100000, 32 * 1024 * 1024); // 物理内存从 1MB 开始，32MB 大小
    vmm_init();
    slab_init();
    vga_write("Memory management initialized.\n");

    // 测试内存分配
    void* page = pmm_alloc_page();
    if (page) {
        Console::print("Allocated page at ");
        uint32_t addr = (uint32_t)page;
        char hex[12];
        hex[0] = '0';
        hex[1] = 'x';
        for (int i = 0; i < 8; i++) {
            uint8_t nibble = (addr >> (28 - i * 4)) & 0xF;
            hex[2 + i] = nibble < 10 ? '0' + nibble : 'A' + nibble - 10;
        }
        hex[10] = '\n';
        hex[11] = '\0';
        Console::print(hex);
    }

    // === 网络子系统初始化 ===
    net_init();
    vga_write("Network subsystem initialized.\n");

    // === 驱动框架初始化 ===
    driver_init_all();       // 注册所有驱动
    usb_init();              // USB 核心
    uhci_init();             // UHCI 主机控制器
    usb_keyboard_init();     // USB 键盘驱动
    keyboard_init_generic(); // 通用输入层
    vga_write("Drivers initialized.\n");

    // === 包管理子系统初始化 ===
    apt_init();
    apt_update(); // 更新包数据库
    vga_write("Package management initialized.\n");

    // 示例：列出已安装包
    vga_write("Installed packages:\n");
    apt_list_installed();

    // === 文件系统初始化 ===
    vfs_init();
    fs_init(); // 注册文件系统类型
    vga_write("File system initialized.\n");

    // 挂载根文件系统（假设设备 "hd0" 是 UEFS 格式）
    mount("hd0", "/", FS_TYPE_UEFS);
    vga_write("Root filesystem mounted.\n");

    // 测试文件操作
    int fd = open("/test.txt", 0);
    if (fd >= 0) {
        char buf[64];
        read(fd, buf, sizeof(buf));
        vga_write("File content: ");
        vga_write(buf);
        vga_putchar('\n');
        close(fd);
    }
    else {
        vga_write("Failed to open /test.txt\n");
    }

    vga_write("Kernel fully initialized. Starting shell...\n");

    // === 启动命令行界面 ===
    shell_run(); // 此函数内部有无限循环
}