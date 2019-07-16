#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"
#define FILENAME "file"
typedef struct
{
    int datalen ; //文件大小
    char buf[1024]; //文件内容

}train;


typedef struct{
	pthread_t *pth_arr;
	int thread_num;
	pthread_cond_t cond;
	que_t que;
	short start_flag;//未启动为0，启动为1
}factory_t,*pfactory_t;

void * thread_func(void*);
void factory_init(pfactory_t,int,int);
void factory_start(pfactory_t);
int trans_file(int);//发送文件
int send_n(int,char *,int);


#endif
