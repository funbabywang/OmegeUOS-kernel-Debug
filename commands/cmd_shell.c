#include <cmd.h>
#include <hal/vga.h>

#define MAX_CMD_LINE 256
#define MAX_ARGS 16

/* 命令表结构 */
typedef struct
{
    const char* name;
    const char* description;
    int (*handler)(int argc, char** argv);
} command_t;

/* 前向声明 */
static int cmd_help(int argc, char** argv);
static int cmd_apt_get(int argc, char** argv);

/* 内置命令表 */
static command_t commands[] = {
    {"help", "Show this help message", cmd_help},
    {"apt-get", "Package manager commands", cmd_apt_get},
};
static int num_commands = sizeof(commands) / sizeof(command_t);

/* 简单的命令行解析 */
static int parse_cmdline(char* line, char** argv)
{
    int argc = 0;
    char* p = line;
    while (*p && argc < MAX_ARGS) {
        while (*p == ' ')
            p++;
        if (*p == '\0')
            break;
        argv[argc++] = p;
        while (*p && *p != ' ')
            p++;
        if (*p)
            *p++ = '\0';
    }
    return argc;
}

/* 执行命令 */
int execute_command(const char* cmdline)
{
    char line_copy[MAX_CMD_LINE];
    char* argv[MAX_ARGS];
    int i;

    /* 复制命令行（需要 strcpy，这里用简单循环代替） */
    const char* src = cmdline;
    char* dst = line_copy;
    while (*src && (dst - line_copy) < MAX_CMD_LINE - 1) {
        *dst++ = *src++;
    }
    *dst = '\0';

    int argc = parse_cmdline(line_copy, argv);
    if (argc == 0)
        return 0;

    for (i = 0; i < num_commands; i++) {
        /* 简单字符串比较 */
        const char* cmd_name = commands[i].name;
        const char* arg = argv[0];
        int match = 1;
        while (*cmd_name && *arg && *cmd_name == *arg) {
            cmd_name++;
            arg++;
        }
        if (*cmd_name == '\0' && *arg == '\0') {
            return commands[i].handler(argc, argv);
        }
    }
    vga_write("Command not found.\n");
    return -1;
}

/* help 命令实现 */
static int cmd_help(int argc, char** argv)
{
    vga_write("Available commands:\n");
    for (int i = 0; i < num_commands; i++) {
        vga_write("  ");
        vga_write(commands[i].name);
        vga_write(" - ");
        vga_write(commands[i].description);
        vga_putchar('\n');
    }
    return 0;
}

/* apt-get 命令实现（调用包管理子系统） */
static int cmd_apt_get(int argc, char** argv)
{
    if (argc < 3) {
        vga_write("Usage: apt-get [install|remove|update] <package>\n");
        return -1;
    }
    const char* action = argv[1];
    const char* pkg = argv[2];

    /* 简单的字符串比较 */
    int is_install = 1, is_remove = 1, is_update = 1;
    const char* a = action;
    const char* inst = "install";
    while (*a && *inst && *a == *inst) {
        a++;
        inst++;
    }
    if (*inst != '\0' || *a != '\0')
        is_install = 0;

    a = action;
    const char* rem = "remove";
    while (*a && *rem && *a == *rem) {
        a++;
        rem++;
    }
    if (*rem != '\0' || *a != '\0')
        is_remove = 0;

    a = action;
    const char* upd = "update";
    while (*a && *upd && *a == *upd) {
        a++;
        upd++;
    }
    if (*upd != '\0' || *a != '\0')
        is_update = 0;

    if (is_install) {
        // 调用 apt_install(pkg); 需要从 apt 子系统引入
        // 这里先简单输出
        vga_write("Installing ");
        vga_write(pkg);
        vga_write("...\n");
    }
    else if (is_remove) {
        vga_write("Removing ");
        vga_write(pkg);
        vga_write("...\n");
    }
    else if (is_update) {
        vga_write("Updating package list...\n");
    }
    else {
        vga_write("Unknown action.\n");
    }
    return 0;
}

/* shell 主循环 */
void shell_run(void)
{
    vga_write("\nOmege UOS Shell v0.1\n");
    vga_write("Type 'help' for available commands.\n");

    /* 为了演示，直接执行一条测试命令 */
    vga_write("$ apt-get install base\n");
    execute_command("apt-get install base");

    /* 实际应循环读取用户输入，但当前缺少行输入支持，故暂停 */
    while (1) {
        asm volatile("hlt");
    }
}