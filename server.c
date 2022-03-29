#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#include "extclib/net.h"

void * AcceptClient(int s_sockap) {
	int rc;
	char buf[64];
	
	rc = send(s_sockap, " ✔ Connected", 12, 0);
	if (rc <= 0) {
		perror(" ✖ Error send");
		exit(0);
	}

	while (1) {
		rc = recv(s_sockap, buf, 64, 0);
		if (rc <= 0) {
			perror(" ✖ Error recv");
			exit(0);
		} else {
			printf(" %s\n", buf);
		}
	}
}



int main() {
	struct sockaddr_in local;
	struct sockaddr_in addr;
	socklen_t t_addr = sizeof(addr);

	int s_sockap, rc;
	char buf [64];
	
	int s_sockfd = listen_net();
	
	while (1) {
		s_sockap = accept(s_sockfd, (struct sockaddr *)&addr, &t_addr);
		if (s_sockap < 0) {
			perror(" ✖ Error accept");
			exit(4);
		}

		print_addr_net(addr);

		pthread_t thread;
	//	int s_sockap_p = &s_sockap;
		//pthread_create(&thread, NULL, AcceptClient, s_sockap_p);
		AcceptClient(s_sockap);	

		/*
		while(1) {
			rc = recv(s_sockap, buf, 64, 0);
			if (rc <= 0) {
				perror(" ✖ Error recv");
				exit(5);
			}

			printf(" « %s\n", buf);
			rc = send(s_sockap, "2", 1, 0);
			if (rc <= 0) {
				perror(" ✖ Error send");
				exit(6);
			}
		}
		*/

	}



}

