#include "factory.h"

void * thread_func(void * p)
{
    while(1);
}

int main(int argc,char ** argv)
{
    args_check(argc,5);
    //IP PORT ThREAD_NUM CAPACITY
    factory_t f ;
    int thread_num = atoi(argv[3]);
    int capacity = atoi(argv[4]);
    
    factory_init(&f,thread_num,capacity);
    factory_start(&f);
    while(1);

    return 0;
}

