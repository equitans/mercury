#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
//handle_client
#include "extclib/net.h"

#define MAX_CLIENT 5
void * client_handler(void *clientdata_t);
struct ClientData_tag
{
	int id;
	int sock;
};

void * client_handler(void *clientdata_t) {
	struct ClientData_tag *client_data = (struct ClientData_tag*)clientdata_t;
	client_data->id = 2;
	printf("id\t %d\nsock \t %d\n", client_data->id,client_data->sock);
	char buf[256];
	while (1)
	{
		if (recv(client_data->sock, buf, sizeof(buf), 0) < 0) {
			perror(" ✖ Error recv");
		}
		printf("\t%s\n", buf);
	}
	return 0;
}


int main() {
	pthread_t client_thread[MAX_CLIENT];
	struct ClientData_tag clientdata_t[MAX_CLIENT];
	int client_count = 0;
	char buf[256];
	int status_addr[MAX_CLIENT];
	int listener = listen_net();

	while (1)
	{
		printf("%d\n", client_count);
		clientdata_t[client_count].sock = accept(listener, NULL, NULL);
		if (clientdata_t[client_count].sock < 0) {
			perror(" ✖ Error accept");
			continue;
		} 
		printf("1%d\n", client_count);
		clientdata_t[client_count].id = client_count;

		if (pthread_create(&client_thread[client_count], NULL, client_handler, (void*)&clientdata_t[client_count]) != 0) {
			perror(" ✖ Error create thread");
			continue;
		}
		//printf("2%d\n", client_count);
		//if (pthread_join(client_thread[client_count], (void**)&status_addr[client_count]) != 0) {
		//	perror(" ✖ Error thread join");
		//	continue;
		//}
		//printf("%d\n", status_addr[client_count]);
		printf("%d\n", clientdata_t[client_count]->id);
		client_count++;
	
	}
	



}

