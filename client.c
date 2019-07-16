#include <stdio.h>
#include <func.h>

int main(int argc,char ** argv)
{
    ARGS_CHECK(argc,3);
    int sfd;
    //socket
    sfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1==sfd)
    {
        perror("socket");
        return -1 ;
    }
    
    //struct sockaddr_in
    struct sockaddr_in ser ;
    memset(&ser,0,sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port = htons(atoi(argv[2]));
    //IP地址的点分十进制转为网络字节序
    ser.sin_addr.s_addr = inet_addr(argv[1]);

    int ret ;
    //connect
    ret = connect(sfd,(struct sockaddr *)&ser,sizeof(ser));
    if(-1==ret)
    {
        perror("connect");
        return -1 ;
    }







    return 0;
}

