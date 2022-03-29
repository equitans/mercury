#ifdef __linux__
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <stdlib.h>
	#include <stdio.h>
#else
	#warning "net.h: platform not supported."
#endif

#if defined(__linux__)

#include "net.h"

extern int listen_net() {
	int listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener < 0 ) { perror(" ✖ Error socket"); exit(0);}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(listener, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
		perror(" ✖ Error bind");
		exit(0);
	}
	if (listen(listener, SOMAXCONN) != 0) {
		perror(" ✖ Error listen");
		exit(0);
	}
	return listener;
}

extern int accept_net(int listener) {

}

extern int connect_net() {
	int conn = socket(AF_INET, SOCK_STREAM, 0);
	if (conn < 0) { perror(" ✖ Error socket"); exit(0);}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (connect(conn, (struct sockaddr*)&conn, sizeof(conn)) != 0) {
		perror(" ✖ Error connect");
		exit(0);
	}
	return conn;
}

extern void print_addr_net(struct sockaddr_in addr) {
	printf(" • %d.%d.%d.%d\n",
			addr.sin_addr.s_addr & 0xff,
			(addr.sin_addr.s_addr & 0xff00) >> 8,
			(addr.sin_addr.s_addr & 0xff0000) >> 16,
			(addr.sin_addr.s_addr & 0xff000000) >> 24);
}

#endif
