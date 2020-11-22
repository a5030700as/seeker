#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>

/*
    
    传输的是内存字节 只要 数据格式转换一下 就可以是数据类型了。。。。。。。。。
    文件读写的是 buff + size 也就不是什么 字符串格式的问题了 。。。。。。。。。

*/

char recv_buff[1024];
int main(int argc, char * argv[])
{
    printf("start %s \n", argv[0]);
    
    struct sockaddr_un addr;

    // 建立一个SOCK 
    int sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);

    //绑定使用 
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(&addr.sun_path[1], "server", sizeof(addr.sun_path) - 2); // 匿名套接字格式 第一个是 0 因为前面memset了 第一个一定是 0;

    //绑定 server 
    bind(sock_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));

    int length = 0;
    int len = 0;
    
    //等待数据接收
    while (1)
    {
        len = sizeof(struct sockaddr_un);
        printf(" go to ...\n");
        length = recvfrom(sock_fd, recv_buff, sizeof(recv_buff), 0,\
                           (struct sockaddr *)&addr,(socklen_t *) &len);

        printf("recv %d  from %s   %s \n", length, recv_buff, &addr.sun_path[1]);  //使用的 就是 本地套接字的格式 
        sleep(1);
    }

    return 0;
}
