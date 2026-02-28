#ifndef APT_H
#define APT_H

#include <types.h>

/* 软件包结构 */
typedef struct
{
    char name[64];         // 包名
    char version[32];      // 版本号
    char description[256]; // 描述
    uint32_t size;         // 大小（字节）
    char** depends;        // 依赖列表（NULL结尾）
    uint32_t depend_count;
    uint8_t installed; // 是否已安装
} package_t;

/* 软件源结构 */
typedef struct
{
    char url[128];   // 源地址（本地路径或网络URL）
    char name[32];   // 源名称
    uint8_t enabled; // 是否启用
} repository_t;

/* 包数据库 */
typedef struct
{
    package_t* packages; // 软件包数组
    uint32_t count;      // 包数量
} package_db_t;

/* 公共接口 */
void apt_init(void);
int apt_update(void); // 更新软件源列表
int apt_install(const char* pkg_name);
int apt_remove(const char* pkg_name);
int apt_search(const char* keyword);
void apt_list_installed(void);

#endif