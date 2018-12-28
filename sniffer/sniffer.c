#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include "functions.h"

/*unsigned char buff[MAXBUF];*/

int main(int argc, char *argv[]) {
	struct arphdr *arp;
	int sock;
	unsigned char buff[MAXBUF];
	int pom;
	struct ethhdr *eth = (void *)buff;
	struct ifreq ifr;
	if (argc < 2) {
		
		printf("Usage: filename network interface\n");
		exit(1);
	}	
	else if (argc == 2) {	
		
		if ((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1) {
			perror("Socket error\n");
			exit(1);
		}
		strncpy((char *)ifr.ifr_name, argv[1], IF_NAMESIZE);
		ifr.ifr_flags |= IFF_PROMISC;
	       	if (ioctl(sock, SIOCGIFFLAGS, &ifr) == -1) {
			perror("Ioctl error");
			exit(1);
		}	
		printf("Sniffing have been started\n");
		while ((pom = recv(sock, buff, MAXBUF, 0)) != -1) {
			print_eth(eth);

			switch(ntohs(eth->h_proto)) {

			    case ETH_P_ARP: {
			            print_arp((void *)(eth+1));
			            break;
			        }

			    case ETH_P_IP: {
			            print_ip4((void *)(eth+1));
			            break;
			    }
			    case ETH_P_IPV6: {
						print_ip6((void *)(eth+1));

			    }
			}
			
		}
	}
	else if (argc > 2) {
		perror("Too much arguments\n");
		exit(1);
	}
	return 0;
}
