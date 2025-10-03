
/*udp demo */

/* usage:
 * ./client serv_ip serv_port 
*/
#include "net.h"
void usage (char *s)
{
	printf ("\nThis is multicast demo!\n");
	printf ("\nUsage:\n\t %s serv_ip serv_port", s);
	printf ("\n\t serv_ip: udp server ip address(between 224~239 segment)");
	printf ("\n\t serv_port: udp server port(serv_port > 5000)\n\n");
}

int main (int argc, char *argv[])
{
	int fd = -1;
	int port = SERV_PORT;

	port = atoi (argv[2]);
	if (port < 0 || (port > 0 && port <= 5000)) {
		usage (argv[0]);
		exit (1);
	}
	struct sockaddr_in sin;
	if (argc != 3) {
		usage (argv[0]);
		exit (1);
	}

	/* 1. 创建socket fd */
	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) < 0) {	//UDP编程
		perror ("socket");
		exit (1);
	}

	/*2.1 填充struct sockaddr_in结构体变量 */
	bzero (&sin, sizeof (sin));

	sin.sin_family = AF_INET;
	sin.sin_port = htons (SERV_PORT);	//网络字节序的端口号
#if 0
	sin.sin_addr.s_addr = inet_addr (argv[1]);
#else
	if (inet_pton (AF_INET, argv[1], (void *) &sin.sin_addr) != 1) {
		perror ("inet_pton");
		exit (1);
	}
#endif
	printf ("multicast started!\n");
	char buf[BUFSIZ];
	while (1) {
		fprintf (stderr, "pls input string:");
		bzero (buf, BUFSIZ);
		if (fgets (buf, BUFSIZ - 1, stdin) == NULL) {
			perror ("fgets");
			continue;
		}

		sendto (fd, buf, strlen (buf), 0, (struct sockaddr *) &sin, sizeof (sin));

		if (!strncasecmp (buf, QUIT_STR, strlen (QUIT_STR))) {	//用户输入了quit字符
			printf ("Client is exited!\n");
			break;
		}

	}
	close (fd);
	return 0;
}
