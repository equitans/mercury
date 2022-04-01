#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#include "extclib/net.h"


int main() {
	char buf[256];
	
	int conn = connect_net();
	
	while (1)
	{
		scanf("%s", buf);
		if(send(conn, buf, sizeof(buf), 0) <= 0) {
			perror(" ✖ Error send");
		}
		//if(recv(conn, buf, 1, 0) <= 0) {
		//	perror(" Error Crecv");
		//}
		//printf("%s\n", buf);
	}
	

	return 0;  
}

