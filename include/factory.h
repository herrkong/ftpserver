#pragma once
#include "head.h"
#include "work_que.h"

typedef struct
{
    pthread_t *pth_arr;//线程数组
    int thread_num;//线程数目
    pthread_cond_t cond;//条件变量
    que_t que;//直接把任务队列放进来了
    short start_flag;//启动标志

}factory_t,*pfactory_t;
