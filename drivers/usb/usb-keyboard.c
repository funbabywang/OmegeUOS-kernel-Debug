#include <input/input.h>
#include <usb/usb-keyboard.h>
#include <usb/usb.h>

static struct usb_device* g_keyboard_dev = NULL;

/* USB 键盘协议处理 */
static void usb_keyboard_poll(void)
{
    if (!g_keyboard_dev)
        return;
    uint8_t report[8]; // 键盘报告格式（Boot Protocol）
    struct usb_hc_ops* ops = usb_get_hc_ops();
    if (ops && ops->bulk_transfer) {
        ops->bulk_transfer(g_keyboard_dev, g_keyboard_dev->ep_in, report, 8, 1); // 1 表示输入
        // 解析报告，产生 input_event
        // 示例：report[2] 包含第一个按键
        uint8_t key = report[2];
        if (key) {
            struct input_event ev;
            ev.type = EV_KEY_DOWN;
            ev.code = key; // 需要映射为字符
            input_report_event(&ev);
        }
    }
}

static int usb_keyboard_probe(uint16_t vid, uint16_t pid)
{
    // 检查 vid/pid 是否为已知键盘
    return (vid == 0x1234 && pid == 0x5678); // 示例
}

static int usb_keyboard_init(void* device)
{
    g_keyboard_dev = (struct usb_device*)device;
    // 获取设备描述符，设置协议等
    return 0;
}

static struct driver_ops usb_keyboard_ops = {
    .probe = usb_keyboard_probe,
    .init = usb_keyboard_init,
    .read = NULL,
    .write = NULL,
};

void usb_keyboard_init(void)
{
    // 向驱动核心注册
    // driver_register(&usb_keyboard_ops, DEVICE_USB, 0x1234, 0x5678);
}