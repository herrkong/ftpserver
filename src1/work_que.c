#include "work_que.h"

void que_init(pque_t pq,int capacity)
{
    memset(pq,0,sizeof(que_t));
    pq->que_capacity = capacity ;
    pthread_mutex_init(&pq->mutex,NULL);
}
