#include <net/if_arp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <sys/socket.h>

void print_hex(unsigned char *adr, unsigned char size) {
	unsigned char i = 0;
	while( i <= size) {
		printf("%02x", adr[i]);
		i += 1;
	}
	printf("\n");
}

void print_dec(unsigned char *adr, unsigned char size) {
	unsigned char i = 0;
	while (i <= size) {
		printf("%u", adr[i]);
	}
	printf("\n");
}


void print_arp(struct arphdr *arp) {
	printf("\t~~~ARP~~~");
	printf("Format of hardware address: %04x\n", ntohs(arp->ar_hrd));
	printf("Format of protocol adress: %04x\n", ntohs(arp->ar_pro));
	printf("Length of hardware address: %x\n", arp->ar_hln);
	printf("Length of protocol address: %x\n", arp->ar_pln);
	printf("ARP opcode: %x\n", ntohs(arp->ar_op));
	printf("Sender hardware address: ");
/*	unsigned char *adr = (void *)arp+sizeof(*arp);
	print_hex(adr, arp->ar_hln);
*/
}

void print_dhcp(struct sockaddr_ll *sockll) {
	printf("Physical-layer protocol: %u\n", sockll->sll_family);
	printf("Interface number: %u\n", sockll->sll_ifindex);
	printf("RP hardware type: %d\n", sockll->sll_hatype);
	printf("Packet type %x\n", sockll->sll_pkttype);
	printf("Length of address %d\n", sockll->sll_halen);	
}

void print_eth(struct ethhdr *eth) {
}
