#include <net/net.h>

int socket_create(int type)
{
    // 分配一个 socket 描述符
    return 0;
}

int socket_bind(int sockfd, uint16_t port)
{
    // 绑定本地端口
    return 0;
}

int socket_send(int sockfd, uint8_t* buf, uint16_t len)
{
    // 根据 socket 类型调用相应协议发送
    return 0;
}