#include <apt/apt.h>
#include <string.h>

int apt_install(const char* pkg_name)
{
    for (uint32_t i = 0; i < db.count; i++) {
        if (strcmp(db.packages[i].name, pkg_name) == 0) {
            if (db.packages[i].installed) {
                // 已安装
                return -1;
            }
            // 检查依赖（略）
            // 执行安装：复制文件等（无文件系统，仅标记）
            db.packages[i].installed = 1;
            return 0;
        }
    }
    return -2; // 未找到
}

int apt_remove(const char* pkg_name)
{
    for (uint32_t i = 0; i < db.count; i++) {
        if (strcmp(db.packages[i].name, pkg_name) == 0) {
            if (!db.packages[i].installed)
                return -1;
            // 移除依赖检查（略）
            db.packages[i].installed = 0;
            return 0;
        }
    }
    return -2;
}