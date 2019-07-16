#pragma once
#include "head.h"

//任务队列
typedef struct node
{
    //这里再加入用户名密码之类的
    //或者加入它上次打开网盘的状态信息
    int new_fd;
    struct node * pNext;
}Node_t,*pNode_t;

typedef struct
{
    pNode_t que_head,que_tail;
   //服务器要设置承载能力上限 否则无法计算负载均衡
   //根据你的具体业务设置上限
    int que_capacity;
    int que_size;
    pthread_mutex_t mutex;
}que_t,*pque_t;

void que_init(pque_t,int);//初始化队列
void que_insert(pque_t,pNode_t);//插入队列
void que_get(pque_t,pNode_t);//拿到队列
