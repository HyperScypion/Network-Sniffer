#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <net/if_arp.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <net/if.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#define MAXBUF 65536

struct dhcphdr {
  uint8_t op;
  uint8_t htype;
  uint8_t hlen;
  uint8_t hops;
  uint32_t xid;
  uint16_t secs;
  uint16_t flags;
  uint8_t cia[4];
  uint8_t yia[4];
  uint8_t sia[4];
  uint8_t gia[4];
  uint32_t haddr[4];

};

void print_arp(struct arphdr *arp);
void print_hex(unsigned char *adr, unsigned char size);
void print_dec(unsigned char *adr, unsigned char size);
void print_eth(struct ethhdr *eth);
void print_ip4(struct iphdr *ip);
void print_ip6(struct ip6_hdr *ip6);
void print_tcp(struct tcphdr *tcp);
void print_udp(struct udphdr *udp);
void print_icmp(struct icmphdr *icmp);
void print_dhcp(struct dhcphdr *dhcp);
#endif
