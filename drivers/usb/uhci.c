#include <hal/io.h> // 端口 I/O
#include <usb/uhci.h>
#include <usb/usb.h>

/* UHCI 寄存器地址（示例）*/
#define UHCI_BASE 0x4000

static int uhci_control_transfer(struct usb_device* dev, uint8_t bmRequestType, uint8_t bRequest,
                                 uint16_t wValue, uint16_t wIndex, uint16_t wLength, void* data)
{
    // 构造 SETUP 包，通过 UHCI 发送（简化）
    // 这里仅占位，实际需要操作链表描述符
    return 0;
}

static int uhci_bulk_transfer(struct usb_device* dev, uint8_t endpoint, void* data, uint16_t len,
                              int dir_in)
{
    // 构造批量传输描述符
    return 0;
}

static struct usb_hc_ops uhci_ops = {
    .init = NULL, // 由 uhci_init 完成
    .control_transfer = uhci_control_transfer,
    .bulk_transfer = uhci_bulk_transfer,
};

void uhci_init(void)
{
    // 检测 UHCI 控制器（PCI 探测略）
    // 初始化寄存器
    // 注册主机控制器操作到 USB 核心
    // usb_register_hc(&uhci_ops);  // 需要 USB 核心提供此函数
}