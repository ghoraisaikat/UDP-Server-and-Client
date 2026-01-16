#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: talk hostname message\n");
		return 1;
	}
	
	int dest;
	struct addrinfo hints, *res, *p;
	int rv;
	int bytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_family = AF_INET;

	if ((rv = getaddrinfo(argv[1], "3490", &hints, &res)) == -1) {
		fprintf(stderr, "Shit happened during addrinfo()!");
		return 1;
	}

	for (p = res; p != NULL; p = p->ai_next){
		if ((dest = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			fprintf(stderr, "Shit happened during socket()!");
			continue;
		}
		break;
	}

	if (p == NULL) {
		perror("Couldn't create socket");
		return 2;
	}

	if ((bytes = sendto(dest, argv[2], strlen(argv[2]), 0, p->ai_addr, p->ai_addrlen)) == -1) {
		perror("sendto()");
		freeaddrinfo(res);
		exit(1);
	}

	printf("Sent %d bytes to %s\n", bytes, argv[1]);
	close(dest);
	return 0;
}
