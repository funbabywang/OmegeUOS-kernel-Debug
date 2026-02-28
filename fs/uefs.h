#ifndef UEFS_H
#define UEFS_H

#include <types.h>

/* UEFS 超级块 */
typedef struct uefs_superblock
{
    uint32_t magic;             // 魔数 0x55454653 ("UEFS")
    uint32_t block_size;        // 块大小
    uint32_t total_blocks;      // 总块数
    uint32_t inode_table_block; // inode 表起始块号
    uint32_t inode_count;       // inode 总数
    uint32_t free_blocks;       // 空闲块数
    uint32_t free_inodes;       // 空闲 inode 数
    uint8_t padding[480];       // 填充到 512 字节
} __attribute__((packed)) uefs_superblock_t;

/* UEFS inode */
typedef struct uefs_inode
{
    uint16_t mode;            // 文件类型及权限
    uint16_t uid;             // 所有者ID
    uint32_t size;            // 文件大小
    uint32_t blocks[12];      // 直接块指针
    uint32_t indirect_block;  // 一级间接块指针
    uint32_t doubly_indirect; // 二级间接块指针
    uint32_t ctime;           // 创建时间
    uint32_t mtime;           // 修改时间
    uint32_t atime;           // 访问时间
    uint16_t gid;             // 组ID
    uint16_t links;           // 硬链接计数
    uint8_t padding[52];      // 填充到 128 字节
} __attribute__((packed)) uefs_inode_t;

/* 目录项 */
typedef struct uefs_dirent
{
    uint32_t inode;    // inode 编号
    uint16_t rec_len;  // 记录长度
    uint8_t name_len;  // 文件名长度
    uint8_t file_type; // 文件类型
    char name[255];    // 文件名（变长）
} __attribute__((packed)) uefs_dirent_t;

/* UEFS 操作接口 */
int uefs_mount(const char* device);
int uefs_read_inode(uint32_t ino, uefs_inode_t* inode);
int uefs_write_inode(uint32_t ino, uefs_inode_t* inode);
int uefs_read_block(uint32_t block, void* buf);
int uefs_write_block(uint32_t block, const void* buf);

#endif