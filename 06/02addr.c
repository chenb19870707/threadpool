#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    unsigned long addr = inet_addr("192.168.1.220");
    printf("addr=%u\n",ntohl(addr));

    struct in_addr ipaddr;
    ipaddr.s_addr =  addr;
    printf("%s\n",inet_ntoa(ipaddr));

    return 0;
}