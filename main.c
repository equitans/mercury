#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
	struct sockaddr_in addr;
	int sockfd, rc;
	char buf[64], message[64];

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror(" ✖ Error socket");
		exit(1);
	}

	rc = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if (rc) { // Возвращает 0 Если ошибка
		perror(" ✖ Error connect");
		exit(2);
	}
	
	rc = recv(sockfd, buf, 12, 0);
	if (rc <= 0) {
		perror(" ✖ Error recv");
		exit(1);
	} else {
		printf("%s\n", buf);
	}


	while (1) {
		printf(" » ");
		scanf("%s", message);
		rc = send(sockfd, message, sizeof(message), 0);
		if (rc <= 0) { // Возвращает число принятых байтов.
			perror(" ✖ Error send");
			exit(3);
		}
	}
	


}



