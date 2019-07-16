#include "factory.h"

void factory_init(pfactory_t pf ,int thread_num,int capacity)
{
    memset(pf,0,sizeof(factory_t));
    pf->pth_arr=(pthread_t*)calloc(thread_num,sizeof(pthread_t));
    pf->thread_num = thread_num ;
    pthread_cond_init(&pf->cond,NULL);
    que_init(&pf->que,capacity);
}

void factory_start(pfactory_t pf)
{
    for(int i = 0 ;i<pf->thread_num;i++)
    {
        //创建线程 给子线程线程函数传了1个参数 就是传了整个世界 
        pthread_create(pf->pth_arr+i,NULL,thread_func,pf);
    }
}

//信号函数
void sigfunc(int signum)
{
    printf("%d is coming\n",signum);
}


int trans_file(int new_fd)
{
    train t ;
    signal(SIGPIPE,sigfunc);
    //发送文件名
    t.datalen = strlen(FILENAME);
    //实际要转为网络字节序
    strcpy(t.buf,FILENAME);




}
