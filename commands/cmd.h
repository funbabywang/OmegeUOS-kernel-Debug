#ifndef CMD_H
#define CMD_H

/* 启动 shell */
void shell_run(void);

/* 执行一条命令行 */
int execute_command(const char* cmdline);

#endif