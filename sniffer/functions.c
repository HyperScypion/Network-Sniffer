#include <net/if_arp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

#define eth_len 1518

void print_arp(struct arphdr arp) {
	ntohs(arp.ar_pro);
	ntohs(arp.ar_op);
	printf("Format of hardware address: %04x\n", ntohs(arp.ar_hrd));
	printf("Format of protocol adress: %04x\n", ntohs(arp.ar_pro));
	printf("Length of hardware address: %x\n", arp.ar_hln);
	printf("Length of protocol address: %x\n", arp.ar_pln);
	printf("ARP opcode: %x\n", ntohs(arp.ar_op));
	/*printf("Sender hardware address: ");
	int i;
	for (i = 0; i < 1518; ++i) {
		printf("%c", apr->__ar_sha[i]);
	}*/

}

