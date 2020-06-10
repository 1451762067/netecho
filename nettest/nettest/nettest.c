 
#define  _MAIN_

#include "nettest.h"

int main(int argc, char **argv)
{
    int                 i;
    struct sockaddr_in  tcp_addr;
    socklen_t           namelen;
    int                 sockfd;
    int                 newsock;
    pid_t               childpid;
    char                cli_addr[50];

    /* �����ź��� */
    for (i = 0; i < 32; i++)
    {
        signal(i,SIG_IGN);
    }

    /*
     * ��ʼ��
     */
    if ( getInit(argc, argv) )
    {
        fprintf(stderr, "getInit error!\n");
        exit(-1);
    }

    /* fork a process to process udp */
    if ((childpid = fork()) > 0)
    {
        for( sockfd=-1, i=0; sockfd<0; i++ )
        {
            (sockfd = getSrvSocket(HostPort,"udp",5))>0 ? 0 : sleep(30*(1+i/10));
        }
    W_LOG("[UDP]==== %s ������=[%s], �ȴ�������...", ProgName, HostPort);
        udpProc(sockfd);  
        close(sockfd);
        exit(0);
    }

    /* ����TCP���� */
    for( sockfd=-1, i=0; sockfd<0; i++ )
    {
        (sockfd = getSrvSocket(HostPort,"tcp",5))>0 ? 0 : sleep(30*(1+i/10));
    }

    /*
     * �ȴ�����
     */
    W_LOG("[TCP]==== %s ������=[%s], �ȴ�������...", ProgName, HostPort);
    while (1)
    {
        namelen = sizeof(tcp_addr);
        memset(&tcp_addr, 0, sizeof(struct sockaddr_in));
        if ((newsock=accept(sockfd,(struct sockaddr *)&tcp_addr,&namelen))<0)
        {
            E_LOG("accept error [%d-%s]!\n", errno, strerror(errno));
            continue;
        }
        

        memset(cli_addr, 0, sizeof(cli_addr));
        sprintf(cli_addr, "%s", inet_ntoa(tcp_addr.sin_addr));
        W_LOG("=>��[%s]�ѽ���������!", cli_addr);

        /* fork a process to process it */
        if ((childpid = fork()) < 0)
        {
            E_LOG("fork : System fatal error!\n");
            close(newsock);
            continue;
        }

        if ( childpid > 0 ) /* father process */
        {
            close(newsock);
            continue;
        }

        /* child process */
        close(sockfd);

        tcpProc(newsock, cli_addr);

        close(newsock);
        exit(0);
    }
}
