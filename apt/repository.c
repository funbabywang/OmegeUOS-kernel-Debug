#include <apt/apt.h>

static repository_t repos[10];
static uint32_t repo_count = 0;

void apt_add_repository(const char* name, const char* url)
{
    if (repo_count >= 10)
        return;
    strcpy(repos[repo_count].name, name);
    strcpy(repos[repo_count].url, url);
    repos[repo_count].enabled = 1;
    repo_count++;
}

int apt_update(void)
{
    // 从启用的源下载 Packages 列表并解析
    // 这里仅模拟
    load_package_db(); // 重新加载数据库
    return 0;
}