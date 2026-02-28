#include <fs.h>
#include <string.h> // 假设有自实现
#include <uefs.h>

static uefs_superblock_t sb;
static int mounted = 0;

// 模拟磁盘读写（实际需调用磁盘驱动）
static int disk_read_block(uint32_t lba, void* buf)
{
    // 占位：从模拟磁盘读取
    return 0;
}

static int disk_write_block(uint32_t lba, const void* buf)
{
    // 占位
    return 0;
}

int uefs_mount(const char* device)
{
    // 读取超级块（假设设备已打开，这里简化）
    if (disk_read_block(0, &sb) < 0)
        return -1;
    if (sb.magic != 0x55454653) // "UEFS"
        return -1;
    mounted = 1;
    return 0;
}

int uefs_read_inode(uint32_t ino, uefs_inode_t* inode)
{
    if (!mounted)
        return -1;
    uint32_t block = sb.inode_table_block + (ino * sizeof(uefs_inode_t)) / sb.block_size;
    uint32_t offset = (ino * sizeof(uefs_inode_t)) % sb.block_size;
    uint8_t buffer[512]; // 假设块大小512
    if (disk_read_block(block, buffer) < 0)
        return -1;
    memcpy(inode, buffer + offset, sizeof(uefs_inode_t));
    return 0;
}

int uefs_write_inode(uint32_t ino, uefs_inode_t* inode)
{
    if (!mounted)
        return -1;
    uint32_t block = sb.inode_table_block + (ino * sizeof(uefs_inode_t)) / sb.block_size;
    uint32_t offset = (ino * sizeof(uefs_inode_t)) % sb.block_size;
    uint8_t buffer[512];
    if (disk_read_block(block, buffer) < 0)
        return -1;
    memcpy(buffer + offset, inode, sizeof(uefs_inode_t));
    return disk_write_block(block, buffer);
}

int uefs_read_block(uint32_t block, void* buf) { return disk_read_block(block, buf); }

int uefs_write_block(uint32_t block, const void* buf) { return disk_write_block(block, buf); }