#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>

char send_buff[1024] = "hello server \n";
int main(int argc, char * argv[])
{
    printf("start %s \n", argv[0]);

    struct sockaddr_un addr;
    int sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    memset(&addr, 0, sizeof(struct sockaddr_un));

    addr.sun_family = AF_UNIX;
    strncpy(&addr.sun_path[1], "client", sizeof(addr.sun_path) - 2);
    bind(sock_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));

    strncpy(&addr.sun_path[1], "server", sizeof(addr.sun_path) - 2);
    int length = 0;
    int len = 0;
    while (1)
    {
        len = sizeof(struct sockaddr_un);
        length = sendto(sock_fd, send_buff, sizeof(send_buff), 0,\
                           (struct sockaddr *)&addr, len);
        
        printf("send %d %s \n", length, &addr.sun_path[1]);
        sleep(1);
    }

    return 0;
}
