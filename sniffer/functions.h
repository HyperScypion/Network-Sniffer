#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <net/if_arp.h>
#include <netinet/ip.h>
#include <net/if.h>
#define MAXBUF 65536
void print_arp(struct arphdr *arp);
void print_hex(unsigned char *adr, unsigned char size);
void print_dec(unsigned char *adr, unsigned char size);
void print_dhcp(struct sockaddr_ll *sockll);
void print_eth(struct ethhdr *eth);
void print_ip4(struct iphdr *ip);
/* void print_ip4(struct iphdr *ip); */
#endif
