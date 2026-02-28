#include <net/net.h>

// 假设的网卡基地址（需根据实际硬件配置）
#define NIC_BASE 0x1000

void ethernet_send(uint8_t* dest_mac, uint8_t* data, uint16_t len)
{
    // 填充以太网帧头并发送
    // 示例：使用端口 I/O 操作网卡寄存器
}

void ethernet_recv(void)
{
    // 从网卡缓冲区读取数据包
    // 解析以太网头，根据协议类型向上传递
}