#ifndef __MAKEU_NET_H__
#define __MAKEU_NET_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>			/* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>			/* superset of previous */

#include <sys/select.h>
#include <sys/time.h>
//#include <sys/types.h>
#include <unistd.h>
#include <sys/un.h>

#define UNIX_DOMAIN_FILE "/tmp/my_domain_file.1"

#define BACKLOG 5


#define QUIT_STR "quit"
#define SERV_RESP_STR "SERVER:"
#endif
