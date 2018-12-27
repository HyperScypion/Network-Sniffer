#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[]) {
	struct arphdr arp;

	if (argc < 2) {
		/* Sniffuj wszystko */
		printf("Sniffuje wszystko\n");
		while (1) {
			break;
		}
	}	
	else if (argc == 2) {	
		/* Sniffuj wybrane */
		if (argv[1][1] == 'a') {
			printf("Sniffuje po ARP\n");
			while (1) {
				print_arp(arp);
			}

		}
		if (argv[1][1] == 'd') {
			printf("Sniffuje po DHCP\n");
		}
	}
	else if (argc > 2) {
		perror("Zbyt duza ilosc argumentow\n");
		exit(0);
	}
	return 0;
}
