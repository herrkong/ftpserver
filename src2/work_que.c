#include "work_que.h"

void que_init(pque_t pq,int capacity)
{
    memset(pq,0,sizeof(que_t));
    pq->que_capacity = capacity ;
    pthread_mutex_init(&pq->mutex,NULL);
}

void que_insert(pque_t pq,pNode_t pnew)
{
    //尾插法
    //先判断链表是否为空
    if(NULL==pq->que_tail)
    {
        pq->que_head = pnew ;
        pq->que_tail = pnew ;
    }
    else
    {
        pq->que_tail->pNext = pnew ;
        pq->que_tail = pnew ;
    }
    pq->que_size++;
}

void que_get(pque_t pq,pNode_t * pdelete)
{
    //头部删除法
    pNode_t pcur;
    pcur = pq->que_head;
    pq->que_head = pcur->pNext ;
    if(NULL==pq->que_head)
    {
        pq->que_tail = NULL ;
    }
    pq->que_size--;
    *pdelete = pcur ;
}
