#include <apt/apt.h>
#include <string.h> // 假设有自实现或依赖

static package_db_t db; // 全局包数据库

void apt_init(void)
{
    db.packages = NULL;
    db.count = 0;
    // 从本地数据库加载已安装包信息（未实现）
}

int apt_search(const char* keyword)
{
    for (uint32_t i = 0; i < db.count; i++) {
        if (strstr(db.packages[i].name, keyword) != NULL) {
            // 输出包信息（需要printf实现，暂用vga_write）
            // vga_write(db.packages[i].name); 等
        }
    }
    return 0;
}

void apt_list_installed(void)
{
    for (uint32_t i = 0; i < db.count; i++) {
        if (db.packages[i].installed) {
            // 输出
        }
    }
}