#ifndef NET_H
#define NET_H

#include <types.h>

/* 网络初始化 */
void net_init(void);

/* 以太网驱动接口 */
void ethernet_send(uint8_t* dest_mac, uint8_t* data, uint16_t len);
void ethernet_recv(void); // 中断处理

/* IP 协议 */
uint16_t ip_checksum(uint16_t* addr, int len);
void ip_send(uint32_t dest_ip, uint8_t protocol, uint8_t* data, uint16_t len);

/* UDP 协议 */
void udp_send(uint32_t dest_ip, uint16_t dest_port, uint16_t src_port, uint8_t* data, uint16_t len);

/* Socket 接口（简化）*/
int socket_create(int type);
int socket_bind(int sockfd, uint16_t port);
int socket_send(int sockfd, uint8_t* buf, uint16_t len);

#endif