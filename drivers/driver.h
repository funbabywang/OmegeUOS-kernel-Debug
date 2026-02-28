#ifndef DRIVER_H
#define DRIVER_H

#include <types.h>

/* 设备类型枚举 */
enum device_type
{
    DEVICE_NONE,
    DEVICE_PCI,
    DEVICE_USB,
    DEVICE_INPUT,
    DEVICE_STORAGE,
};

/* 驱动操作结构 */
struct driver_ops
{
    int (*probe)(uint32_t vid, uint32_t pid); // 探测设备
    int (*init)(void* device);                // 初始化设备
    int (*read)(void* device, void* buf, uint32_t len);
    int (*write)(void* device, const void* buf, uint32_t len);
};

/* 设备结构 */
struct device
{
    enum device_type type;
    uint32_t vid, pid;      // 厂商/产品ID
    void* private_data;     // 驱动私有数据
    struct driver_ops* ops; // 设备操作
};

/* 驱动注册 */
int driver_register(struct driver_ops* ops, enum device_type type, uint32_t vid, uint32_t pid);
void driver_init_all(void); // 内核调用，初始化所有驱动

#endif