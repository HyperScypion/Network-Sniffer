#include <net/if_arp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <netinet/ip6.h>
#include <netinet/ip_icmp.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include "functions.h"

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
		printf(":%04x", adr[i]);
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
	unsigned char *adr = (void *)arp+sizeof(*arp);
	print_hex(adr, arp->ar_hln);

}


void print_eth(struct ethhdr *eth) {
	printf("\n~~~Ethernet~~~\n");
	printf("Destination ethernet address: ");
	print_hex((void *)&eth->h_dest, ETH_ALEN);
	printf("Source ehernet address: ");
	print_hex((void *)&eth->h_source, ETH_ALEN);
	printf("Packet type ID: 0x%04x", ntohs(eth->h_proto));
}

void print_ip4(struct iphdr *ip) {
	printf("\n\t~~~IP~~~\n");
	printf("\tVersion: %u\n", ip->version);
	printf("\tToS: %u\n", ip->tos);
	printf("\tTotal length: %u\n", ip->tot_len);
	printf("\tID: %u\n", ip->id);
	printf("\tFragment offset: %u\n", ip->frag_off);
	printf("\tTTL: %u\n", ip->ttl);
	printf("\tProtocol: %u\n", ip->protocol);
	printf("\tCheck: %u\n", ip->check);
	printf("\tSource address: ");
	print_dec((void *)ip+12, 4);
	printf("\tDestination address: ");
	print_dec((void *)ip+16, 4);
	switch (ip->protocol) {
		case IPPROTO_TCP:
			print_tcp((void *)ip+ip->ihl*4);
			break;
		case IPPROTO_UDP:
			print_udp((void *)ip+ip->ihl*4);
			break;
		case IPPROTO_ICMP:
			print_icmp((void *)ip+ip->ihl*4);
	}
}

void print_ip6(struct ip6_hdr *ip6) {
    printf("\t~~~IPV6~~~\n");
    printf("\tPayload length: %u\n", ntohl(ip6->ip6_plen));
    printf("\tNext header: %u\n", ntohs(ip6->ip6_nxt));
    printf("\tHop limit: %u", ntohs(ip6->ip6_hlim));

}

void print_udp(struct udphdr *udp) {
	printf("\t\t~~~UDP~~~\n");
	printf("\t\tSource: %u\n", ntohs(udp->source));
	printf("\t\tDestination: %u\n", ntohs(udp->dest));
	printf("\t\tLength: %u\n", ntohs(udp->len));
	printf("\t\tCheck: %u", udp->check);
	if (ntohs(udp->source) == 67 && ntohs(udp->dest) == 67) {
		print_dhcp((void *)(udp+1));
	}
}

void print_tcp(struct tcphdr *tcp) {
	printf("\t\t~~~TCP~~~\n");
	printf("\t\tSource port: %u\n", ntohs(tcp->source));
	printf("\t\tDestination port: %u\n", ntohs(tcp->dest));
	printf("\t\tSequence: %u\n", ntohl(tcp->seq));
	printf("\t\tAck sequence: %u\n", ntohl(tcp->ack_seq));
	printf("\t\tWindow: %u\n", ntohs(tcp->window));
	printf("\t\tCheck: %u\n", tcp->check);
	printf("\t\tUrgent pointer: %u\n", ntohs(tcp->urg_ptr));
}

void print_icmp(struct icmphdr *icmp) {
	printf("\t\t~~~ICMP~~~\n");
	printf("\t\tMessage type: %u\n", icmp->type);
	printf("\t\tCode: %u\n", icmp->code);
	printf("\t\tChecksum: 0x%04x\n", ntohs(icmp->checksum));
}

void print_dhcp(struct dhcphdr *dhcp) {
	printf("\n~~~DHCP~~~\n");
	printf("\t\t\tOperation: %u\n", dhcp->op);
	printf("\t\t\tType of hardware address:  %u\n", dhcp->htype);
	printf("\t\t\tLength of hardware address:  %u\n", dhcp->hlen);
	printf("\t\t\tHops:  %u\n", dhcp->hops);
	printf("\t\t\tXID:  0x%08X\n", ntohl(dhcp->xid));
	printf("\t\t\tSECS:  %u\n", ntohs(dhcp->secs));
	printf("\t\t\tClient IP: ");
	print_dec(dhcp->cia, 4);
	printf("\n");
	printf("\t\t\tYour IP: ");
	print_dec(dhcp->yia, 4);
	printf("\n");
	printf("\t\t\tGateway IP: ");
	print_dec(dhcp->gia, 4);
	printf("\n");

}
