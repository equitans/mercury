#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
//handle_client
#include "extclib/net.h"

struct client_sock
{
	struct sockaddr_in addr;
	char nickname[];
};



int main() {	
	char buf[256];

	int listener = listen_net();

	while (1)
	{
		int client = accept(listener, NULL, NULL);
		if(client < 0)
        {
            perror("accept");
            exit(3);
        }
		//if (client < 0) printf(" • Connection.");
		while (1)
		{
			int bytes_read = recv(client, buf, sizeof(buf), 0);
            if(bytes_read <= 0) break;
			printf(" %s\n", buf);
            
			//if(recv(client, buf, sizeof(buf), 0) <= 0) break;
			//printf(" « %s\t", buf);
		}
		close_net(listener);
		
	}
	



}

