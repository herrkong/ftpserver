#include <sys/epoll.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#define args_check(a,b) {if(a!=b){printf("error args\n");return -1;}}

#define FILENAME "file"
typedef struct{
	pid_t pid;
	int fd;//管道的一端
	short busy;//代表子进程是否忙碌，0代表非忙碌，1代表忙碌
}process_data;

typedef struct{
	int data_len;//控制数据，火车头，记录火车装载内容长度
	char buf[1000];//火车车厢
}train;
void make_child(process_data*,int);
void child_handle(int);
int send_fd(int,int);
int recv_fd(int,int*);
int trans_file(int);
int recv_n(int,char*,int);
