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
	printf("%02x", adr[0]);
	while( ++i < size) {
		printf(":%02x", adr[i]);
		i += 1;
	}
	printf("\n");
}

void print_dec(unsigned char *adr, unsigned char size) {
	unsigned char i = 0;
	printf("%04x", adr[0]);
	while (++i < size) {
		printf("%u", adr[i]);
	}
	printf("\n");
}


void print_arp(struct arphdr *arp) {
	printf("\n~~~ARP~~~\n");
	printf("\tFormat of hardware address: %04x\n", ntohs(arp->ar_hrd));
	printf("\tFormat of protocol adress: %04x\n", ntohs(arp->ar_pro));
	printf("\tLength of hardware address: %x\n", arp->ar_hln);
	printf("\tLength of protocol address: %x\n", arp->ar_pln);
	printf("\tARP opcode: %x\n", ntohs(arp->ar_op));
	printf("\tSender hardware address: ");
/*	unsigned char *adr = (void *)arp+sizeof(*arp);
	print_hex(adr, arp->ar_hln);
*/
}

void print_dhcp(struct sockaddr_ll *sockll) {
	printf("\t\tPhysical-layer protocol: %u\n", sockll->sll_family);
	printf("\t\tInterface number: %u\n", sockll->sll_ifindex);
	printf("\t\tRP hardware type: %d\n", sockll->sll_hatype);
	printf("\t\tPacket type %x\n", sockll->sll_pkttype);
	printf("\t\tLength of address %d\n", sockll->sll_halen);	
}

void print_eth(struct ethhdr *eth) {
	printf("\n~~~Ethernet~~~\n");
	printf("Destination ethernet address: ");
	print_hex((void *)&eth->h_dest, ETH_ALEN);
	printf("Source ehernet address: ");
	print_hex((void *)&eth->h_source, ETH_ALEN);
	printf("Packet type ID: 0x%04x\n", ntohs(eth->h_proto));
}
