/* -------------------------------------------------------
 * FileName  : doProc.c (1.40)
 * Function  :
 * CreateInfo: tangyx @ 2014.12.17 16:59:28
 * ------------------------------------------------------- */
 
#include "nettest.h"

int udpProc(int SockFd)
{
    struct sockaddr_in  udp_addr;
    socklen_t           namelen;
    int                 sockfd;
    char                cli_addr[50];
    int                 rcvlen;
    char                rcvbuf[BUFF_SIZE];

    sockfd = SockFd;
    while(1)
    {
        memset(&udp_addr, 0, sizeof(struct sockaddr));
        namelen = sizeof(udp_addr);
        memset( rcvbuf, 0, sizeof(rcvbuf) );
        rcvlen = recvfrom(sockfd, rcvbuf, BUFF_SIZE, 0, (struct sockaddr *)&udp_addr, &namelen);
        if ( rcvlen <= 0 )
        {
            E_LOG("接收UDP通讯连接发生错误=[%d-%s]!", rcvlen, strerror(errno));
            continue;
        }

        W_LOG("[udp]read req buf ok, len=[%d]...", rcvlen);
        D_LOG(HEX_FORMAT, rcvbuf, rcvlen);

        memset(cli_addr, 0, sizeof(cli_addr));
        sprintf(cli_addr, "%s", inet_ntoa(udp_addr.sin_addr));
        if(strstr(rcvbuf, "TEST"))
        {
            memset(rcvbuf, 0, sizeof(rcvbuf));
            strcpy(rcvbuf, cli_addr);
            rcvlen = strlen(rcvbuf);
        }

        W_LOG("=>和[%s]已建立了连接!", cli_addr);
        sendto(sockfd, rcvbuf, rcvlen, 0, (struct sockaddr *)&udp_addr, namelen);
    }

    return 0;
}
