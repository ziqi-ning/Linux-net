#include <errno.h>

#include "tcpnet.h"
 void *cli_data_handle(void *arg);
int main(void)
{
	int fd = -1, newfd;
//	int ret = -1;
	struct sockaddr_in sin;
//	char buf[BUFSIZ];

	/*1.创建IPV4的TCP套接字 */	
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0) {
		perror("socket error!");
		exit(1);	
	}

     /* 允许本地的地址和端口快速重用 */
        int b_reuse = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(int));


	/* 2.绑定在服务器的IP地址和端口号上*/
	 /* 2.1 填充struct sockaddr_in结构体*/
	 bzero(&sin, sizeof(sin));
	 sin.sin_family = AF_INET;
	 sin.sin_port = htons(SERV_PORT);

	/*优化1：  接收从本机任意IP地址过来的发给TCP，SERV_PORT的数据*/
         sin.sin_addr.s_addr = htonl(INADDR_ANY);
	 
	/* 2.2 绑定*/
	if(bind(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("bind");
	       	exit(1);	
	}	
	/*3.把主动套接字变为被动套接字 */
	listen(fd, 5);

	printf("Server starting.....OK!\n");

	pthread_t tid; 
	while(1) {
		struct cli_info *pcinfo= NULL;
	
		struct sockaddr_in cin;
        	socklen_t clen = sizeof(cin);
        	/*等待客户端连接*/
		do {
                	newfd = accept(fd, (struct sockaddr *)&cin, &clen);
        	}while(newfd < 0 && EINTR ==errno);
        	if(newfd < 0) {
                	perror("accept");
                	exit(1);
        	}

		/* 填充客户端信息*/
		pcinfo= (struct cli_info *)malloc(sizeof(struct cli_info));
		
		bzero(pcinfo, sizeof(struct cli_info));

		//填充内核链表
		//....FIXME!!!!
		pcinfo->cli_fd = newfd;
		memcpy(&pcinfo->cin, &cin, sizeof(cin));	
		//...填充其他数据
		//....FIXME!!!
		//把cinfo加入到user_info内核链表
		//...FIXME!!
		pthread_create(&tid, NULL, cli_data_handle, (void *)pcinfo);
		pthread_detach(tid);		
	}
	

	close(fd);

	return 0;
}

 void *cli_data_handle(void *arg)
{
	struct cli_info *pcinfo = (struct cli_info *)arg;
	char buf[BUFSIZ];
	char ipaddr[16];
	int ret = -1;

	/*设置线程的分离属性*/
//	pthread_detach(pthread_self());

	int newfd = pcinfo->cli_fd;
	struct sockaddr_in cin;

	memcpy(&cin ,&pcinfo->cin, sizeof(cin));

	bzero(ipaddr, 16);
        if(!inet_ntop(AF_INET, (void *)&cin.sin_addr, ipaddr, sizeof(cin))) {
                perror("inet_ntop");
                exit(1);
        }
        printf("Client(%s:%d) is conneted!\n", ipaddr,ntohs(cin.sin_port));
	
	
	/*5.和客户端进行信息的交互(读写) */
        while(1) {
                bzero(buf, BUFSIZ);

                do {
                        ret =read(newfd, buf,BUFSIZ-1);
                }while(ret < 0 && EINTR == errno);
                if(ret < 0) {
                        continue;
                }
                /* 处理数据*/
                //....
                printf("Receive data: %s\n",buf);
                if(!ret || !strncasecmp(buf, QUIT_STR, strlen(QUIT_STR))) { //客户端发送了quit字符
                       //...FIXME!!, 删除cli_info的所占内存
			 break;
                }
        }
        close(newfd);

	return NULL;
}
