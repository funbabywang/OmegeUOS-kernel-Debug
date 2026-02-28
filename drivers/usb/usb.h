#ifndef USB_H
#define USB_H

#include <types.h>

/* USB 设备描述符（简化）*/
struct usb_device
{
    uint8_t address;
    uint16_t vid;
    uint16_t pid;
    uint8_t class_code;
    uint8_t subclass;
    uint8_t protocol;
    uint8_t ep_in;    // 输入端点地址
    uint8_t ep_out;   // 输出端点地址
    void* hc_private; // 主机控制器私有数据
};

/* 主机控制器操作 */
struct usb_hc_ops
{
    int (*init)(void);
    int (*control_transfer)(struct usb_device* dev, uint8_t bmRequestType, uint8_t bRequest,
                            uint16_t wValue, uint16_t wIndex, uint16_t wLength, void* data);
    int (*bulk_transfer)(struct usb_device* dev, uint8_t endpoint, void* data, uint16_t len,
                         int dir_in);
};

/* USB 核心接口 */
void usb_init(void);
int usb_register_device(struct usb_device* dev);
struct usb_hc_ops* usb_get_hc_ops(void);

#endif