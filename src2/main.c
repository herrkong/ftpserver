#include "factory.h"

void cleanup(void * p)
{
    pthread_mutex_t * mutex = (pthread_mutex_t *)p;
    pthread_mutex_unlock(mutex);
}

//线程函数
void * thread_func(void * p)
{
    pfactory_t pf = (pfactory_t)p;//指向线程工厂的指针
    pque_t pq = &pf->que; //指向任务队列的指针
    pNode_t pdelete;//要领走的任务(待删除的结点)
    while(1)
    {
        //所有任务(结点)都加锁
        pthread_mutex_lock(&pq->mutex);
        pthread_cleanup_push(cleanup,&pq->mutex);
        if(pf->start_flag && 0 == pq->que_size)
        {
            //等待唤醒 否则阻塞在此 睡觉
            pthread_cond_wait(&pf->cond,&pq->mutex);
        }
        if(!pf->start_flag)
        {
            pthread_exit(NULL);
        }
        //拿结点之前要判断队列不为为空 才来取结点...
        //pdelete是一个指针 传这个指针的地址过去  
       //走到这里时 一定是只有一个人(线程)来取结点的~ 
        que_get(pq,&pdelete);//从队列获取任务
        pthread_mutex_unlock(&pq->mutex);
        pthread_cleanup_pop(0);
        trans_file(pdelete->new_fd);//发文件
        free(pdelete);
        pdelete=NULL;
    }
}

int main(int argc,char ** argv)
{
    args_check(argc,5);
    //IP PORT ThREAD_NUM CAPACITY
    factory_t f ;
    int thread_num = atoi(argv[3]);
    int capacity = atoi(argv[4]);
    
    factory_init(&f,thread_num,capacity);
    factory_start(&f);//创建线程
    
    //主线程的流程
    //socket listen bind  accept
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in ser;
    memset(&ser,0,sizeof(ser));
    ser.sin_family = AF_INET ;
    ser.sin_port = htons(atoi(argv[2]));
    ser.sin_addr.s_addr = inet_addr(argv[1]);
    //IP地址点分十进制转为网络字节序
    int ret ;
    int reuse = 1;
    setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ret = bind(sfd,(struct sockaddr *)&ser,sizeof(ser));
    if(-1==ret)
    {
        perror("bind");
        return -1 ;
    }
    int new_fd ;//连接之后产生一个新的fd
    pque_t pq = &f.que;//指向任务队列的指针
    while(1)
    {
        new_fd = accept(sfd,NULL,NULL);
        pNode_t pnew = (pNode_t)calloc(1,sizeof(Node_t));
        pnew->new_fd = new_fd ;
        {
            //插入任务队列之前加锁 
            pthread_mutex_lock(&pq->mutex);
            que_insert(pq,pnew);//将任务放入队列 尾插法
            pthread_mutex_unlock(&pq->mutex);
            //在锁里面只做简单较少的操作
            pthread_cond_signal(&f.cond);//唤醒一个子线程
        }
    }
    return 0;
}

