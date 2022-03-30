#ifndef EXTCLIB_NET_H
#define EXTCLIB_NET_H

#include <stddef.h>

extern int listen_net();
extern int accept_net(int listener);
extern int connect_net();

extern int close_net(int listener);

extern void print_addr_net(struct sockaddr_in addr);

#endif 
