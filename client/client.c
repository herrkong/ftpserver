#include "func.h"

int send_n(int sfd,char * buf,int len)
{
    int total = 0 ;
    int ret ;
    while(total < len)
    {
        ret = send(sfd,buf+total,len - total,0);
        total = total + ret ;
    }
    return 0;
}


int recv_n(int sfd,char * buf,int len)
{
    int total = 0 ;
    int ret ;
    while(total < len)
    {
        ret = recv(sfd,buf+total,len-total,0);
        if(!ret)
        {
            return -1 ;
        }
        total = total + ret ;
    }
    return 0 ;
}


int main(int argc,char ** argv)
{
    args_check(argc,3);
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
    ret = connect(sfd,(struct sockaddr *) &ser,sizeof(ser));
    if(-1==ret)
    {
        perror("connect");
        return -1 ;
    }
    printf("连接成功\n");

    int datalen;
    char buf[1024]={0};
    recv_n(sfd,(char *)&datalen,sizeof(int));//4个字节
    recv_n(sfd,buf,datalen);
    //接收文件大小    
    
    off_t file_size,download_size=0,before_download_size=0,
          compare_level;
    recv_n(sfd,(char *)&datalen,sizeof(int));
    recv_n(sfd,(char *)&file_size,datalen);
    //接收文件内容
    int fd = open(buf,O_WRONLY|O_CREAT,0666);
    compare_level = file_size/100;
    while(1)
    {
        ret = recv_n(sfd,(char *)& datalen,sizeof(int));
        if(-1==ret)
        {
            break;
        }
        if(datalen>0)
        {
            ret = recv_n(sfd,buf,datalen);
            if(-1 == ret )
            {
                break;
            }
            download_size = download_size + datalen ;
            write(fd,buf,datalen);
            if(download_size - before_download_size > compare_level)
            {
                printf("%5.2f%s\r",(float)download_size*100/file_size,"%");
                fflush(stdout);//刷新输出缓冲区
                before_download_size = download_size ;
            }
        }
        else
        {
            printf("%5.2f%s\n",(float)download_size*100/file_size,"%");
            break;   
        }
    }   
    close(fd);
    close(sfd);
    return 0;
}

