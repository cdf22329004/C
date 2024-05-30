#include "./inc/global.h"
int sockfd;
int flag = 0;
void menu()
{
	printf("1: login\n");
	printf("2: register\n");
	printf("0: help\n");
}
void menu1()
{
	printf("1: chat\n");
	printf("2: exit\n");
}
int login()
{
	struct user q;
    char buf[128] = {0};
	printf("please input name\n");
	scanf("%s",q.name);
	printf("please input passwd\n");
pw:
	scanf("%s",q.passwd);
	strcat(buf,"login$");
	strcat(buf,q.name);
	strcat(buf,"$");
	strcat(buf,q.passwd);
	write(sockfd,(void *)buf,strlen(buf));
	memset(buf,0,128);
	read(sockfd,(void *)buf,128);
	if(strcmp(buf,"0") == 0)
	{
		printf("login success\n");
		return 0;
	}
	if(strcmp(buf,"1") == 0)
	{
		printf("user name is not exist,please register\n");
		return -1;
	}
	if(strcmp(buf,"2") == 0)
	{
		printf("user passwd is error,please input passwd\n");
        memset(buf,0,128);
		memset(q.passwd,0,32);
		goto pw;
	}

}
void client_register_user()
{
	char buf[128] = {0};
	struct user q = {0};
us:
	printf("please input register name\n");
	scanf("%s",q.name);
	printf("please input register passwd\n");
	scanf("%s",q.passwd);
	strcat(buf,"register$");
	strcat(buf,q.name);
	strcat(buf,"$");
	strcat(buf,q.passwd);
	write(sockfd,(void *)buf,strlen(buf));
	memset(buf,0,128);
	read(sockfd,(void *)buf,128);
	if(strcmp(buf,"0") == 0)
	{
		printf("register success,please login\n");
		return ;
	}
	if(strcmp(buf,"1") == 0)
	{
		printf("user name is exist,please register\n");
		memset(buf,0,128);
		memset(q.name,0,32);
		memset(q.passwd,0,32);
		goto us;
	}
}
void display_user(char *p)
{
	int i;
	i = 1;
	while(1)
	{
		if(*p == '\0')
			break;
		if(*p == '$')
		{
			printf(":%d\n",i);
			p ++;
			i ++;
		}
		printf("%c",*p);
		p ++;
		
	}
	return ;
}
void myfun(int sig)
{
     flag = 1;
	 printf("sig = %d\n",sig);
	 return ;
}
int main()
{
	char user[1024] = {0};
	int choice,len;
	char buf[128] = {0};
	int pid;
	//int sockfd;
	struct sockaddr_in myaddr;
	int ret;
	sockfd = socket(PF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		printf("socket error\n");
		exit(-1);
	}
    myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(7777);
	myaddr.sin_addr.s_addr = inet_addr("192.168.1.123");
	ret = connect(sockfd,(struct sockaddr *)&myaddr, sizeof(struct sockaddr));
	if(ret < 0)
	{
		printf("connect error\n");
		exit(-2);
	}

	menu();
	while(1)
	{
		printf("please input choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
                ret = login();
				break;
			case 2:
				client_register_user();
				break;
			case 0:
				break;
		}
		if(ret == 0)
		{
            break;
		}
	}
    
    read(sockfd,(void *)user,1024);
start:
	flag = 0;
	display_user(user);
	//memset(user,0,1024);
	signal(10,myfun);
	menu1();
	while(1)
	{
		printf("please input choice\n");
		scanf("%d",&choice);
		if(choice == 2)
		{
			//sprintf(buf,"quit$%s",q)
			write(sockfd,"quit",4);
			exit(0);
		}
		if(choice == 1)
		{
			strcpy(buf,"chat$");
			pid = fork();
			if(pid < 0)
			{
				printf("fork error\n");
				exit(-5);
			}
			if(pid > 0)
			{
				while(1)
				{
				/*	if(flag == 1)
					{
						goto start;
					}*/
					printf("please input chat name \n");
					scanf("%s",buf + 5);
					strcat(buf,"$");
					len = strlen(buf);
					while(1)
					{
						if(flag == 1)
						{
							printf("goto start\n");
							goto start;

	c						}
	             		printf("please input data\n");
						scanf("%s",buf + len);
						write(sockfd,(void *)buf,strlen(buf));
						if(strcmp(buf +len, "quit") == 0)
						{
				    		 kill(pid,9);
							 goto start;
						}
						memset(buf + len,0,128 - len);
					}
				}
			}
			if(pid == 0)
			{
				while(1)
       			 {
					memset(buf,0,128);
					read(sockfd,(void *)buf,128);
					printf("recv:%s\n",buf);
					if(strcmp(buf,"quit") == 0)
					{
						kill(getppid(),10);
						exit(0);
					}
				}
			}	
		}	

	}
	//chat 
	/*
	while(1)
	{
		printf("please input data\n");
		scanf("%s",buf);
		write(sockfd,(void *)buf,strlen(buf));
		if(strcmp(buf,"quit") == 0)
		{
			break;
		}
		memset(buf,0,128);
	}
	close(sockfd);
	*/
	return 0;
}
