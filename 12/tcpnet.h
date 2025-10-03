#ifndef __TCPNET_H__

#define __TCPNET_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

#include <pthread.h>

#define SERV_PORT 5001
#define SERV_IPADDR "192.168.7.3"
#define QUIT_STR "quit"

        struct cli_info {
//                struct list_head list; /* 内核链表*/
                int cli_fd;
                struct sockaddr_in cin;
                int qq_num;
                char nick[32];
                //...

        };

#endif
