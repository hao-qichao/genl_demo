/*************************************************************************
	> File Name: netlink_usb.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月10日 星期五 16时11分49秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/netlink.h>
#include <sys/socket.h>

#define UEVENT_BUFFER_SIZE 2048

int main(int argc, char ** argv)
{
    struct sockaddr_nl client;
    struct timeval tv;
    int cpplive, rcvlen, ret;
    fd_set fds;
    int buffersize =1024;

    cpplive = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);
    memset(&client, 0, sizeof(client));
    client.nl_family = AF_NETLINK;
    client.nl_pid = getpid();
    client.nl_groups = 1;
    setsockopt(cpplive, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize));

    bind(cpplive, (struct sockaddr *)&client, sizeof(client));
    
    while (1)
    {
        char buf[UEVENT_BUFFER_SIZE] = {0};
        FD_ZERO(&fds);
        FD_SET(cpplive, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 100*1000;
        ret = select(cpplive+1, &fds, NULL, NULL, &tv);
        if (ret < 0)
            continue;
        if (!(ret > 0 && FD_ISSET(cpplive, &fds)))
            continue;
        rcvlen = recv(cpplive, &buf, sizeof(buf), 0);
        if (rcvlen > 0)
        {
            printf("%s\n", buf);

        }
    }
    close (cpplive);
    return 0;
}
