#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT "3490"
#define MAXBUFLEN 1000

int main(int argc, char *argv[]) {
	int sockfd;
	struct addrinfo hints, *res, *p;
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &res)) == -1) {
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(rv));
		return 1;
	}

	for (p = res; p != NULL; p = p->ai_next){
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("socket()");
			continue;
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1){
			perror("bind()");
			continue;
		}
		
		break;
	}

	if (p == NULL) {
		perror("socket()");
		freeaddrinfo(res);
		exit(1);
	}

	int bytes;
	char buf[MAXBUFLEN];
	if ((bytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, NULL, NULL)) == -1) {
		perror("recvfrom()");
		exit(1);
	}
	buf[bytes] = '\0';
	printf("I received: %s", buf);
	close(sockfd);
	freeaddrinfo(res);
	return 0;


}
