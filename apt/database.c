#include <apt/apt.h>
#include <string.h>

// 简化的本地数据库：模拟从某个存储读取包信息
// 实际应读取文件系统中的 /var/lib/dpkg/status 类似文件

int load_package_db(void)
{
    // 示例：静态数据
    static package_t sample_pkgs[] = {{.name = "base",
                                       .version = "1.0",
                                       .description = "Base system",
                                       .size = 1024,
                                       .depends = NULL,
                                       .depend_count = 0,
                                       .installed = 1},
                                      {.name = "kernel",
                                       .version = "5.4",
                                       .description = "Omege UOS Kernel",
                                       .size = 2048,
                                       .depends = NULL,
                                       .depend_count = 0,
                                       .installed = 1},
                                      {.name = "bash",
                                       .version = "4.4",
                                       .description = "Bourne Again SHell",
                                       .size = 512,
                                       .depends = NULL,
                                       .depend_count = 0,
                                       .installed = 0}};
    // 实际应动态分配
    db.packages = sample_pkgs;
    db.count = sizeof(sample_pkgs) / sizeof(package_t);
    return 0;
}