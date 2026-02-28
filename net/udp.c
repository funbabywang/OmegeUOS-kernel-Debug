#include <net/net.h>

void udp_send(uint32_t dest_ip, uint16_t dest_port, uint16_t src_port, uint8_t* data, uint16_t len)
{
    // 构造 UDP 头，调用 IP 发送
}