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
        pthread_create(pf->pth_arr+i,NULL,thread_func,pf);
    }
}


