#ifndef FS_H
#define FS_H

#include <types.h>

/* 文件系统类型 */
typedef enum
{
    FS_TYPE_UEFS,
    FS_TYPE_UNKNOWN
} fs_type_t;

/* 文件系统挂载信息 */
struct mount
{
    char* device;   // 设备名（如 "hd0"）
    fs_type_t type; // 文件系统类型
    void* sb;       // 超级块指针
};

/* 文件操作接口 */
struct file_ops
{
    int (*open)(const char* path, int flags);
    int (*close)(int fd);
    int (*read)(int fd, void* buf, uint32_t count);
    int (*write)(int fd, const void* buf, uint32_t count);
    int (*lseek)(int fd, int offset, int whence);
};

/* 全局函数 */
void fs_init(void);
int mount(const char* device, const char* mountpoint, fs_type_t type);
int open(const char* path, int flags);
int close(int fd);
int read(int fd, void* buf, uint32_t count);
int write(int fd, const void* buf, uint32_t count);

#endif