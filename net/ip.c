#include <net/net.h>

uint16_t ip_checksum(uint16_t* addr, int len)
{
    uint32_t sum = 0;
    while (len > 1) {
        sum += *addr++;
        len -= 2;
    }
    if (len)
        sum += *(uint8_t*)addr;
    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);
    return ~sum;
}

void ip_send(uint32_t dest_ip, uint8_t protocol, uint8_t* data, uint16_t len)
{
    // 构造 IP 头，调用以太网发送
    // 需要先获取目标 MAC（ARP 未实现）
}