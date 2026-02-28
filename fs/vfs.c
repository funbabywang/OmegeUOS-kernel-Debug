#include <fs.h>
#include <uefs.h>
#include <vfs.h>

#define MAX_FILES 64
static file_t file_table[MAX_FILES];
static int next_fd = 3; // 0,1,2 预留给 stdin,out,err

void vfs_init(void)
{
    for (int i = 0; i < MAX_FILES; i++)
        file_table[i].mount = NULL;
}

int sys_open(const char* path, int flags)
{
    // 简化：查找文件 inode，分配文件描述符
    // 此处假定根目录下固定文件 "test.txt"
    if (strcmp(path, "/test.txt") == 0) {
        int fd = next_fd++;
        file_table[fd].inode = 1; // 假定 inode 1 是 test.txt
        file_table[fd].pos = 0;
        file_table[fd].flags = flags;
        file_table[fd].mount = NULL; // 实际应指向挂载点
        return fd;
    }
    return -1;
}

int sys_close(int fd)
{
    if (fd < 0 || fd >= MAX_FILES)
        return -1;
    file_table[fd].mount = NULL;
    return 0;
}

int sys_read(int fd, void* buf, uint32_t count)
{
    if (fd < 0 || fd >= MAX_FILES)
        return -1;
    file_t* f = &file_table[fd];
    // 从 inode 读取数据（简化，直接返回假数据）
    // 这里应调用 uefs_read_block 等
    const char* test_data = "Hello from UEFS!";
    uint32_t len = strlen(test_data);
    if (count > len)
        count = len;
    memcpy(buf, test_data, count);
    f->pos += count;
    return count;
}

int sys_write(int fd, const void* buf, uint32_t count)
{
    // 简化，不做实际写入
    return count;
}