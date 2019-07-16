#include "factory.h"

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
    strcpy(t.buf,FILENAME);
    int ret ;
    //先发文件长度
    ret = send_n(new_fd,(char *)&t,4+t.datalen);
    if(-1 == ret )
    {
        close(new_fd);
    }
    //再发文件内容
    int fd = open(FILENAME,O_RDONLY);
    if(-1 == fd)
    {
        perror("open");
        return -1 ;
    }
    while((t.datalen = read(fd,t.buf,sizeof(t.buf))))
    {
        ret = send_n(new_fd,(char *)&t,4+t.datalen);
        if(-1 == ret)
        {
            close(new_fd);
        }
    }
    send_n(new_fd,(char *)&t,4);//发送结束符
}
