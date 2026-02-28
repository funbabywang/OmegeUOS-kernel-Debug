#ifndef VFS_H
#define VFS_H

#include <types.h>

/* 文件描述符 */
typedef struct file
{
    uint32_t inode;      // inode 编号
    uint32_t pos;        // 当前读写位置
    uint32_t flags;      // 打开标志
    struct mount* mount; // 挂载点
} file_t;

/* VFS 初始化 */
void vfs_init(void);

/* 系统调用接口（供用户态使用）*/
int sys_open(const char* path, int flags);
int sys_close(int fd);
int sys_read(int fd, void* buf, uint32_t count);
int sys_write(int fd, const void* buf, uint32_t count);

#endif